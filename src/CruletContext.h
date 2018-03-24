#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CONTEXT_H

#include "clang/Basic/Diagnostic.h"
#include "CruletOptions.h"
#include "bugreporter/JsonBugReporter.h"

namespace clang {
namespace crulet {

class JsonBugReporter;

class CruletContext{
public:
  CruletContext();
  ~CruletContext();

  bool isCheckerEnabled(StringRef CheckerName);
  CruletOptions &getOptions();
  JsonBugReporter &getJsonBugReporter();

  void setBuildDirectory(std::string BuildDirectory);
  std::string getBuildDirectory();
  void setCurrentFile(std::string FileName);
  std::string getCurrentFile();

  DiagnosticBuilder report(std::string CheckerName, std::string Msg, 
                           DiagnosticsEngine &DE, SourceLocation Loc, 
                           DiagnosticIDs::Level Level = DiagnosticIDs::Warning);

private:
  CruletOptions Options;
  JsonBugReporter *JsonReporter;
  std::string BuildDirectory;
  std::string CurrentFile;
};

} // namespace crulet
} // namespace clang

#endif