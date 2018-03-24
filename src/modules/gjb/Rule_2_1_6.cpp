#include "Rule_2_1_6.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include <unordered_set>

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_2_1_6 : public PPCallbacks {
public:
  PPCallbacks_2_1_6(Preprocessor *PP, Rule_2_1_6 *Checker)
      : PP(PP), Checker(Checker) {}

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override {
    SourceManager &SM = PP->getSourceManager();
    SourceLocation SL = MD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const auto *Info = MD->getMacroInfo();
    if(Info->isFunctionLike() && !Info->param_empty()){
      std::unordered_set<std::string> ParamSet;
      for(auto it = Info->param_begin(); it != Info->param_end(); ++it){
        ParamSet.insert((*it)->getName());
      }

      DiagnosticsEngine &DE = PP->getDiagnostics();
      auto *Context = Checker->getCruletContext();
      StringRef ReportMsg = Checker->getReportMsg();
      StringRef CheckerName = Checker->getName();
      DiagnosticIDs::Level DiagLevel = Checker->getDiagLevel();

      bool HasReported = false;
      for (auto it = Info->tokens_begin(); !HasReported && it != Info->tokens_end(); ++it) {
        if(it->isAnyIdentifier()){
          std::string Name = it->getIdentifierInfo()->getName();
          if(ParamSet.find(Name) != ParamSet.end()){
            if(it != Info->tokens_begin() && it + 1 != Info->tokens_end()){
              auto pre = it - 1;
              auto next = it + 1;
              if(pre->getKind() != tok::l_paren || next->getKind() != tok::r_paren){
                Context->report(CheckerName, ReportMsg, DE, it->getLocation(), DiagLevel);
                Context->getJsonBugReporter().report(CheckerName, ReportMsg, SM, it->getLocation(), DiagLevel);
              }
              HasReported = true;
            }else{
              Context->report(CheckerName, ReportMsg, DE, it->getLocation(), DiagLevel);
              Context->getJsonBugReporter().report(CheckerName, ReportMsg, SM, it->getLocation(), DiagLevel);
            }
            HasReported = true;
          }
        }
      }
    }
  }

private:
  Preprocessor *PP;
  Rule_2_1_6 *Checker;
};
} // namespace

void Rule_2_1_6::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_2_1_6>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
