#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

namespace clang {
namespace crulet {

CruletChecker::CruletChecker(StringRef CheckerName){
  this->CheckerName = CheckerName;
}

CruletChecker::~CruletChecker(){
    
}

StringRef CruletChecker::getName(){
  return CheckerName;
}

} // namespace crulet
} // namespace clang