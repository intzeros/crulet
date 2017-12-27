#include "CruletContext.h"

namespace clang {
namespace crulet {

bool CruletContext::isCheckerEnabled(StringRef ModuleName, StringRef CheckerName){
  return Options.isCheckerEnabled(ModuleName, CheckerName);
}

CruletOptions &CruletContext::getOptions() {
  return Options;
}

} // namespace crulet
} // namespace clang