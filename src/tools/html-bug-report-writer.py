#!/usr/bin/python

import os
import json
import cgi
import argparse
import sys
from bs4 import BeautifulSoup

reload(sys) 
sys.setdefaultencoding('utf-8')

db_path = "compile_commands.json"
json_report_dir = "report/json/"
html_report_dir = "report/html/"
json_report_file = "report/report.json"
html_report_file = "report/index.html"

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
              '''<link rel="stylesheet" type="text/css" href="index.css">\n''' +
              '''<title>Crulet analysis results</title>\n</head>\n''' +
              '''<body>\n<h1>Crulet Analysis Results</h1>\n<h2>General Information</h2>\n''')
  fout.write('''<h2>Summary</h2>\n<table>\n<tr><th>Bug Type</th><th>Quantity</th><th>Display</th></tr>\n''')
  
  errs_counts = {}
  with open(os.path.join(report_root, json_report_file), "r") as fin:
    data = json.load(fin)
    if data == None:
      return
    for item in data:
      if not errs_counts.has_key(item["type"]):
        errs_counts[item["type"]] = 0
      errs_counts[item["type"]] = errs_counts[item["type"]] + 1

  for k, v in errs_counts.items():
    fout.write('''<tr><td>''' + k + '''</td><td>''' + str(v) + '''</td><td>ok</td></tr>\n''')
  
  fout.write('''</table>\n''')
  fout.write('''<h2>Reports</h2>\n<table>\n<tr><td>Bug Type</td><td>Description</td><td>File</td><td>Line</td><td></td></tr>\n''')

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
def create_html_file(input_file, output_file, filename):
  fout = open(output_file, "w")
  fout.write('''<html>\n<head>\n<meta charset="UTF-8">\n''' + 
              '''<link rel="stylesheet" type="text/css" href="report.css">\n''' +
              '''<title>''' + filename + '''</title>\n</head>\n''' +
              '''<body>\n<table class="code">\n''')
  fin = open(input_file, "r")
  line_num = 0
  for line in fin.readlines():
    line_num = line_num + 1
    fout.write('''<tr>\n<td class="num" id="''')
    fout.write(str(line_num))
    fout.write('''">''')
    fout.write(str(line_num))
    fout.write('''</td>\n<td>''')
    fout.write(cgi.escape(line).replace(' ', '&nbsp;'))
    fout.write('''</td>\n</tr>\n''')

  fout.write('''</table>\n</body>\n</html>\n''')
  fout.close()

def cmp(a, b):
  if a["location"]["line"] == b["location"]["line"]:
    return a["location"]["column"] - b["location"]["column"]
  else:
    return a["location"]["line"] - b["location"]["line"]

def parse_json_report(project_root, report_root):
  # fout = open(os.path.join(report_root, html_report_file), "w")
  # fout.write('''<html>\n<head>\n<meta charset="UTF-8">\n''' + 
  #             '''<link rel="stylesheet" type="text/css" href="index.css">\n''' +
  #             '''<title>Crulet analysis results</title>\n</head>\n''' +
  #             '''<body>\n<h1>Crulet Analysis Results</h1>\n<h2>General Information</h2>\n''')
  # fout.write('''<h2>Summary</h2>\n''')
  # fout.write('''<h2>Reports</h2>\n''')

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
    create_html_file(source_path, html_path, filename)

    # v.sort(cmp)

  # fout.write('''</body>\n</html>\n''')
  # fout.close()

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("-d", default=None, help="report path")
  args = parser.parse_args()

  report_root = args.d
  project_root = get_project_root(db_path)

  read_all_json_files(project_root, report_root)
  create_html_index(project_root, report_root)
  parse_json_report(project_root, report_root)

if __name__ == '__main__':
  main()