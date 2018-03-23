#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

namespace clang {
namespace crulet {

CruletChecker::CruletChecker(CruletContext *Context, 
    StringRef CheckerName, StringRef ReportMsg, 
    DiagnosticIDs::Level DiagLevel) {
  this->Context = Context;
  this->CheckerName = CheckerName;
  this->ReportMsg = ReportMsg;
  this->DiagLevel = DiagLevel;
}

CruletChecker::~CruletChecker(){

}

CruletContext* CruletChecker::getCruletContext(){
  return Context;
}

StringRef CruletChecker::getReportMsg(){
  return ReportMsg;
}

StringRef CruletChecker::getName(){
  return CheckerName;
}

DiagnosticIDs::Level CruletChecker::getDiagLevel(){
  return DiagLevel;
}

} // namespace crulet
} // namespace clang
