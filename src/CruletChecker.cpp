#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

namespace clang {
namespace crulet {

CruletChecker::CruletChecker(CruletContext *Context, StringRef CheckerName, StringRef ReportMsg){
  this->Context = Context;
  this->CheckerName = CheckerName;
  this->ReportMsg = ReportMsg;
}

CruletChecker::~CruletChecker(){
    
}

StringRef CruletChecker::getName(){
  return CheckerName;
}

} // namespace crulet
} // namespace clang
