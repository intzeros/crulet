#include "Rule_2_1_4.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_2_1_4::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(ifStmt(hasCondition(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(ifStmt(hasCondition(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(ifStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);
  Finder->addMatcher(ifStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);

  Finder->addMatcher(forStmt(hasCondition(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(forStmt(hasCondition(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(forStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);
  Finder->addMatcher(forStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);

  Finder->addMatcher(whileStmt(hasCondition(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(whileStmt(hasCondition(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(whileStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);
  Finder->addMatcher(whileStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);

  Finder->addMatcher(doStmt(hasCondition(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(doStmt(hasCondition(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      )), this);
  Finder->addMatcher(doStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("||"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);
  Finder->addMatcher(doStmt(hasCondition(hasDescendant(
                        binaryOperator(hasOperatorName("&&"), eachOf(
                          hasLHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("||")).bind("gjb_214")),
                          hasLHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214")),
                          hasRHS(binaryOperator(hasOperatorName("&&")).bind("gjb_214"))))
                      ))), this);
}

void Rule_2_1_4::run(const MatchFinder::MatchResult &Result) {
  if(const auto *OP = Result.Nodes.getNodeAs<BinaryOperator>("gjb_214")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = OP->getOperatorLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
    Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);

    const auto &LangOpts = Result.Context->getLangOpts();
    SourceLocation EndLoc = Lexer::getLocForEndOfToken(OP->getLocEnd(), 0, SM, LangOpts);
    const auto FixIt1 = clang::FixItHint::CreateInsertion(OP->getLocStart(), "(");
    const auto FixIt2 = clang::FixItHint::CreateInsertion(EndLoc, ")");
    DB.AddFixItHint(FixIt1);
    DB.AddFixItHint(FixIt2);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
