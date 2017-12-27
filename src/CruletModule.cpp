#include "CruletModule.h"
#include "CruletChecker.h"
#include <map>
#include <vector>
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

using namespace clang;
using namespace std;

namespace clang {
namespace crulet {

CruletModule::CruletModule(CruletContext *Context, StringRef ModuleName){
  this->Context = Context;
  this->ModuleName = ModuleName;
}

CruletModule::~CruletModule() {
  for(auto &kvp : CheckerMap){
    if(kvp.second != nullptr){
      delete kvp.second;
    }
  }
}

// template <typename CheckerType>
// void CruletModule::registerChecker(StringRef CheckerName, ast_matchers::MatchFinder *Finder){
//   if(Context->isCheckerEnabled(ModuleName, CheckerName)){
//     createChecker<CheckerType>(CheckerName)->registerMatchers(Finder);
//   }
// }

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