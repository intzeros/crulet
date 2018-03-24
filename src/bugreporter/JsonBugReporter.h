#ifndef CRULET_JSON_BUG_REPORTER_H
#define CRULET_JSON_BUG_REPORTER_H

// #include "BugReporter.h"
#include "../CruletContext.h"
#include "../exlibs/json.hpp"
#include <fstream>

namespace clang {
namespace crulet {

class CruletContext;

// class JsonBugReporter : public BugReporter {
class JsonBugReporter {
public:
  JsonBugReporter(CruletContext* Context){
    this->Context = Context;
  }
  ~JsonBugReporter();

  void setOutputFile(std::string filename);

  void report(std::string CheckerName, std::string Msg, 
                       SourceManager &SM, SourceLocation Loc, 
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning);

  void report(std::string CheckerName, std::string Msg, 
                       SourceManager &SM, SourceLocation Loc, SourceLocation RelativeLoc,
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning);

private:
  std::string getFilePath(std::string Dir, std::string Name);

private:
  CruletContext* Context;
  std::string filename;
  std::ofstream JsonOFS;
  nlohmann::json Json;
};

} // namespace crulet
} // namespace clang

#endif