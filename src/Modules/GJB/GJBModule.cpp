#include "GJBModule.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
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
#include "Rule_4_8_1_1.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(MatchFinder *Finder){
  this->registerChecker<Rule_4_3_1_1>("GJB-rule-4.3.1.1", Finder);
  this->registerChecker<Rule_4_3_1_2>("GJB-rule-4.3.1.2", Finder);
  this->registerChecker<Rule_4_3_1_3>("GJB-rule-4.3.1.3", Finder);
  this->registerChecker<Rule_4_3_1_4>("GJB-rule-4.3.1.4", Finder);
  this->registerChecker<Rule_4_3_1_5>("GJB-rule-4.3.1.5", Finder);
  this->registerChecker<Rule_4_3_1_6>("GJB-rule-4.3.1.6", Finder);
  this->registerChecker<Rule_4_3_1_7>("GJB-rule-4.3.1.7", Finder);
  this->registerChecker<Rule_4_3_1_8>("GJB-rule-4.3.1.8", Finder);

  this->registerChecker<Rule_4_4_1_2>("GJB-rule-4.4.1.2", Finder);
  this->registerChecker<Rule_4_4_1_3>("GJB-rule-4.4.1.3", Finder);

  this->registerChecker<Rule_4_5_1_1>("GJB-rule-4.5.1.1", Finder);
  this->registerChecker<Rule_4_5_1_2>("GJB-rule-4.5.1.2", Finder);

  this->registerChecker<Rule_4_6_1_1>("GJB-rule-4.6.1.1", Finder);
  this->registerChecker<Rule_4_6_1_3>("GJB-rule-4.6.1.3", Finder);
  this->registerChecker<Rule_4_6_1_4>("GJB-rule-4.6.1.4", Finder);
  this->registerChecker<Rule_4_6_1_5>("GJB-rule-4.6.1.5", Finder);
  this->registerChecker<Rule_4_6_1_6>("GJB-rule-4.6.1.6", Finder);
  this->registerChecker<Rule_4_6_1_7>("GJB-rule-4.6.1.7", Finder);
  this->registerChecker<Rule_4_6_1_11>("GJB-rule-4.6.1.11", Finder);
  this->registerChecker<Rule_4_6_1_12>("GJB-rule-4.6.1.12", Finder);
  this->registerChecker<Rule_4_6_1_15>("GJB-rule-4.6.1.15", Finder);
  this->registerChecker<Rule_4_6_1_16>("GJB-rule-4.6.1.16", Finder);
  this->registerChecker<Rule_4_6_1_17>("GJB-rule-4.6.1.17", Finder);
  this->registerChecker<Rule_4_6_1_18>("GJB-rule-4.6.1.18", Finder);

  this->registerChecker<Rule_4_8_1_1>("GJB-rule-4.8.1.1", Finder);
}

} // namespace GJB
} // namespace crulet
} // namespace clang