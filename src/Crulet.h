#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_H

#include "CruletModule.h"
#include "CruletChecker.h"
#include "CruletContext.h"
#include <map>
#include <vector>

namespace clang {
namespace crulet {

class CruletManager {
public:
  CruletManager(CruletContext *Context);
  ~CruletManager();
 
  void registerModules(ast_matchers::MatchFinder *Finder);

  std::vector<std::string> getCheckerNames(StringRef ModuleName);
  std::vector<std::string> getModuleNames();

private:
  template <typename ModuleType>
  CruletModule* registerModule(StringRef ModuleName){
    if(ModuleMap.find(ModuleName) == ModuleMap.end()){
      ModuleMap[ModuleName] = new ModuleType(Context, ModuleName);
    }
    return ModuleMap[ModuleName];
  }

private:
  std::map<std::string, CruletModule*> ModuleMap;
  CruletContext *Context;
};

} // namespace crulet
} // namespace clang


#endif