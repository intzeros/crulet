#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_GJB_MODULE_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_GJB_MODULE_H

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "../../CruletContext.h"
#include "../../CruletModule.h"

namespace clang {
namespace crulet {
namespace GJB {

class GJBModule : public CruletModule {
public:
  GJBModule(CruletContext *Context, StringRef ModuleName)
      : CruletModule(Context, ModuleName) {}
  ~GJBModule() {}

  void registerCheckers(ast_matchers::MatchFinder *Finder) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif