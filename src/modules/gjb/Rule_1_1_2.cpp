#include "Rule_1_1_2.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_2::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher1 = labelStmt().bind("labelStmt");
  DeclarationMatcher Matcher2 = namedDecl().bind("namedDecl");
  Finder->addMatcher(Matcher1, this);
  Finder->addMatcher(Matcher2, this);
}

void Rule_1_1_2::run(const MatchFinder::MatchResult &Result) {
  // llvm::outs() << "--------------------------------------\n";
  // if(const LabelStmt *LS = Result.Nodes.getNodeAs<LabelStmt>("labelStmt")){
  //   llvm::outs() << "labelStmt = " << LS->getName() << "\n";
  //   const auto *Context = LS->getDecl()->getDeclContext();
  //   for(const auto *D : Context->decls()){
  //     if(const auto ND = dyn_cast<NamedDecl>(D)){
  //       llvm::outs() << ND->getName() << "\n";
  //     }else{
  //       llvm::outs() << "null\n";
  //     }
  //   }
  // }

  // if(const NamedDecl *CurND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
  //   llvm::outs() << "namedDecl = " << CurND->getName() << "\n";
  //   const auto *Context = CurND->getDeclContext();
  //   for(const auto *D : Context->decls()){
  //     if(const auto ND = dyn_cast<NamedDecl>(D)){
  //       llvm::outs() << ND->getName() << "\n";
  //     }else{
  //       llvm::outs() << "null\n";
  //     }
  //   }
  // }

  // if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
  //   llvm::outs() << "namedDecl = " << ND->getName() << "\n";
  // }
  // if(const LabelStmt *LS = Result.Nodes.getNodeAs<LabelStmt>("labelStmt")){
  //   llvm::outs() << "labelStmt = " << LS->getName() << "\n";
  //   if(LS->getDecl()){
  //     LS->getDecl()->dump();
  //   }else{
  //     llvm::outs() << "null\n";
  //   }
  // }
  // if(const NamedDecl *CurND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
  //   TranslationUnitDecl *TUD = Result.Context->getTranslationUnitDecl();
  //   for(const auto D : TUD->decls()){
  //     if(const auto *ND = dyn_cast<FunctionDecl>(D)){
  //       if(CurND != ND && CurND->getName() == ND->getName()){
  //         DiagnosticsEngine &DE = Result.Context->getDiagnostics();
  //         Context->report(this->CheckerName, this->ReportMsg, DE, CurND->getLocation(), DiagnosticIDs::Warning);
  //       }
  //     }
  //   }
  // }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
