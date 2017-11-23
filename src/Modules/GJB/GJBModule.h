#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_GJB_MODULE_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_GJB_MODULE_H

#include "../../CruletModule.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
namespace crulet {
namespace GJB {

class GJBModule : public CruletModule {
public:
  GJBModule(StringRef ModuleName)
      : CruletModule(ModuleName) {}
  ~GJBModule() {}

  void registerCheckers(ast_matchers::MatchFinder *Finder) override;
};

// class GJBModule : public CruletModule {
// public:
//   void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
//     CheckFactories.registerCheck<SideEffectChecker>("readability-delete-null-pointer");
//   }
// };

// Register your module using this statically initialized variable.
// static llvm::Registry<CruletModule>::Add<GJBModule> X("GJB-module", "GJB rules for C.");

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif