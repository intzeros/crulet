#include "GJBModule.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "Rule_1_1_1.h"
#include "Rule_1_1_2.h"
#include "Rule_1_1_4.h"
#include "Rule_1_1_6.h"
#include "Rule_1_1_7.h"
#include "Rule_1_1_8.h"
#include "Rule_1_1_9.h"
#include "Rule_3_1_1.h"
#include "Rule_3_1_2.h"
#include "Rule_3_1_3.h"
#include "Rule_3_1_4.h"
#include "Rule_3_1_5.h"
#include "Rule_3_1_6.h"
#include "Rule_3_1_7.h"
#include "Rule_3_1_8.h"
#include "Rule_4_1_2.h"
#include "Rule_4_1_3.h"
#include "Rule_5_1_1.h"
#include "Rule_5_1_2.h"
#include "Rule_6_1_1.h"
#include "Rule_6_1_3.h"
#include "Rule_6_1_4.h"
#include "Rule_6_1_5.h"
#include "Rule_6_1_6.h"
#include "Rule_6_1_7.h"
#include "Rule_6_1_11.h"
#include "Rule_6_1_12.h"
#include "Rule_6_1_15.h"
#include "Rule_6_1_16.h"
#include "Rule_6_1_17.h"
#include "Rule_6_1_18.h"
#include "Rule_8_1_1.h"
#include "Rule_11_1_1.h"
#include "Rule_11_1_2.h"
#include "Rule_12_1_1.h"
#include "Rule_13_1_1.h"
#include "Rule_13_1_2.h"
#include "Rule_13_1_4.h"
#include "Rule_14_1_1.h"
#include "Rule_14_1_2.h"
#include "Rule_14_1_3.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(MatchFinder *Finder){
  this->registerChecker<Rule_1_1_1>("GJB-rule-1.1.1", "过程名禁止被重用", Finder);
  // this->registerChecker<Rule_1_1_2>("GJB-rule-1.1.2", "标号名禁止被重用", Finder);
  this->registerChecker<Rule_1_1_4>("GJB-rule-1.1.4", "禁止声明多重标号", Finder);
  this->registerChecker<Rule_1_1_6>("GJB-rule-1.1.6", "在过程声明中必须对参数说明", Finder);
  this->registerChecker<Rule_1_1_7>("GJB-rule-1.1.7", "禁止过程参数只有类型没有标识符", Finder);
  this->registerChecker<Rule_1_1_8>("GJB-rule-1.1.8", "禁止在过程参数中使用省略号", Finder);
  this->registerChecker<Rule_1_1_9>("GJB-rule-1.1.9", "禁止重新定义使用C或C++的关键字", Finder);

  this->registerChecker<Rule_3_1_1>("GJB-rule-3.1.1", "禁止条件判别成立时相应分支无执行语句", Finder);
  this->registerChecker<Rule_3_1_2>("GJB-rule-3.1.2", "在if...else if语句中必须使用else分支", Finder);
  this->registerChecker<Rule_3_1_3>("GJB-rule-3.1.3", "禁止条件判别的else分支无可执行语句", Finder);
  this->registerChecker<Rule_3_1_4>("GJB-rule-3.1.4", "在switch语句中必须有default语句", Finder);
  this->registerChecker<Rule_3_1_5>("GJB-rule-3.1.5", "禁止使用空switch语句", Finder);
  this->registerChecker<Rule_3_1_6>("GJB-rule-3.1.6", "禁止switch语句中只包含default语句", Finder);
  this->registerChecker<Rule_3_1_7>("GJB-rule-3.1.7", "禁止switch的case语句不是由break终止", Finder);
  this->registerChecker<Rule_3_1_8>("GJB-rule-3.1.8", "禁止switch的case语句中无任何可执行的语句", Finder);

  this->registerChecker<Rule_4_1_2>("GJB-rule-4.1.2", "禁止指针的指针超过两级", Finder);
  this->registerChecker<Rule_4_1_3>("GJB-rule-4.1.3", "禁止将过程声明为指针类型", Finder);

  this->registerChecker<Rule_5_1_1>("GJB-rule-5.1.1", "禁止直接从过程中跳出", Finder);
  this->registerChecker<Rule_5_1_2>("GJB-rule-5.1.2", "禁止使用goto语句", Finder);

  this->registerChecker<Rule_6_1_1>("GJB-rule-6.1.1", "禁止在非赋值表达式中出现赋值操作符", Finder);
  this->registerChecker<Rule_6_1_3>("GJB-rule-6.1.3", "禁止对有符号类型进行移位操作", Finder);
  this->registerChecker<Rule_6_1_4>("GJB-rule-6.1.4", "对变量进行移位运算必须保证不会产生溢出", Finder);
  this->registerChecker<Rule_6_1_5>("GJB-rule-6.1.5", "禁止给无符号变量赋负值", Finder);
  this->registerChecker<Rule_6_1_6>("GJB-rule-6.1.6", "有符号类型的位长度必须大于等于两位", Finder);
  this->registerChecker<Rule_6_1_7>("GJB-rule-6.1.7", "位的定义必须是有符号整数或无符号整数", Finder);
  this->registerChecker<Rule_6_1_11>("GJB-rule-6.1.11", "禁止对常数值做逻辑非的运算", Finder);
  this->registerChecker<Rule_6_1_12>("GJB-rule-6.1.12", "禁止对有符号类型进行移位操作", Finder);
  this->registerChecker<Rule_6_1_15>("GJB-rule-6.1.15", "禁止在逻辑表达式中使用赋值操作符", Finder);
  this->registerChecker<Rule_6_1_16>("GJB-rule-6.1.16", "禁止赋值操作符与\"&&\"或\"||\"连用", Finder);
  this->registerChecker<Rule_6_1_17>("GJB-rule-6.1.17", "禁止位操作符带有布尔型的操作数", Finder);
  this->registerChecker<Rule_6_1_18>("GJB-rule-6.1.18", "禁止位操作符作用于布尔值", Finder);

  this->registerChecker<Rule_8_1_1>("GJB-rule-8.1.1", "禁止单独使用小写字母\"l\"或大写字母\"O\"作为变量名", Finder);

  this->registerChecker<Rule_11_1_1>("GJB-rule-11.1.1", "禁止使用不合适的循环变量类型", Finder);
  this->registerChecker<Rule_11_1_2>("GJB-rule-11.1.2", "循环变量必须是局部声明的", Finder);

  this->registerChecker<Rule_12_1_1>("GJB-rule-12.1.1", "禁止对指针变量使用强制类型转换赋值", Finder);

  this->registerChecker<Rule_13_1_1>("GJB-rule-13.1.1", "枚举元素的初始化必须完整", Finder);
  this->registerChecker<Rule_13_1_2>("GJB-rule-13.1.2", "结构体变量初始化的类型必须一致", Finder);
  // this->registerChecker<Rule_13_1_4>("GJB-rule-13.1.4", "变量使用前必须被赋过值", Finder);

  this->registerChecker<Rule_14_1_1>("GJB-rule-14.1.1", "禁止对实数类型的量做是否相等的比较", Finder);
  this->registerChecker<Rule_14_1_2>("GJB-rule-14.1.2", "禁止逻辑判别的表达式不是逻辑表达式", Finder);
  this->registerChecker<Rule_14_1_3>("GJB-rule-14.1.3", "switch语句中的表达式禁止是逻辑表达式", Finder);
}

} // namespace GJB
} // namespace crulet
} // namespace clang