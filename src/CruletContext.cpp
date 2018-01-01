#include "CruletContext.h"

namespace clang {
namespace crulet {

bool CruletContext::isCheckerEnabled(StringRef CheckerName){
  return Options.isCheckerEnabled(CheckerName);
}

CruletOptions &CruletContext::getOptions() {
  return Options;
}

} // namespace crulet
} // namespace clang