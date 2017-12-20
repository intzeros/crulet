#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "GJBModule.h"
#include "../../CruletChecker.h"
#include "Rule_4_3_1_1.h"
#include "Rule_4_3_1_2.h"
#include "Rule_4_3_1_3.h"
#include "Rule_4_3_1_4.h"
#include "Rule_4_3_1_5.h"
#include "Rule_4_3_1_6.h"
#include "Rule_4_3_1_7.h"
#include "Rule_4_3_1_8.h"
#include "Rule_4_4_1_2.h"
#include "Rule_4_4_1_3.h"
#include "Rule_4_5_1_1.h"
#include "Rule_4_5_1_2.h"
#include "Rule_4_6_1_1.h"
#include "Rule_4_6_1_3.h"
#include "Rule_4_6_1_4.h"
#include "Rule_4_6_1_5.h"
#include "Rule_4_6_1_6.h"
#include "Rule_4_6_1_7.h"
#include "Rule_4_6_1_11.h"
#include "Rule_4_6_1_12.h"
#include "Rule_4_6_1_15.h"
#include "Rule_4_6_1_16.h"
#include "Rule_4_6_1_17.h"
#include "Rule_4_6_1_18.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(MatchFinder *Finder){
  this->registerChecker<Rule_4_3_1_1>("GJB-Rule-4.3.1.1")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_2>("GJB-Rule-4.3.1.2")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_3>("GJB-Rule-4.3.1.3")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_4>("GJB-Rule-4.3.1.4")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_5>("GJB-Rule-4.3.1.5")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_6>("GJB-Rule-4.3.1.6")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_7>("GJB-Rule-4.3.1.7")->registerMatchers(Finder);
  this->registerChecker<Rule_4_3_1_8>("GJB-Rule-4.3.1.8")->registerMatchers(Finder);

  this->registerChecker<Rule_4_4_1_2>("GJB-Rule-4.4.1.2")->registerMatchers(Finder);
  this->registerChecker<Rule_4_4_1_3>("GJB-Rule-4.4.1.3")->registerMatchers(Finder);

  this->registerChecker<Rule_4_5_1_1>("GJB-Rule-4.5.1.1")->registerMatchers(Finder);
  this->registerChecker<Rule_4_5_1_2>("GJB-Rule-4.5.1.2")->registerMatchers(Finder);

  this->registerChecker<Rule_4_6_1_1>("GJB-Rule-4.6.1.1")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_3>("GJB-Rule-4.6.1.3")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_4>("GJB-Rule-4.6.1.4")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_5>("GJB-Rule-4.6.1.5")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_6>("GJB-Rule-4.6.1.6")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_7>("GJB-Rule-4.6.1.7")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_11>("GJB-Rule-4.6.1.11")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_12>("GJB-Rule-4.6.1.12")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_15>("GJB-Rule-4.6.1.15")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_16>("GJB-Rule-4.6.1.16")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_17>("GJB-Rule-4.6.1.17")->registerMatchers(Finder);
  this->registerChecker<Rule_4_6_1_18>("GJB-Rule-4.6.1.18")->registerMatchers(Finder);
}

} // namespace GJB
} // namespace crulet
} // namespace clang