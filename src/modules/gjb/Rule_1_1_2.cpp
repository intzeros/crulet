#include "Rule_1_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher1 = labelStmt().bind("gjb112_labelStmt");
  DeclarationMatcher Matcher2 = namedDecl(anyOf(
                                          labelDecl(), 
                                          declaratorDecl(), 
                                          typedefDecl(), enumDecl(), recordDecl())
                                ).bind("gjb112_namedDecl");
  Finder->addMatcher(Matcher1, this);
  Finder->addMatcher(Matcher2, this);
}

void Rule_1_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const LabelStmt *LS = Result.Nodes.getNodeAs<LabelStmt>("gjb112_labelStmt")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = LS->getIdentLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    std::string LabelName = LS->getName();
    if(LabelName == ""){
      return;
    }

    if(LabelSet.find(LabelName) != LabelSet.end() || NameSet.find(LabelName) != NameSet.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }else{
      LabelSet.insert(LabelName);
    }
  }else if(const NamedDecl *CurND = Result.Nodes.getNodeAs<NamedDecl>("gjb112_namedDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = CurND->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }
    
    std::string Name = CurND->getName();
    if(Name == ""){
      return;
    }

    if(LabelSet.find(Name) != LabelSet.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
    }else{
      NameSet.insert(Name);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
