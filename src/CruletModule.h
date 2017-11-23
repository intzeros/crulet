#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_MODULE_H

#include "CruletChecker.h"
#include <map>
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
namespace crulet {

class CruletModule {
public:
  CruletModule(StringRef ModuleName)
      : ModuleName(ModuleName) {}
  virtual ~CruletModule() {
    for(auto Checker : CheckerMap){
      delete Checker.second;
    }
  }

  virtual void registerCheckers(ast_matchers::MatchFinder *Finder) = 0;

protected:
  template <class CheckerType>
  CruletChecker* registerChecker(StringRef CheckerName){
    if(CheckerMap.find(CheckerName) == CheckerMap.end()){
      CheckerMap[CheckerName] = new CheckerType(CheckerName);
    }
    return CheckerMap[CheckerName];
  }

protected:
  std::string ModuleName;
  std::map<std::string, CruletChecker*> CheckerMap;
};

} // namespace crulet
} // namespace clang

#endif