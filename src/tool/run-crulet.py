#!/usr/bin/python

import os
import sys
import json
import signal
import argparse

def quit():
  sys.exit(0)

def main():
  db_path = "compile_commands.json"

  parser = argparse.ArgumentParser()
  parser.add_argument("-check", default=None, help="checkers filter")
  parser.add_argument("-f", default=None, help="output file")
  args = parser.parse_args()

  with open(db_path, "r") as fin:
    data = json.load(fin)
    for item in data:
      file = ""
      if item["file"][0] != '/':
        n = len(item["directory"])
        if item["directory"][n-1] == '/':
          file = item["directory"] + item["file"]
        else:
          file = item["directory"] + "/" + item["file"]
      else:
        file = item["file"]

      command = "crulet"
      if args.check:
        command = command + " -check=" + args.check + " " + file
      else:
        command = command + " " + file

      print "\n" + command

      if args.f:
        os.system("echo '\n" + command + "' >> " + args.f)
        code = os.system(command + " >> " + args.f)
      else:
        code = os.system(command)

      if code == signal.SIGINT:  # Ctrl-C
        sys.exit(1)

if __name__ == '__main__':
  main()