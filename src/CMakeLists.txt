set(LLVM_LINK_COMPONENTS support)

add_clang_executable(crulet
  Crulet.cpp
  )

target_link_libraries(crulet
  clangTooling
  clangBasic
  clangASTMatchers
  cruletGJBModule
  )

add_subdirectory(Modules)