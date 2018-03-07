set(LLVM_LINK_COMPONENTS support)

add_clang_library(cruletBugReporter
  BugReporter.cpp
  JsonBugReporter.cpp
  )