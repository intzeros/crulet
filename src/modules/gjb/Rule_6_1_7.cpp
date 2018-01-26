#include "Rule_6_1_7.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_6_1_7::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = fieldDecl(isBitField()).bind("bitField");
  // DeclarationMatcher Matcher = fieldDecl(hasType(isInteger()), has(integerLiteral())).bind("gjb_4617");
  // Finder->addMatcher(Matcher, this);
}

void Rule_6_1_7::run(const MatchFinder::MatchResult &Result) {
  if(const FieldDecl *FD = Result.Nodes.getNodeAs<FieldDecl>("bitField")){
    // QualType Type = FD->getType().getCanonicalType();
    // const Type *TP = FD->getType().getTypePtr();
    // if(!TP->isIntegerType()){
    //   DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    //   Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocation(), DiagnosticIDs::Warning);
    // }else{
    //   llvm::errs() << FD->getType().getAsString() << "\n";
    // }
    // llvm::errs() << Type.getAsString() << "\n";
    
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
