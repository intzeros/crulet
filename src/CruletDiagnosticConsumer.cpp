#include "CruletDiagnosticConsumer.h"
#include "clang/Tooling/Tooling.h"

namespace clang {
namespace crulet {

void CruletDiagnosticConsumer::HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info){
  TextDiagnosticPrinter::HandleDiagnostic(DiagLevel, Info);
  // llvm::errs() << "---------------- Info.getID() = " << Info.getID() << " ---------------\n";

  if(Info.getID() == 3196u && Context->isCheckerEnabled("GJB-rule-1.1.7")){    // GJB-rule-1.1.7
    // DiagnosticsEngine &DE = Info.getSourceManager().getDiagnostics();
    // Context->report("GJB-rule-1.1.7", "禁止过程参数只有类型没有标识符", DE, Info.getLocation(), DiagnosticIDs::Warning);
    llvm::errs() << "[GJB-rule-1.1.7] 禁止过程参数只有类型没有标识符\n\n";
  }
}

} // namespace crulet
} // namespace clang