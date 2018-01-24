#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECK_UTILS_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_CHECK_UTILS_H

#include <unordered_set>
#include <string>

namespace clang {
namespace crulet {
namespace check_utils {

std::unordered_set<std::string> CPPKeywords({"alignas", "alignof", "and", "and_eq", "ams", 
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

bool isCPPKeyword(std::string Name){
  if(CPPKeywords.find(Name) != CPPKeywords.end()){
    return true;
  }
  return false;
}

} // namespace check_utils
} // namespace crulet
} // namespace clang

#endif