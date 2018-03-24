#include "CruletContext.h"

namespace clang {
namespace crulet {

CruletContext::CruletContext() {
  JsonReporter = new JsonBugReporter(this);
}

CruletContext::~CruletContext() {
  if(JsonReporter != nullptr){
    delete JsonReporter;
  }
}

bool CruletContext::isCheckerEnabled(StringRef CheckerName){
  return Options.isCheckerEnabled(CheckerName);
}

CruletOptions &CruletContext::getOptions() {
  return Options;
}

JsonBugReporter &CruletContext::getJsonBugReporter() {
  return *JsonReporter;
}

void CruletContext::setBuildDirectory(std::string BuildDirectory){
  this->BuildDirectory = BuildDirectory;
}

std::string CruletContext::getBuildDirectory(){
  return BuildDirectory;
}

void CruletContext::setCurrentFile(std::string FileName){
  this->CurrentFile = FileName;
}

std::string CruletContext::getCurrentFile(){
  return CurrentFile;
}

DiagnosticBuilder CruletContext::report(std::string CheckerName, std::string Msg, 
    DiagnosticsEngine &DE, SourceLocation Loc, 
    DiagnosticIDs::Level Level){

  Msg = "[" + CheckerName + "] " + Msg;
  unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(Level, Msg);
  return DE.Report(Loc, DiagID);
}

} // namespace crulet
} // namespace clang