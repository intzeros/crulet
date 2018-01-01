#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletModule.h"
#include "CruletChecker.h"
#include <map>
#include <vector>

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

vector<string> CruletModule::getCheckerNames(){
  vector<string> rst;
  for(const auto &kvp : CheckerMap){
    rst.push_back(ModuleName + "-" + kvp.first);
  }
  return rst;
}

StringRef CruletModule::getName(){
  return ModuleName;
}

} // namespace crulet
} // namespace clang