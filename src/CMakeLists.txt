set(LLVM_LINK_COMPONENTS support)

add_clang_library(Crulet
  CruletOptions.cpp
  CruletContext.cpp
  CruletChecker.cpp
  CruletModule.cpp
  Crulet.cpp

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