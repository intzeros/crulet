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
#include "Rule_4_11_1_1.h"
#include "Rule_4_11_1_2.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(MatchFinder *Finder){
  this->registerChecker<Rule_4_3_1_1>("GJB-rule-4.3.1.1", "禁止条件判别成立时相应分支无执行语句", Finder);
  this->registerChecker<Rule_4_3_1_2>("GJB-rule-4.3.1.2", "在if...else if语句中必须使用else分支", Finder);
  this->registerChecker<Rule_4_3_1_3>("GJB-rule-4.3.1.3", "禁止条件判别的else分支无可执行语句", Finder);
  this->registerChecker<Rule_4_3_1_4>("GJB-rule-4.3.1.4", "在switch语句中必须有default语句", Finder);
  this->registerChecker<Rule_4_3_1_5>("GJB-rule-4.3.1.5", "禁止使用空switch语句", Finder);
  this->registerChecker<Rule_4_3_1_6>("GJB-rule-4.3.1.6", "禁止switch语句中只包含default语句", Finder);
  this->registerChecker<Rule_4_3_1_7>("GJB-rule-4.3.1.7", "禁止switch的case语句不是由break终止", Finder);
  this->registerChecker<Rule_4_3_1_8>("GJB-rule-4.3.1.8", "禁止switch的case语句中无任何可执行的语句", Finder);

  this->registerChecker<Rule_4_4_1_2>("GJB-rule-4.4.1.2", "禁止指针的指针超过两级", Finder);
  this->registerChecker<Rule_4_4_1_3>("GJB-rule-4.4.1.3", "禁止将过程声明为指针类型", Finder);

  this->registerChecker<Rule_4_5_1_1>("GJB-rule-4.5.1.1", "禁止直接从过程中跳出", Finder);
  this->registerChecker<Rule_4_5_1_2>("GJB-rule-4.5.1.2", "禁止使用goto语句", Finder);

  this->registerChecker<Rule_4_6_1_1>("GJB-rule-4.6.1.1", "禁止在非赋值表达式中出现赋值操作符", Finder);
  this->registerChecker<Rule_4_6_1_3>("GJB-rule-4.6.1.3", "禁止对有符号类型进行移位操作", Finder);
  this->registerChecker<Rule_4_6_1_4>("GJB-rule-4.6.1.4", "对变量进行移位运算必须保证不会产生溢出", Finder);
  this->registerChecker<Rule_4_6_1_5>("GJB-rule-4.6.1.5", "禁止给无符号变量赋负值", Finder);
  this->registerChecker<Rule_4_6_1_6>("GJB-rule-4.6.1.6", "有符号类型的位长度必须大于等于两位", Finder);
  this->registerChecker<Rule_4_6_1_7>("GJB-rule-4.6.1.7", "位的定义必须是有符号整数或无符号整数", Finder);
  this->registerChecker<Rule_4_6_1_11>("GJB-rule-4.6.1.11", "禁止对常数值做逻辑非的运算", Finder);
  this->registerChecker<Rule_4_6_1_12>("GJB-rule-4.6.1.12", "禁止对有符号类型进行移位操作", Finder);
  this->registerChecker<Rule_4_6_1_15>("GJB-rule-4.6.1.15", "禁止在逻辑表达式中使用赋值操作符", Finder);
  this->registerChecker<Rule_4_6_1_16>("GJB-rule-4.6.1.16", "禁止赋值操作符与\"&&\"或\"||\"连用", Finder);
  this->registerChecker<Rule_4_6_1_17>("GJB-rule-4.6.1.17", "禁止位操作符带有布尔型的操作数", Finder);
  this->registerChecker<Rule_4_6_1_18>("GJB-rule-4.6.1.18", "禁止位操作符作用于布尔值", Finder);

  this->registerChecker<Rule_4_8_1_1>("GJB-rule-4.8.1.1", "禁止单独使用小写字母\"l\"或大写字母\"O\"作为变量名", Finder);

  this->registerChecker<Rule_4_11_1_1>("GJB-rule-4.11.1.1", "禁止使用不合适的循环变量类型", Finder);
  this->registerChecker<Rule_4_11_1_2>("GJB-rule-4.11.1.2", "循环变量必须是局部声明的", Finder);
}

} // namespace GJB
} // namespace crulet
} // namespace clang