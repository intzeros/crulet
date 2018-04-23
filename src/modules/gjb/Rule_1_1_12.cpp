#include "Rule_1_1_12.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "stack"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_1_1_12 : public PPCallbacks {
public:
  PPCallbacks_1_1_12(Preprocessor *PP, Rule_1_1_12 *Checker)
      : PP(PP), Checker(Checker) {}

  bool checkBraceMatching(const MacroInfo* Info){
    std::stack<char> stk;

    for (auto it = Info->tokens_begin(); it != Info->tokens_end(); ++it) {
      if(it->getKind() == tok::TokenKind::l_brace){
        stk.push('{');
      }else if(it->getKind() == tok::TokenKind::r_brace){
        if(stk.empty()){
          return false;
        }else{
          stk.pop();
        }
      }
    }
    return stk.empty();
  }

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override {
    SourceManager &SM = PP->getSourceManager();
    SourceLocation SL = MD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Info = MD->getMacroInfo();
    if(!Info->isFunctionLike()){
      return;
    }

    if(!checkBraceMatching(Info)){
      DiagnosticsEngine &DE = PP->getDiagnostics();
      auto *Context = Checker->getCruletContext();
      StringRef ReportMsg = Checker->getReportMsg();
      StringRef CheckerName = Checker->getName();
      DiagnosticIDs::Level DiagLevel = Checker->getDiagLevel();
      Context->report(CheckerName, ReportMsg, DE, Info->getDefinitionLoc(), DiagLevel);
      Context->getJsonBugReporter().report(CheckerName, ReportMsg, SM, Info->getDefinitionLoc(), DiagLevel);
    }
  }

private:
  Preprocessor *PP;
  Rule_1_1_12 *Checker;
};
} // namespace

void Rule_1_1_12::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_1_1_12>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
