#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletModule.h"
#include "CruletChecker.h"
#include <map>
#include <vector>

using namespace clang;
using namespace std;

namespace clang {
namespace crulet {

CruletModule::~CruletModule() {
  for(auto &kvp : CheckerMap){
    if(kvp.second != nullptr){
      delete kvp.second;
    }
  }
}

void CruletModule::addCheckerActions(CompilerInstance &CI, ast_matchers::MatchFinder *Finder){
  for(auto &kvp : CheckerMap){
    kvp.second->registerPPCallbacks(CI);
    kvp.second->registerMatchers(Finder);
  }
}

vector<string> CruletModule::getCheckerNames(){
  vector<string> rst;
  for(const auto &kvp : CheckerMap){
    rst.push_back(kvp.first);
  }
  return rst;
}

StringRef CruletModule::getName(){
  return ModuleName;
}

} // namespace crulet
} // namespace clang