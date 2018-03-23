#ifndef CRULET_JSON_BUG_REPORTER_H
#define CRULET_JSON_BUG_REPORTER_H

#include "../exlibs/json.hpp"
#include "BugReporter.h"
#include <fstream>

namespace clang {
namespace crulet {

class JsonBugReporter : public BugReporter {
public:
  JsonBugReporter();
  ~JsonBugReporter();

  void setOutputFile(std::string filename);

  void report(std::string CheckerName, std::string Msg, 
                       SourceManager &SM, SourceLocation Loc, 
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning) override;
private:
  std::string filename;
  std::ofstream JsonOFS;
  nlohmann::json Json;
};

} // namespace crulet
} // namespace clang

#endif