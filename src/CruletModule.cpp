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