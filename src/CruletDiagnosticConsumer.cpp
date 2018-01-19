#include "CruletDiagnosticConsumer.h"
#include "clang/Tooling/Tooling.h"

namespace clang {
namespace crulet {

void CruletDiagnosticConsumer::HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info){
  TextDiagnosticPrinter::HandleDiagnostic(DiagLevel, Info);
  // llvm::errs() << "---------------- Info.getID() = " << Info.getID() << " ---------------\n";
}

} // namespace crulet
} // namespace clang