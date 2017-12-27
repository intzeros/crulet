set(LLVM_LINK_COMPONENTS support)

add_clang_library(Crulet
  Crulet.cpp
  CruletModule.cpp
  CruletChecker.cpp
  CruletOptions.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangTooling
  clangToolingCore
  )

add_subdirectory(modules)
add_subdirectory(tool)