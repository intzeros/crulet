#include "Rule_11_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include <vector>

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_11_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher1 = forStmt(hasCondition(binaryOperator(
                                anyOf(hasOperatorName("<"), hasOperatorName(">"), 
                                  hasOperatorName("<="), hasOperatorName(">="), 
                                  hasOperatorName("=="), hasOperatorName("!=")),
                                anyOf(
                                  hasLHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("gjb1112_forLoop_condVar"))),
                                  hasRHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("gjb1112_forLoop_condVar"))))
                                ))).bind("gjb1112_forLoop");
  StatementMatcher Matcher2 = forStmt(hasCondition(forEachDescendant(binaryOperator(
                                anyOf(hasOperatorName("<"), hasOperatorName(">"), 
                                  hasOperatorName("<="), hasOperatorName(">="), 
                                  hasOperatorName("=="), hasOperatorName("!=")),
                                anyOf(
                                  hasLHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("gjb1112_forLoop_condVar"))),
                                  hasRHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("gjb1112_forLoop_condVar"))))
                              )))).bind("gjb1112_forLoop");
  Finder->addMatcher(Matcher1, this);
  Finder->addMatcher(Matcher2, this);
}

void Rule_11_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const ForStmt *FS = Result.Nodes.getNodeAs<ForStmt>("gjb1112_forLoop")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FS->getForLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    std::vector<VarDecl*> varDeclVec;
    if(const Stmt *InitStmt = FS->getInit()){
      if(isa<DeclStmt>(InitStmt)){
        const DeclStmt *InitDS = dyn_cast<DeclStmt>(InitStmt);
        for(auto it = InitDS->decl_begin(); it != InitDS->decl_end(); ++it){
          if(isa<VarDecl>(*it)){
            varDeclVec.push_back(dyn_cast<VarDecl>(*it));
          }
        }
      }
    }

    const DeclRefExpr *DRE = Result.Nodes.getNodeAs<DeclRefExpr>("gjb1112_forLoop_condVar");
    if(DRE){
      const ValueDecl *VD = DRE->getDecl();
      if(VD){
        bool IsForInitDecl = false;
        for(unsigned int i = 0; i < varDeclVec.size(); i++){
          if(VD == varDeclVec[i]){
            IsForInitDecl = true;
            break;
          }
        }

        if(!IsForInitDecl){
          DiagnosticsEngine &DE = Result.Context->getDiagnostics();
          Context->report(this->CheckerName, this->ReportMsg, DE, DRE->getLocation(), this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, DRE->getLocation(), this->DiagLevel);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
