#include "Rule_1_1_20.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_1_1_20 : public PPCallbacks {
public:
  PPCallbacks_1_1_20(Preprocessor *PP, Rule_1_1_20 *Checker)
      : PP(PP), Checker(Checker) {}

  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok, 
                          StringRef FileName, bool IsAngled, CharSourceRange FilenameRange, 
                          const FileEntry *File, StringRef SearchPath, 
                          StringRef RelativePath, const Module *Imported) override {
    SourceManager &SM = PP->getSourceManager();
    if(!SM.isInMainFile(HashLoc)) return;

    DiagnosticsEngine &DE = PP->getDiagnostics();
    auto *Context = Checker->getCruletContext();
    StringRef ReportMsg = Checker->getReportMsg();
    StringRef CheckerName = Checker->getName();
    DiagnosticIDs::Level DiagLevel = Checker->getDiagLevel();

    if(FileName.size() > 0 && FileName[0] == '/'){
      DiagnosticBuilder DB = Context->report(CheckerName, ReportMsg, DE, HashLoc, DiagLevel);
      Context->getJsonBugReporter().report(CheckerName, ReportMsg, SM, HashLoc, DiagLevel);
      DB.AddSourceRange(FilenameRange);
    }
  }

private:
  Preprocessor *PP;
  Rule_1_1_20 *Checker;
};
} // namespace

void Rule_1_1_20::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_1_1_20>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
