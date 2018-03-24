#ifndef CRULET_BUG_REPORTER_H
#define CRULET_BUG_REPORTER_H

#include "clang/Basic/Diagnostic.h"
#include "../CruletContext.h"

namespace clang {
namespace crulet {

class CruletContext;

class BugReporter {
public:
  BugReporter(CruletContext* Context)
    : Context(Context) {}
  virtual ~BugReporter() {}

  virtual void report(std::string CheckerName, std::string Msg, 
                       SourceManager &SM, SourceLocation Loc, 
                       DiagnosticIDs::Level Level = DiagnosticIDs::Warning) {}

protected:
  CruletContext* Context;
};

} // namespace crulet
} // namespace clang

#endif