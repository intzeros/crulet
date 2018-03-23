#include "GJBModule.h"
#include "Rule_1_1_1.h"
#include "Rule_1_1_2.h"
#include "Rule_1_1_3.h"
#include "Rule_1_1_4.h"
#include "Rule_1_1_5.h"
#include "Rule_1_1_6.h"
#include "Rule_1_1_7.h"
#include "Rule_1_1_8.h"
#include "Rule_1_1_9.h"
#include "Rule_1_1_10.h"
#include "Rule_1_1_11.h"
#include "Rule_1_1_12.h"
#include "Rule_1_1_13.h"
#include "Rule_1_1_14.h"
#include "Rule_1_1_15.h"
#include "Rule_1_1_16.h"
#include "Rule_1_1_17.h"
#include "Rule_1_1_18.h"
#include "Rule_1_1_19.h"
#include "Rule_1_1_20.h"
#include "Rule_1_1_21.h"
#include "Rule_1_1_22.h"
#include "Rule_2_1_1.h"
#include "Rule_2_1_2.h"
#include "Rule_2_1_3.h"
#include "Rule_2_1_4.h"
#include "Rule_2_1_5.h"
#include "Rule_2_1_6.h"
#include "Rule_2_1_8.h"
#include "Rule_2_1_9.h"
#include "Rule_2_1_10.h"
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
#include "Rule_6_1_8.h"
#include "Rule_6_1_9.h"
#include "Rule_6_1_10.h"
#include "Rule_6_1_11.h"
#include "Rule_6_1_12.h"
#include "Rule_6_1_13.h"
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

