#include "Rule_2_1_10.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_2_1_10::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = functionDecl().bind("gjb2110_functionDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_2_1_10::run(const MatchFinder::MatchResult &Result) {
  if(const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("gjb2110_functionDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = FD->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    if(FD->isMain()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();

      QualType ReturnType = FD->getReturnType().getCanonicalType();
      if(ReturnType.getAsString() != "int"){
        DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, FD->getLocStart(), this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, FD->getLocStart(), this->DiagLevel);
        SourceRange Range = FD->getReturnTypeSourceRange();
        const auto FixIt = clang::FixItHint::CreateReplacement(Range, "int");
        DB.AddFixItHint(FixIt);
      }

      if(FD->param_size() == 0){
        std::string Name = FD->getType().getAsString();
        if(Name.find(')') - Name.find('(') == 1){
          Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
        }
      }else if(FD->param_size() == 2u){
        const ParmVarDecl *PVD1 = FD->getParamDecl(0);
        QualType ParmType1 = PVD1->getOriginalType().getCanonicalType();
        if(ParmType1.getAsString() != "int"){
          DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
          SourceRange Range = PVD1->getSourceRange();
          const auto FixIt = clang::FixItHint::CreateReplacement(Range, "int");
          DB.AddFixItHint(FixIt);
        }
        
        const ParmVarDecl *PVD2 = FD->getParamDecl(1);
        QualType ParmType2 = PVD2->getOriginalType().getCanonicalType();
        if(ParmType2.getAsString() != "char *[]" && ParmType2.getAsString() != "char **"){
          DiagnosticBuilder DB = Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
          Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
          SourceRange Range = PVD2->getSourceRange();
          const auto FixIt = clang::FixItHint::CreateReplacement(Range, "char *[]");
          DB.AddFixItHint(FixIt);
        }
      }else{
        Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
        Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, this->DiagLevel);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
