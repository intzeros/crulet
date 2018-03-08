#!/usr/bin/python

import os
import sys
import json
import signal
import argparse

db_path = "compile_commands.json"
json_report_dir = "report/json/"

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

# get relative path
def get_relative_path(base_path, path):
  pos = path.find(base_path)
  if pos != -1:
    return path[-(len(path) - len(base_path)):]
  else:
    return None

# preprocessing: return (project_base_dir, path_map)
def preprocessing(db_path):
  path_map = {}
  id = 0
  with open(db_path, "r") as fin:
    data = json.load(fin)
    for item in data:
      abspath = get_absolute_path(item["directory"], item["file"])
      if not path_map.has_key(abspath):
        id = id + 1
        path_map[abspath] = id

  project_base_dir = os.path.commonprefix(path_map.keys())
  return project_base_dir, path_map

# parse 'compile_commands.json' file
def parse_db(db_path, args, project_base_dir, path_map):
  with open(db_path, "r") as fin:
    data = json.load(fin)
    for item in data:
      abspath = get_absolute_path(item["directory"], item["file"])
      
      command = "crulet"
      if args.check:
        command = command + " -check=" + args.check + " " + abspath
      else:
        command = command + " " + abspath

      if args.p:
        command = command + " -p=" + args.p

      if args.d:
        relvpath = get_relative_path(project_base_dir, abspath)
        relvdir = os.path.dirname(relvpath)
        dir = os.path.join(args.d, json_report_dir, relvdir)
        if not os.path.exists(dir):
          os.makedirs(dir)
        # filename = os.path.join(dir, str(path_map[abspath]) + ".json")
        filename = os.path.join(dir, os.path.basename(abspath) + ".json")
        command = command + " -d=" + filename

      print "\n" + command

      if args.f:
        os.system("echo '\n" + command + "' >> " + args.f)
        code = os.system(command + " >> " + args.f)
      else:
        code = os.system(command)

      if code == signal.SIGINT:  # Ctrl-C
        sys.exit(1)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("-check", default=None, help="checkers filter")
  parser.add_argument("-f", default=None, help="output file")
  parser.add_argument("-d", default=None, help="report path")
  parser.add_argument("-p", default=None, help="build path")
  args = parser.parse_args()

  (project_base_dir, path_map) = preprocessing(db_path)
  parse_db(db_path, args, project_base_dir, path_map)
  

if __name__ == '__main__':
  main()