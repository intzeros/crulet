#include "Rule_1_1_16.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_16::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl(anyOf(
                                          functionDecl(isDefinition()),
                                          fieldDecl(),
                                          varDecl(isDefinition()),
                                          enumConstantDecl(),
                                          labelDecl(), 
                                          typedefDecl(),
                                          enumDecl(isDefinition()), 
                                          recordDecl(isDefinition())
                                        )).bind("gjb1116_namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_16::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("gjb1116_namedDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ND->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    std::string Name = ND->getNameAsString();
    if(Name == ""){
      return;
    }

    if(VarNameMap.find(Name) != VarNameMap.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, VarNameMap[Name]->getLocation(), this->DiagLevel);
    }else{
      VarNameMap[Name] = ND;
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
