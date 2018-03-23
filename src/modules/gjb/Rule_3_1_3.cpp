#include "Rule_3_1_3.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_3::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = ifStmt().bind("gjb313_if");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_3::run(const MatchFinder::MatchResult &Result) {
  if(const IfStmt *IF = Result.Nodes.getNodeAs<IfStmt>("gjb313_if")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = IF->getIfLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const Stmt* Else = IF->getElse();

    if(Else && isa<NullStmt>(Else)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, Else->getLocStart(), this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, Else->getLocStart(), this->DiagLevel);
    }else if(Else && isa<CompoundStmt>(Else)){
      auto ThenCS = dyn_cast<CompoundStmt>(Else);
      bool IsEmpty = true;
      for(auto it = ThenCS->body_begin(); it != ThenCS->body_end(); ++it){
        if(isa<NullStmt>(*it) == false){
          IsEmpty = false;
          break;
        }
      }

      if(IsEmpty){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Else->getLocStart(), this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, Else->getLocStart(), this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
