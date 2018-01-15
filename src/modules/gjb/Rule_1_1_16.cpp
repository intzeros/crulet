#include "Rule_1_1_16.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_16::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl().bind("namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_16::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
    std::string Name = ND->getNameAsString();

    if(Name == "") return;

    if(const auto *FD = dyn_cast<FunctionDecl>(ND)){
      if(!FD->isThisDeclarationADefinition()) return;
    }

    if(VarNameSet.find(Name) != VarNameSet.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, ND->getLocation(), DiagnosticIDs::Warning);
    }else{
      VarNameSet.insert(Name);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
