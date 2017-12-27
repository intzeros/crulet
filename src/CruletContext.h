#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H

#include "CruletOptions.h"

namespace clang {
namespace crulet {

class CruletContext{
public:
  CruletContext(){}
  ~CruletContext(){}

  bool isCheckerEnabled(StringRef ModuleName, StringRef CheckerName);
  CruletOptions &getOptions();

private:
  CruletOptions Options;
};


} // namespace crulet
} // namespace clang


#endif