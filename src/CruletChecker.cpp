#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CruletChecker.h"

namespace clang {
namespace crulet {

StringRef CruletChecker::getName(){
  return CheckerName;
}

} // namespace crulet
} // namespace clang
