#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_DIAG_CONSUMER_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_DIAG_CONSUMER_H

#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "CruletContext.h"

namespace clang {
namespace crulet {

class CruletDiagnosticConsumer : public TextDiagnosticPrinter {
public:
  CruletDiagnosticConsumer(CruletContext* Context, raw_ostream &os, DiagnosticOptions *diags, bool OwnsOutputStream = false)
    : TextDiagnosticPrinter(os, diags, OwnsOutputStream) {
      this->Context = Context;
  }

  void HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info) override;

private:
  CruletContext* Context;
};

} // namespace crulet
} // namespace clang


#endif