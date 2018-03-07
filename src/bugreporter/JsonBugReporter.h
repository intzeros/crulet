#ifndef CRULET_JSON_BUG_REPORTER_H
#define CRULET_JSON_BUG_REPORTER_H

#include "../exlibs/json.hpp"
#include "BugReporter.h"
#include <fstream>

namespace clang {
namespace crulet {

class JsonBugReporter : public BugReporter {
public:
  ~JsonBugReporter() {}

  void create(std::string filename);
  void close();

  void addElement(std::string CheckerName, std::string Msg, 
                       DiagnosticsEngine &DE, SourceManager &SM, SourceLocation Loc, 
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning);
private:
  std::ofstream JsonOFS;
  nlohmann::json Json;
};

} // namespace crulet
} // namespace clang

#endif