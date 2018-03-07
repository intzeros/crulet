#include "CruletContext.h"

namespace clang {
namespace crulet {

CruletContext::CruletContext(){
  JsonReporter = nullptr;
}

CruletContext::~CruletContext(){
  if(JsonReporter != nullptr){
    JsonReporter->close();
    delete JsonReporter;
  }
}

bool CruletContext::isCheckerEnabled(StringRef CheckerName){
  return Options.isCheckerEnabled(CheckerName);
}

CruletOptions &CruletContext::getOptions() {
  return Options;
}

void CruletContext::setJsonBugReporter(std::string filename){
  if(JsonReporter == nullptr){
    JsonReporter = new JsonBugReporter();
    JsonReporter->create(filename);
  }
}

JsonBugReporter* CruletContext::getJsonBugReporter() {
  return JsonReporter;
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