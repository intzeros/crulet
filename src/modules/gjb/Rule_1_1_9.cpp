#include "Rule_1_1_9.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Sema/TypoCorrection.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_9::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl().bind("namedDecl");
  Finder->addMatcher(Matcher, this);

  Keywords = std::unordered_set<std::string>({"alignas", "alignof", "and", "and_eq", "ams", 
      "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", 
      "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", 
      "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
      "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int",
      "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "oprerator", 
      "or", "or_eq", "private", "public", "protected", "register", "reinterpret_cast", "requires", "return",
      "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", 
      "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", 
      "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq",
      "final", "override", "cout", "cin", "endl"});
}

void Rule_1_1_9::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("namedDecl")){
    if(Keywords.find(ND->getName()) != Keywords.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, ND->getLocation(), DiagnosticIDs::Warning);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
