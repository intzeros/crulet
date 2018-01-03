#include "Rule_4_11_1_2.h"
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

void Rule_4_11_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher1 = forStmt(hasCondition(binaryOperator(
                                anyOf(hasOperatorName("<"), hasOperatorName(">"), 
                                  hasOperatorName("<="), hasOperatorName(">="), 
                                  hasOperatorName("=="), hasOperatorName("!=")),
                                anyOf(
                                  hasLHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("forLoop_condVar"))),
                                  hasRHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("forLoop_condVar"))))
                                ))).bind("forLoop");
  StatementMatcher Matcher2 = forStmt(hasCondition(forEachDescendant(binaryOperator(
                                anyOf(hasOperatorName("<"), hasOperatorName(">"), 
                                  hasOperatorName("<="), hasOperatorName(">="), 
                                  hasOperatorName("=="), hasOperatorName("!=")),
                                anyOf(
                                  hasLHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("forLoop_condVar"))),
                                  hasRHS(ignoringParenImpCasts(declRefExpr(
                                    to(varDecl(hasType(isInteger())))).bind("forLoop_condVar"))))
                              )))).bind("forLoop");
  Finder->addMatcher(Matcher1, this);
  Finder->addMatcher(Matcher2, this);
}

void Rule_4_11_1_2::run(const MatchFinder::MatchResult &Result) {
  if(const ForStmt *FS = Result.Nodes.getNodeAs<ForStmt>("forLoop")){
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

    const DeclRefExpr *DRE = Result.Nodes.getNodeAs<DeclRefExpr>("forLoop_condVar");
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
          Context->report(this->CheckerName, this->ReportMsg, DE, DRE->getLocation(), DiagnosticIDs::Warning);
        }
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
