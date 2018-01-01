#include "Crulet.h"
#include "modules/gjb/GJBModule.h"

namespace clang {
namespace crulet {

CruletManager::CruletManager(CruletContext *Context) {
  this->Context = Context;
}

CruletManager::~CruletManager(){
  for(const auto& kvp : ModuleMap){
    if(kvp.second != nullptr){
      delete kvp.second;
    }
  }
}

void CruletManager::registerModules(ast_matchers::MatchFinder *Finder){
  this->registerModule<clang::crulet::GJB::GJBModule>("GJB")->registerCheckers(Finder);
}

std::vector<std::string> CruletManager::getCheckerNames(StringRef ModuleName){
  if(ModuleMap.find(ModuleName) != ModuleMap.end()){
    return ModuleMap[ModuleName]->getCheckerNames();
  }else{
    return std::vector<std::string>();
  }
}

std::vector<std::string> CruletManager::getModuleNames(){
  std::vector<std::string> rst;
  for(const auto &kvp : ModuleMap){
    rst.push_back(kvp.first);
  }
  return rst;
}

} // namespace crulet
} // namespace clang