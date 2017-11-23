#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "GJBModule.h"
#include "../../CruletChecker.h"
#include "Rule_4_3_1_4.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(MatchFinder *Finder){
  this->registerChecker<Rule_4_3_1_4>("GJB-Rule-4.3.1.4")->registerMatchers(Finder);
}

} // namespace GJB
} // namespace crulet
} // namespace clang