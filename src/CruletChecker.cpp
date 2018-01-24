#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

namespace clang {
namespace crulet {

CruletContext* CruletChecker::getCruletContext(){
  return Context;
}

StringRef CruletChecker::getReportMsg(){
  return ReportMsg;
}

StringRef CruletChecker::getName(){
  return CheckerName;
}

} // namespace crulet
} // namespace clang
