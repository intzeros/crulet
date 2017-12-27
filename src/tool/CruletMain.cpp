#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "../Crulet.h"
#include "../CruletOptions.h"

using namespace llvm;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace clang::crulet;

const std::string crulet_version = "1.0.0";

// Apply a custom category to all command-line options so that they are the only ones displayed.
static llvm::cl::OptionCategory CruletCategory("crulet options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
// static cl::extrahelp MoreHelp("\nMore help text...");

static cl::opt<bool> ListModulesOpt("list-modules", cl::desc("List all modules."), 
    cl::init(false), cl::cat(CruletCategory));

static cl::opt<bool> ListEnabledModulesOpt("list-enabled-modules", cl::desc("List all enabled modules."), 
    cl::init(false), cl::cat(CruletCategory));

static cl::opt<std::string> EnableModuleOpt("enable-module", cl::desc("Enable module."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> DisableModuleOpt("disable-module", cl::desc("Disable module."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> ListCheckersOpt("list-checkers", cl::desc("List all checkers."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> ListEnabledCheckersOpt("list-enabled-checkers", cl::desc("List all enabled checkers."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> EnableCheckersOpt("enable-checker", cl::desc("Enable checker."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> DisableCheckersOpt("disable-checker", cl::desc("Disable checker."), 
    cl::init("none"), cl::cat(CruletCategory));

static cl::opt<std::string> CheckOpt("check", cl::desc("Run the given checkers."), 
    cl::init("*"), cl::cat(CruletCategory));


static void PrintVersion() {
  raw_ostream &OS = outs();
  OS << "Crulet version " << crulet_version << "\n";
}

// int runCruletTool(){
  // CommonOptionsParser OptionsParser(argc, argv, CruletCategory);
  // ClangTool Tool(OptionsParser.getCompilations(),
  //                OptionsParser.getSourcePathList());

  // MatchFinder Finder;
  // crulet::CruletManager Manager;
  // Manager.registerModules(&Finder);

  // return Tool.run(newFrontendActionFactory(&Finder).get());
// }


int main(int argc, const char **argv){
  cl::SetVersionPrinter(PrintVersion);
  CommonOptionsParser OptionsParser(argc, argv, CruletCategory, cl::ZeroOrMore);
  
  CruletContext Context;
  CruletOptions &Options = Context.getOptions();
  Options.parseCheckOptions(CheckOpt);

  MatchFinder Finder;
  CruletManager Manager(&Context);
  Manager.registerModules(&Finder);

  if(ListModulesOpt){
    std::vector<std::string> ModuleNames = Manager.getModuleNames();
    if (ModuleNames.empty()) {
      llvm::errs() << "No modules registered.\n";
      return 1;
    }

    llvm::outs() << "Modules:";
    for (const auto &Name : ModuleNames){
      llvm::outs() << "\n    " << Name;
    }
    llvm::outs() << "\n\n";
    return 0;
  }

  if(ListCheckersOpt != "none"){
    std::vector<std::string> CheckerNames = Manager.getCheckerNames(ListCheckersOpt);
    if (CheckerNames.empty()) {
      llvm::errs() << "No checkers registered.\n";
      return 1;
    }

    llvm::outs() << "Checkers:";
    for (const auto &Name : CheckerNames){
      llvm::outs() << "\n    " << Name;
    }
    llvm::outs() << "\n\n";
    return 0;
  }

  if(CheckOpt != "none"){

  }

  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory(&Finder).get());
  // return runCruletTool();
}