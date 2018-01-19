#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_DIAG_CONSUMER_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_DIAG_CONSUMER_H

#include "clang/Frontend/TextDiagnosticPrinter.h"

namespace clang {
namespace crulet {

class CruletDiagnosticConsumer : public TextDiagnosticPrinter {
public:
  CruletDiagnosticConsumer(raw_ostream &os, DiagnosticOptions *diags, bool OwnsOutputStream = false)
    : TextDiagnosticPrinter(os, diags, OwnsOutputStream) {}

  void HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info) override;
};

} // namespace crulet
} // namespace clang


#endif