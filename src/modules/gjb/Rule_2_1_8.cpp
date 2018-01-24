#include "Rule_2_1_8.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_2_1_8 : public PPCallbacks {
public:
  PPCallbacks_2_1_8(Preprocessor *PP, Rule_2_1_8 *Checker)
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

    std::string Name = FileName;
    if(Name.find("'") != std::string::npos){
      Context->report(CheckerName, ReportMsg, DE, HashLoc, DiagnosticIDs::Warning);
    }

    if(Name.find("\\") != std::string::npos){
      Context->report(CheckerName, ReportMsg, DE, HashLoc, DiagnosticIDs::Warning);
    }

    if(Name.find("/*") != std::string::npos){
      Context->report(CheckerName, ReportMsg, DE, HashLoc, DiagnosticIDs::Warning);
    }
  }

private:
  Preprocessor *PP;
  Rule_2_1_8 *Checker;
};
} // namespace

void Rule_2_1_8::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_2_1_8>(&PP, this));
}

} // namespace GJB
} // namespace crulet
} // namespace clang
