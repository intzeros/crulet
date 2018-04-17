#!/usr/bin/python

import os
import json
import cgi
import argparse
import sys
import datetime
from bs4 import BeautifulSoup

reload(sys) 
sys.setdefaultencoding('utf-8')

db_path = "compile_commands.json"
json_report_dir = "report/json/"
html_report_dir = "report/html/"
json_report_file = "report/report.json"
html_report_file = "report/index.html"
css_files = "css/report.css"

# get absolute path
def get_absolute_path(dir, filename):
  if filename[0] == '/':
    return filename
  else:
    n = len(dir) 
    if dir[n-1] == '/':
      return dir + filename
    else:
      return dir + "/" + filename

# create css files
def create_css_files(report_root):
  script_root = os.path.split(os.path.realpath(__file__))[0]
  css_dir = os.path.join(report_root, "report/css/")
  if not os.path.exists(css_dir):
    os.makedirs(css_dir)
  os.system("cp -rf " + os.path.join(script_root, "css/*") + " " + css_dir)

# get css relative path
def get_css_path(cur_path, report_root):
  parts = cur_path.split('/')
  n = len(parts) - len(report_root.split('/')) - 2
  path = ""
  while n > 0:
    path = "../" + path
    n = n - 1
  return path + css_files

# get project root path
def get_project_root(db_path):
  path_list = []
  with open(db_path, "r") as fin:
    data = json.load(fin)
    if data == None:
      return
    for item in data:
      abspath = get_absolute_path(item["directory"], item["file"])
      path_list.append(abspath)

  return os.path.commonprefix(path_list)

# simplify path like /a/b/../c
def simplify_path(path):
  stack = []
  parts = path.split('/')
  for token in parts:
    if token in ('.', ''):
      pass
    elif token == '..':
      if stack:
        stack.pop()
    else:
      stack.append(token)
  return '/' + '/'.join(stack)

# fix header path (like: ../lib/A.h) to absulte path 
def fix_header_path(project_root, report_root, h_path, c_path):
  if h_path[0] == '/':
    return h_path
  if os.path.splitext(h_path)[1] != ".h":
    return h_path

  report_dir = os.path.join(report_root, json_report_dir)
  source_path = os.path.dirname(c_path[-(len(c_path) - len(report_dir)):])
  return simplify_path(os.path.join(project_root, source_path, h_path))

# read and filter json files
def read_all_json_files(project_root, report_root):
  jsonfiles = []
  report_dir = os.path.join(report_root, json_report_dir)
  for curpath, subdirs, files in os.walk(report_dir):
    for file in files:
      parts = os.path.splitext(file)
      if parts[1] == ".json":
        jsonfiles.append(curpath + "/" + file)

  data_list = []
  errs_set = set()

  for file in jsonfiles:
    c_filepath = os.path.splitext(file)[0]
    with open(file, "r") as fin:
      data = json.load(fin)
      if data == None:
        continue
      for item in data:
        item["location"]["file"] = fix_header_path(project_root, report_root, item["location"]["file"], c_filepath)
        if str(item) not in errs_set:
          errs_set.add(str(item))
          data_list.append(item)

  with open(os.path.join(report_root, json_report_file), "w") as fout:
    fout.write(json.dumps(data_list, indent=4, ensure_ascii=False))

# create bug report index.html
def create_html_index(project_root, report_root):
  fout = open(os.path.join(report_root, html_report_file), "w")
  fout.write('''<html>\n<head>\n<meta charset="UTF-8">\n''' + 
              '''<link rel="stylesheet" type="text/css" href="''' + css_files + '''">\n''' +
              '''<title>Crulet analysis results</title>\n</head>\n''' +
              '''<body>\n<h1>Crulet Analysis Results</h1>\n''')
  fout.write('''<h2>General Information</h2>\n<table class="index"><tbody>\n''')
  nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
  fout.write("<tr><td>Project path</td><td>" + project_root + "</td></tr>\n")
  fout.write("<tr><td>Create time</td><td>" + nowTime + "</td></tr>\n")
  fout.write("</tbody></table>\n")
  fout.write('''<h2>Summary</h2>\n<table class="index">\n<tr><th>Bug Type</th><th>Quantity</th><th>Display</th></tr>\n''')
  
  errs_counts = {}
  with open(os.path.join(report_root, json_report_file), "r") as fin:
    data = json.load(fin)
    if data == None:
      return
    for item in data:
      if not errs_counts.has_key(item["type"]):
        errs_counts[item["type"]] = 0
      errs_counts[item["type"]] = errs_counts[item["type"]] + 1

  err_items = errs_counts.items()
  err_items.sort()

  total_num = 0
  for k, v in err_items:
    total_num = total_num + v
    
  fout.write('''<p>Total: ''' + str(total_num) + '''</p>''')

  for k, v in err_items:
    fout.write('''<tr><td>''' + k + '''</td><td>''' + str(v) + '''</td><td><input type="checkbox" onclick="chose(this)" name="dispaly" value="1" checked="checked"/></td></tr>\n''')
  
  fout.write('''</table>\n''')
  fout.write('''<h2>Reports</h2>\n<table class="index">\n<tr><th>Bug Type</th><th>Description</th><th>File</th><th>Line</th><th>Link</th></tr>\n''')

  with open(os.path.join(report_root, json_report_file), "r") as fin:
    data = json.load(fin)
    if data == None:
      return
    for item in data:
      file = item["location"]["file"]
      path = file[-(len(file) - len(project_root)):]
      html_path = os.path.join("html/", path + ".html")
      fout.write("<tr><td>" + item["type"] + "</td><td>" + item["description"] + "</td><td>" 
                  + os.path.basename(item["location"]["file"]) + "</td><td>" + str(item["location"]["line"]) 
                  + '''</td><td><a href="''' + html_path + "#" + str(item["location"]["line"]) + '''">View Report</a></td></tr>\n''')

  fout.write('''</table>\n</body>\n</html>\n''')
  fout.close()

