set(LLVM_LINK_COMPONENTS support)

add_clang_library(cruletCore
  Crulet.cpp
  CruletOptions.cpp
  CruletContext.cpp
  CruletChecker.cpp
  CruletModule.cpp
  CruletDiagnosticConsumer.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangTooling
  clangToolingCore
  )

add_subdirectory(utils)
add_subdirectory(modules)
add_subdirectory(tools)
add_subdirectory(bugreporter)