#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_H

#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/Process.h"
#include "CruletDiagnosticConsumer.h"
#include "CruletModule.h"
#include "CruletChecker.h"
#include "CruletContext.h"
#include <unordered_map>
#include <vector>

namespace clang {
namespace crulet {

class CruletManager {
public:
  CruletManager(CruletContext *Context)
      : Context(Context) {}
  ~CruletManager();
 
  void registerModules();

  void addCheckerActions(CompilerInstance &CI, ast_matchers::MatchFinder *Finder);
  std::vector<std::string> getCheckerNames(StringRef ModuleName);
  std::vector<std::string> getModuleNames();
  ast_matchers::MatchFinder &getMatchFinder();
  CruletContext *getCruletContext();

private:
  template <typename ModuleType>
  CruletModule* registerModule(StringRef ModuleName){
    if(ModuleMap.find(ModuleName) == ModuleMap.end()){
      ModuleMap[ModuleName] = new ModuleType(Context, ModuleName);
    }
    return ModuleMap[ModuleName];
  }

private:
  CruletContext *Context;
  ast_matchers::MatchFinder Finder;
  std::unordered_map<std::string, CruletModule*> ModuleMap;
};


class CruletFrontendAction : public ASTFrontendAction{
public:
  CruletFrontendAction(CruletManager *Manager) : Manager(Manager) {}

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef File) override{
    ast_matchers::MatchFinder &Finder = Manager->getMatchFinder();
    Manager->addCheckerActions(CI, &Finder);
    DiagnosticsEngine &DE = CI.getDiagnostics();
    auto *DiagOpts = new DiagnosticOptions();
    DiagOpts->ShowColors = llvm::sys::Process::StandardOutHasColors();
    auto *DiagPrinter = new CruletDiagnosticConsumer(Manager->getCruletContext(), llvm::outs(), DiagOpts);
    DE.setClient(DiagPrinter, /*ShouldOwnClient=*/true);
    DiagPrinter->BeginSourceFile(CI.getLangOpts(), &CI.getPreprocessor());
    return Finder.newASTConsumer();
  }

private:
  CruletManager *Manager;
};

class CruletFrontendActionFactory : public tooling::FrontendActionFactory{
public:
  CruletFrontendActionFactory(CruletManager *Manager) : Manager(Manager) {}
  
  FrontendAction *create() override {
   return new CruletFrontendAction(Manager); 
 }

private:
  CruletManager *Manager;
};

} // namespace crulet
} // namespace clang


#endif