#include "CruletContext.h"

namespace clang {
namespace crulet {

bool CruletContext::isCheckerEnabled(StringRef CheckerName){
  return Options.isCheckerEnabled(CheckerName);
}

CruletOptions &CruletContext::getOptions() {
  return Options;
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