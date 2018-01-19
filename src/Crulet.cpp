#include "Crulet.h"
#include "modules/gjb/GJBModule.h"

namespace clang {
namespace crulet {

CruletManager::~CruletManager(){
  for(const auto& kvp : ModuleMap){
    if(kvp.second != nullptr){
      delete kvp.second;
    }
  }
}

void CruletManager::registerModules(){
  this->registerModule<clang::crulet::GJB::GJBModule>("GJB")->registerCheckers();
}

void CruletManager::addCheckerActions(CompilerInstance &CI, ast_matchers::MatchFinder *Finder){
  for(auto &kvp : ModuleMap){
    kvp.second->addCheckerActions(CI, Finder);
  }
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

ast_matchers::MatchFinder &CruletManager::getMatchFinder(){
  return this->Finder;
}

CruletContext *CruletManager::getCruletContext(){
  return this->Context;
}


} // namespace crulet
} // namespace clang