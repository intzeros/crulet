#include "Rule_2_1_5.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

namespace {
class PPCallbacks_2_1_5 : public PPCallbacks {
public:
  PPCallbacks_2_1_5(Preprocessor *PP, Rule_2_1_5 *Checker)
      : PP(PP), Checker(Checker) {}

  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok, 
                          StringRef FileName, bool IsAngled, CharSourceRange FilenameRange, 
                          const FileEntry *File, StringRef SearchPath, 
                          StringRef RelativePath, const Module *Imported) override {
    SourceManager &SM = PP->getSourceManager();
    if(!SM.isInMainFile(HashLoc)) return;

    Checker->addIncludeSourceLocation(HashLoc);
  }

private:
  Preprocessor *PP;
  Rule_2_1_5 *Checker;
};
} // namespace

void Rule_2_1_5::registerPPCallbacks(CompilerInstance &CI) {
  Preprocessor &PP = CI.getPreprocessor();
  PP.addPPCallbacks(
      llvm::make_unique<PPCallbacks_2_1_5>(&PP, this));
}

void Rule_2_1_5::registerMatchers(ast_matchers::MatchFinder *Finder){
  Finder->addMatcher(stmt().bind("stmt"), this);
  Finder->addMatcher(decl().bind("decl"), this);
}

void Rule_2_1_5::run(const ast_matchers::MatchFinder::MatchResult &Result){
  if(IsReported) return;

  if(const auto S = Result.Nodes.getNodeAs<Stmt>("stmt")){
    SourceLocation SSL = S->getLocStart();
    SourceManager &SM = Result.Context->getSourceManager();
    if(!SM.isInMainFile(SSL)) return;

    for(auto &SL : IncludeSLVec){
      if(SM.isWrittenInSameFile(SSL, SL) && SM.isBeforeInTranslationUnit(SSL, SL)){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, DiagnosticIDs::Warning);
        IsReported = true;
        break;
      }
    }
  }else if(const auto D = Result.Nodes.getNodeAs<Decl>("decl")){
    SourceLocation SSL = D->getLocStart();
    SourceManager &SM = Result.Context->getSourceManager();
    if(!SM.isInMainFile(SSL)) return;

    for(auto &SL : IncludeSLVec){
      if(SM.isWrittenInSameFile(SSL, SL) && SM.isBeforeInTranslationUnit(SSL, SL)){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, DiagnosticIDs::Warning);
        IsReported = true;
        break;
      }
    }
  }
}

void Rule_2_1_5::addIncludeSourceLocation(SourceLocation SL){
  IncludeSLVec.push_back(SL);
}

} // namespace GJB
} // namespace crulet
} // namespace clang
