#ifndef CRULET_BUG_REPORTER_H
#define CRULET_BUG_REPORTER_H

#include "clang/Basic/Diagnostic.h"

namespace clang {
namespace crulet {

class BugReporter {
public:
  virtual ~BugReporter() {}

  virtual void report(std::string CheckerName, std::string Msg, 
                       SourceManager &SM, SourceLocation Loc, 
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning) {}
};

} // namespace crulet
} // namespace clang

#endif