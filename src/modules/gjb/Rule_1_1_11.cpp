#include "Rule_1_1_11.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_1_1_11 : public PPCallbacks {
public:
  PPCallbacks_1_1_11(Preprocessor *PP, Rule_1_1_11 *Checker)
      : PP(PP), Checker(Checker) {}

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override {
    SourceLocation SL = MacroNameTok.getLocation(); 
    SourceManager &SM = PP->getSourceManager();
    if(SM.isInMainFile(SL) && !SM.isInSystemHeader(SL)){
      const auto *Info = MD->getMacroInfo();
      unsigned Count1 = 0, Count2 = 0;
      for(auto it = Info->tokens_begin(); it != Info->tokens_end(); ++it){
        if(it->getKind() == tok::hash){   // "#"
          Count1++;
        }else if(it->getKind() == tok::hashhash){ // "##"
          Count2++;
        }
      }

      if(Count1 > 1 || Count2 > 1 || (Count1 >= 1 && Count2 >= 1)){
        DiagnosticsEngine &DE = PP->getDiagnostics();
        auto *Context = Checker->getCruletContext();
        StringRef ReportMsg = Checker->getReportMsg();
        StringRef CheckerName = Checker->getName();
        Context->report(CheckerName, ReportMsg, DE, SL, DiagnosticIDs::Warning);
      }
    }
  }

private:
  Preprocessor *PP;
  Rule_1_1_11 *Checker;
};
} // namespace

void Rule_1_1_11::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_1_1_11>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
