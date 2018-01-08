#include "Rule_3_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = ifStmt().bind("if");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const IfStmt *IF = Result.Nodes.getNodeAs<IfStmt>("if")){
    const Stmt* Then = IF->getThen();

    if(Then && isa<NullStmt>(Then)){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, Then->getLocStart(), DiagnosticIDs::Warning);
    }else if(Then && isa<CompoundStmt>(Then)){
      auto ThenCS = dyn_cast<CompoundStmt>(Then);
      bool IsEmpty = true;
      for(auto it = ThenCS->body_begin(); it != ThenCS->body_end(); ++it){
        if(isa<NullStmt>(*it) == false){
          IsEmpty = false;
          break;
        }
      }

      if(IsEmpty){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, IF->getIfLoc(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
