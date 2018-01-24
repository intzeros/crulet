#include "Rule_1_1_12.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_1_1_12 : public PPCallbacks {
public:
  PPCallbacks_1_1_12() {}

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override {

  }
};
}

void Rule_1_1_12::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_1_1_12>());
}

} // namespace GJB
} // namespace crulet
} // namespace clang