# create single .html
def create_html_file(report_root, input_file, output_file, filename):
  fout = open(output_file, "w")
  fout.write('''<html>\n<head>\n<meta charset="UTF-8">\n''' + 
              '''<link rel="stylesheet" type="text/css" href="''' + get_css_path(output_file, report_root) + '''">\n''' +
              '''<title>''' + filename + '''</title>\n</head>\n''' +
              '''<body>\n<table class="code"><tbody>\n''')
  fin = open(input_file, "r")
  line_num = 0
  for line in fin.readlines():
    line_num = line_num + 1
    fout.write('''<tr id="''' + str(line_num) + '''">\n<td class="num">''' + str(line_num) + '''</td>\n<td>''')
    fout.write(cgi.escape(line).replace(' ', '&nbsp;') + '''</td>\n</tr>\n''')

  fout.write('''</tbody></table>\n</body>\n</html>\n''')
  fout.close()

def cmp(a, b):
  if a["location"]["line"] == b["location"]["line"]:
    return a["location"]["column"] - b["location"]["column"]
  else:
    return a["location"]["line"] - b["location"]["line"]

def insert_buginfo_2html(html_file, bug_info, bug_index):
  fin = open(html_file, "r")
  html_doc = fin.read()
  fin.close()

  soup = BeautifulSoup(html_doc, "html.parser")
  node = soup.find(id = str(bug_info["location"]["line"]))
  if node != None:
    line_num = str(bug_info["location"]["line"])
    column_num = str(bug_info["location"]["column"])
    offset = bug_info["location"]["column"] - 2
    if bug_info["location"].get("relativeLoc") == None:
      node.insert_before(BeautifulSoup('''<tr><td></td><td class="bug_info"><div style="margin-left:''' + str(offset) + '''ch;">''' + '''<div class="bug_info_text"><span class="bug_index">''' 
              + str(bug_index) + '''</span>''' + bug_info["type"] + "(" + line_num + ":" + column_num + "): " + bug_info["description"]
              + '''</div></div></td></tr>''', "html.parser"))
    else:
      node.insert_before(BeautifulSoup('''<tr><td></td><td class="bug_info"><div style="margin-left:''' + str(offset) + '''ch;">''' + '''<div class="bug_info_text"><span class="bug_index">''' 
              + str(bug_index) + '''</span>''' + bug_info["type"] + "(" + line_num + ":" + column_num + "): " + bug_info["description"]
              + " (see: " + bug_info["location"]["relativeLoc"]["file"] + ":" + str(bug_info["location"]["relativeLoc"]["line"]) + ":" + str(bug_info["location"]["relativeLoc"]["column"]) + ")"
              + '''</div></div></td></tr>''', "html.parser"))

  with open(html_file, "w") as fout:
    # fout.write(soup.prettify())
    fout.write(str(soup))

def parse_json_report(project_root, report_root):
  errs_map = {}
  report_dir = os.path.join(report_root, json_report_file)
  with open(report_dir, "r") as fin:
    data = json.load(fin)
    if data == None:
      return
    for item in data:
      key = item["location"]["file"]
      if not errs_map.has_key(key):
        errs_map[key] = []
      errs_map[key].append(item)

  for source_path, v in errs_map.items():
    relvpath = source_path[-(len(source_path) - len(project_root)):]
    filename = os.path.basename(relvpath)
    html_path = os.path.join(report_root, html_report_dir, relvpath) + ".html"
    html_dir = os.path.dirname(html_path)

    if not os.path.exists(html_dir):
      os.makedirs(html_dir)
    create_html_file(report_root, source_path, html_path, filename)

    v.sort(cmp)
    bug_index = 0
    for buginfo in v:
      bug_index = bug_index + 1
      insert_buginfo_2html(html_path, buginfo, bug_index)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("-d", default=None, help="report path")
  args = parser.parse_args()

  report_root = args.d
  project_root = get_project_root(db_path)

  create_css_files(report_root)
  read_all_json_files(project_root, report_root)
  create_html_index(project_root, report_root)
  parse_json_report(project_root, report_root)

if __name__ == '__main__':
  main()