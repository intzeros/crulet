set(LLVM_LINK_COMPONENTS support)

add_clang_executable(crulet
  CruletMain.cpp
  )

target_link_libraries(crulet
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangTooling
  clangToolingCore
  cruletGJBModule
  Crulet
  )

install(TARGETS crulet
  RUNTIME DESTINATION bin)