namespace clang {
namespace crulet {
namespace GJB {

void GJBModule::registerCheckers(){
  this->registerChecker<Rule_1_1_1>("GJB-1.1.1", "过程名禁止被重用");
  this->registerChecker<Rule_1_1_2>("GJB-1.1.2", "标号名禁止被重用");
  // this->registerChecker<Rule_1_1_3>("GJB-1.1.3", "禁止在结构体定义中含有空域");
  this->registerChecker<Rule_1_1_4>("GJB-1.1.4", "禁止声明多重标号");
  this->registerChecker<Rule_1_1_5>("GJB-1.1.5", "参数必须使用类型声明");
  this->registerChecker<Rule_1_1_6>("GJB-1.1.6", "在过程声明中必须对参数说明");
  this->registerChecker<Rule_1_1_7>("GJB-1.1.7", "禁止过程参数只有类型没有标识符");
  this->registerChecker<Rule_1_1_8>("GJB-1.1.8", "禁止在过程参数中使用省略号");
  this->registerChecker<Rule_1_1_9>("GJB-1.1.9", "禁止重新定义使用C或C++的关键字");
  this->registerChecker<Rule_1_1_10>("GJB-1.1.10", "禁止过程或函数中的参数表为空");
  this->registerChecker<Rule_1_1_11>("GJB-1.1.11", "禁止在同一个宏中使用多个#或##");
  // this->registerChecker<Rule_1_1_12>("GJB-1.1.12", "禁止定义不像函数的宏");
  this->registerChecker<Rule_1_1_13>("GJB-1.1.13", "禁止在宏中包含不允许的项");
  this->registerChecker<Rule_1_1_14>("GJB-1.1.14", "禁止重新定义保留字");
  this->registerChecker<Rule_1_1_15>("GJB-1.1.15", "字符型变量必须明确定义是有符号还是无符号");
  this->registerChecker<Rule_1_1_16>("GJB-1.1.16", "禁止对一个名字重新定义");
  this->registerChecker<Rule_1_1_17>("GJB-1.1.17", "用typedef自定义的类型禁止被重新定义");
  this->registerChecker<Rule_1_1_18>("GJB-1.1.18", "禁止在同一个文件中有#if而没有#endif");
  this->registerChecker<Rule_1_1_19>("GJB-1.1.19", "禁止数组没有边界限定");
  this->registerChecker<Rule_1_1_20>("GJB-1.1.20", "禁止在#include<……>中使用绝对路径名");
  this->registerChecker<Rule_1_1_21>("GJB-1.1.21", "禁止结构体声明不完整");
  this->registerChecker<Rule_1_1_22>("GJB-1.1.22", "禁止参数的声明形式上不一致");

  this->registerChecker<Rule_2_1_1>("GJB-2.1.1", "过程体必须用大括号括起来");
  this->registerChecker<Rule_2_1_2>("GJB-2.1.2", "循环体必须用大括号括起来");
  this->registerChecker<Rule_2_1_3>("GJB-2.1.3", "then/else中的语句必须用大括号括起来");
  this->registerChecker<Rule_2_1_4>("GJB-2.1.4", "逻辑表达式的连接必须使用括号");
  this->registerChecker<Rule_2_1_5>("GJB-2.1.5", "禁止在头文件前有可执行代码");
  this->registerChecker<Rule_2_1_6>("GJB-2.1.6", "宏参数必须用括号括起来");
  this->registerChecker<Rule_2_1_8>("GJB-2.1.8", "头文件名禁止使用“'”，“\\”和“/*”等字符");
  this->registerChecker<Rule_2_1_9>("GJB-2.1.9", "禁止字符串中单独使用“\\”，字符串的终止必须使用“\\0”");
  this->registerChecker<Rule_2_1_10>("GJB-2.1.10", "main必须定义为int main(void)或int main(int, char*[])的形式");

  this->registerChecker<Rule_3_1_1>("GJB-3.1.1", "禁止条件判别成立时相应分支无执行语句");
  this->registerChecker<Rule_3_1_2>("GJB-3.1.2", "在if...else if语句中必须使用else分支");
  this->registerChecker<Rule_3_1_3>("GJB-3.1.3", "禁止条件判别的else分支无可执行语句");
  this->registerChecker<Rule_3_1_4>("GJB-3.1.4", "在switch语句中必须有default语句");
  this->registerChecker<Rule_3_1_5>("GJB-3.1.5", "禁止使用空switch语句");
  this->registerChecker<Rule_3_1_6>("GJB-3.1.6", "禁止switch语句中只包含default语句");
  this->registerChecker<Rule_3_1_7>("GJB-3.1.7", "禁止switch的case语句不是由break终止");
  this->registerChecker<Rule_3_1_8>("GJB-3.1.8", "禁止switch的case语句中无任何可执行的语句");

  this->registerChecker<Rule_4_1_2>("GJB-4.1.2", "禁止指针的指针超过两级");
  this->registerChecker<Rule_4_1_3>("GJB-4.1.3", "禁止将过程声明为指针类型");

  this->registerChecker<Rule_5_1_1>("GJB-5.1.1", "禁止直接从过程中跳出");
  this->registerChecker<Rule_5_1_2>("GJB-5.1.2", "禁止使用goto语句");

  this->registerChecker<Rule_6_1_1>("GJB-6.1.1", "禁止在非赋值表达式中出现赋值操作符");
  this->registerChecker<Rule_6_1_3>("GJB-6.1.3", "禁止对有符号类型进行移位操作");
  this->registerChecker<Rule_6_1_4>("GJB-6.1.4", "对变量进行移位运算必须保证不会产生溢出");
  this->registerChecker<Rule_6_1_5>("GJB-6.1.5", "禁止给无符号变量赋负值");
  this->registerChecker<Rule_6_1_6>("GJB-6.1.6", "有符号类型的位长度必须大于等于两位");
  // this->registerChecker<Rule_6_1_7>("GJB-6.1.7", "位的定义必须是有符号整数或无符号整数");
  this->registerChecker<Rule_6_1_8>("GJB-6.1.8", "禁止给变量赋的值与变量的类型不一致");
  this->registerChecker<Rule_6_1_9>("GJB-6.1.9", "赋值类型必须匹配");
  this->registerChecker<Rule_6_1_10>("GJB-6.1.10", "数组下标必须是整型数");
  this->registerChecker<Rule_6_1_11>("GJB-6.1.11", "禁止对常数值做逻辑非的运算");
  this->registerChecker<Rule_6_1_12>("GJB-6.1.12", "禁止对有符号类型进行移位操作");
  this->registerChecker<Rule_6_1_13>("GJB-6.1.13", "禁止对枚举类型的越限使用");
  this->registerChecker<Rule_6_1_15>("GJB-6.1.15", "禁止在逻辑表达式中使用赋值操作符");
  this->registerChecker<Rule_6_1_16>("GJB-6.1.16", "禁止赋值操作符与\"&&\"或\"||\"连用");
  this->registerChecker<Rule_6_1_17>("GJB-6.1.17", "禁止位操作符带有布尔型的操作数");
  this->registerChecker<Rule_6_1_18>("GJB-6.1.18", "禁止位操作符作用于布尔值");

  this->registerChecker<Rule_8_1_1>("GJB-8.1.1", "禁止单独使用小写字母\"l\"或大写字母\"O\"作为变量名");

  this->registerChecker<Rule_11_1_1>("GJB-11.1.1", "禁止使用不合适的循环变量类型");
  this->registerChecker<Rule_11_1_2>("GJB-11.1.2", "循环变量必须是局部声明的");

  this->registerChecker<Rule_12_1_1>("GJB-12.1.1", "禁止对指针变量使用强制类型转换赋值");

  this->registerChecker<Rule_13_1_1>("GJB-13.1.1", "枚举元素的初始化必须完整");
  this->registerChecker<Rule_13_1_2>("GJB-13.1.2", "结构体变量初始化的类型必须一致");
  // this->registerChecker<Rule_13_1_4>("GJB-13.1.4", "变量使用前必须被赋过值");

  this->registerChecker<Rule_14_1_1>("GJB-14.1.1", "禁止对实数类型的量做是否相等的比较");
  this->registerChecker<Rule_14_1_2>("GJB-14.1.2", "禁止逻辑判别的表达式不是逻辑表达式");
  this->registerChecker<Rule_14_1_3>("GJB-14.1.3", "switch语句中的表达式禁止是逻辑表达式");
}

} // namespace GJB
} // namespace crulet
} // namespace clang