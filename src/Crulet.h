#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_H

#include "CruletModule.h"
#include "CruletChecker.h"
#include <map>
#include <vector>
#include "CruletContext.h"
#include "CruletOptions.h"

namespace clang {
namespace crulet {

class CruletManager {
public:
  CruletManager(CruletContext *Context);
  virtual ~CruletManager();
 
  void registerModules(ast_matchers::MatchFinder *Finder);

  // template <typename ModuleType>
  // void registerChecker(StringRef ModuleName, StringRef CheckerName){
  //   if(ModuleMap.find(ModuleName) != ModuleMap.end()){
      
  //   }
  //   ModuleMap
  // }

  // template <typename ModuleType>
  // static void registerModule(StringRef ModuleName){
  //   this->registerModule<ModuleType>(ModuleName)->registerCheckers(&Finder);
  // }

  // ast_matchers::MatchFinder& getMatchFinder() const {
  //   return Finder;
  // }

  std::vector<std::string> getCheckerNames(StringRef ModuleName);
  std::vector<std::string> getModuleNames();

protected:
  template <typename ModuleType>
  CruletModule* registerModule(StringRef ModuleName){
    if(ModuleMap.find(ModuleName) == ModuleMap.end()){
      ModuleMap[ModuleName] = new ModuleType(Context, ModuleName);
    }
    return ModuleMap[ModuleName];
  }

protected:
  std::map<std::string, CruletModule*> ModuleMap;
  CruletContext *Context;
  // ast_matchers::MatchFinder Finder;
};

} // namespace crulet
} // namespace clang


#endif