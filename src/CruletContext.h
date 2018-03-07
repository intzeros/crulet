#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H

#include "clang/Basic/Diagnostic.h"
#include "CruletOptions.h"
#include "bugreporter/JsonBugReporter.h"

namespace clang {
namespace crulet {

class CruletContext{
public:
  CruletContext();
  ~CruletContext();

  bool isCheckerEnabled(StringRef CheckerName);
  CruletOptions &getOptions();
  void setJsonBugReporter(std::string filename);
  JsonBugReporter* getJsonBugReporter();

  DiagnosticBuilder report(std::string CheckerName, std::string Msg, 
                           DiagnosticsEngine &DE, SourceLocation Loc, 
                           DiagnosticIDs::Level Level = DiagnosticIDs::Warning);

private:
  CruletOptions Options;
  JsonBugReporter *JsonReporter;
};


} // namespace crulet
} // namespace clang


#endif