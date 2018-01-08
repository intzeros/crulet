#include "Rule_4_14_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_14_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = stmt(anyOf(
                                ifStmt(), 
                                forStmt(), 
                                whileStmt(),
                                conditionalOperator(),
                                binaryConditionalOperator())).bind("condition_stmt");
  Finder->addMatcher(Matcher, this);
}

void Rule_4_14_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const Stmt *S = Result.Nodes.getNodeAs<Stmt>("condition_stmt")){
    if(isa<IfStmt>(S)){
      const IfStmt *IF = dyn_cast<IfStmt>(S);
      const Expr* Cond = IF->getCond();
      if(Cond && !Cond->isKnownToHaveBooleanValue()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Cond->getExprLoc(), DiagnosticIDs::Warning);
      }
    }else if(isa<ForStmt>(S)){
      const ForStmt *For = dyn_cast<ForStmt>(S);
      const Expr* Cond = For->getCond();
      if(Cond && !Cond->isKnownToHaveBooleanValue()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Cond->getExprLoc(), DiagnosticIDs::Warning);
      }
    }else if(isa<WhileStmt>(S)){
      const WhileStmt *While = dyn_cast<WhileStmt>(S);
      const Expr* Cond = While->getCond();
      if(Cond && !Cond->isKnownToHaveBooleanValue()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Cond->getExprLoc(), DiagnosticIDs::Warning);
      }
    }else if(isa<ConditionalOperator>(S)){
      const ConditionalOperator *CO = dyn_cast<ConditionalOperator>(S);
      const Expr* Cond = CO->getCond();
      if(Cond && !Cond->isKnownToHaveBooleanValue()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Cond->getExprLoc(), DiagnosticIDs::Warning);
      }
    }else if(isa<BinaryConditionalOperator>(S)){
      const BinaryConditionalOperator *BCO = dyn_cast<BinaryConditionalOperator>(S);
      const Expr* Cond = BCO->getCond();
      if(Cond && !Cond->isKnownToHaveBooleanValue()){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Cond->getExprLoc(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
