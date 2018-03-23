#include "CruletDiagnosticConsumer.h"
#include "clang/Tooling/Tooling.h"

namespace clang {
namespace crulet {

void CruletDiagnosticConsumer::HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info){
  TextDiagnosticPrinter::HandleDiagnostic(DiagLevel, Info);
  // llvm::errs() << "---------------- Info.getID() = " << Info.getID() << " ---------------\n";

  if(Info.getID() == 3196u && Context->isCheckerEnabled("GJB-1.1.7")){    // GJB-1.1.7
    // DiagnosticsEngine &DE = Info.getSourceManager().getDiagnostics();
    // Context->report("GJB-1.1.7", "禁止过程参数只有类型没有标识符", DE, Info.getLocation(), DiagnosticIDs::Warning);
    llvm::errs() << "[GJB-1.1.7] 禁止过程参数只有类型没有标识符\n\n";
  }
  else if(Info.getID() == 1189u && Context->isCheckerEnabled("GJB-2.1.1")){    // GJB-2.1.1
    llvm::errs() << "[GJB-2.1.1] 过程体必须用大括号括起来\n\n";
  }
  else if(Info.getID() == 1963u && Context->isCheckerEnabled("GJB-6.1.10")){    // GJB-6.1.10
    llvm::errs() << "[GJB-6.1.10] 数组下标必须是整型数\n\n";
  }
  else if(Info.getID() == 795u && Context->isCheckerEnabled("GJB-1.1.18")){    // GJB-1.1.18
    llvm::errs() << "[GJB-1.1.18] 禁止在同一个文件中有#if而没有#endif\n\n";
  }
}

} // namespace crulet
} // namespace clang