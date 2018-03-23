#include "Rule_1_1_13.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_1_1_13 : public PPCallbacks {
public:
  PPCallbacks_1_1_13(Preprocessor *PP, Rule_1_1_13 *Checker)
      : PP(PP), Checker(Checker) {}

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override {
    SourceLocation SL = MacroNameTok.getLocation(); 
    SourceManager &SM = PP->getSourceManager();
    if(SM.isInMainFile(SL) && !SM.isInSystemHeader(SL)){
      const auto *Info = MD->getMacroInfo();
      unsigned NumKeywords = 0;
      for(auto it = Info->tokens_begin(); it != Info->tokens_end(); ++it){
        if(it->isAnyIdentifier() && it->getIdentifierInfo()->isKeyword(PP->getLangOpts())){
          NumKeywords++;
        }
      }

      if(NumKeywords == Info->getNumTokens()){
        DiagnosticsEngine &DE = PP->getDiagnostics();
        auto *Context = Checker->getCruletContext();
        StringRef ReportMsg = Checker->getReportMsg();
        StringRef CheckerName = Checker->getName();
        DiagnosticIDs::Level DiagLevel = Checker->getDiagLevel();
        Context->report(CheckerName, ReportMsg, DE, SL, DiagLevel);
        Context->getJsonBugReporter().report(CheckerName, ReportMsg, SM, SL, DiagLevel);
      }
    }
  }

private:
  Preprocessor *PP;
  Rule_1_1_13 *Checker;
};
} // namespace

void Rule_1_1_13::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_1_1_13>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
