#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "Modules/GJB/GJBModule.h"

using namespace llvm;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

// Apply a custom category to all command-line options so that they are the only ones displayed.
static llvm::cl::OptionCategory CruletCategory("crulet options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...");

int main(int argc, const char **argv){
  CommonOptionsParser OptionsParser(argc, argv, CruletCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  MatchFinder Finder;
  crulet::GJB::GJBModule GJBModule("GJB Module");
  GJBModule.registerCheckers(&Finder);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}