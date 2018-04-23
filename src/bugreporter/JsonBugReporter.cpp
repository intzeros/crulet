#include "JsonBugReporter.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/FileManager.h"
#include "llvm/Support/raw_ostream.h"
#include <stack>

namespace clang {
namespace crulet {

JsonBugReporter::~JsonBugReporter(){
  if(filename == "") return;
  if(Json.size() == 0) return;

  JsonOFS.open(filename, std::ios::out);
  if(!JsonOFS.is_open()){
    llvm::errs() << "The file could not be opened: " << filename << "\n\n";
    return;
  }
  JsonOFS << Json.dump();
  JsonOFS.close();
}

std::string JsonBugReporter::getFilePath(std::string Dir, std::string Name){
  if(Name.size() > 0 && Name[0] == '/'){
    return Name;
  }

  std::string Path;
  if(Dir.size() > 0 && Dir[Dir.size()-1] != '/'){
    Path = Dir + "/" + Name;
  }else{
    Path = Dir + Name;
  }

  std::stack<std::string> stk;
  size_t i = 1, j = 1;
  while(j <= Path.size()){
    if(j == Path.size() || Path[j] == '/'){
      std::string item = Path.substr(i, j-i);
      if(item == "" || item == ".") {}
      else if(!stk.empty() && item == ".."){
        stk.pop();
      }else{
        stk.push(item);
      }
      j++;
      i = j;
    }else{
      j++;
    }
  }

  std::string rst;
  while(!stk.empty()){
    rst = "/" + stk.top() + rst;
    stk.pop();
  }
  return rst;
}

void JsonBugReporter::setOutputFile(std::string filename){
  this->filename = filename;
}

void JsonBugReporter::report(std::string CheckerName, std::string Msg, 
                             SourceManager &SM, SourceLocation Loc, 
                             DiagnosticIDs::Level Level){
  if(filename == "") return;
  if(!Loc.isValid()) return;

  nlohmann::json JObj;
  JObj["type"] = CheckerName;
  JObj["description"] = Msg;

  if(Level == DiagnosticIDs::Warning){
    JObj["level"] = "Warning";
  }

  FullSourceLoc FSL(Loc, SM);
  FSL = FSL.getFileLoc(); // to remove SpellingLoc in some cases
  std::string FileName = getFilePath(Context->getBuildDirectory(), FSL.getFileEntry()->getName().str());
  
  // const DirectoryEntry *DireEntry = FSL->getFileEntry()->getDir();
  // FileManager &FM = SM.getFileManager();
  // std::string BuildDir = FM.getCanonicalName(DireEntry);
  // JObj["location"]["file"] = FSL.getFileEntry()->getName().str();
  JObj["location"]["file"] = FileName;
  JObj["location"]["line"] = FSL.getLineNumber();
  JObj["location"]["column"] = FSL.getColumnNumber();

  Json.push_back(JObj);
}


void JsonBugReporter::report(std::string CheckerName, std::string Msg, 
                             SourceManager &SM, SourceLocation Loc, SourceLocation RelativeLoc,
                             DiagnosticIDs::Level Level){
  if(filename == "") return;
  if(!Loc.isValid() || !RelativeLoc.isValid()) return;
  
  nlohmann::json JObj;
  JObj["type"] = CheckerName;
  JObj["description"] = Msg;

  if(Level == DiagnosticIDs::Warning){
    JObj["level"] = "Warning";
  }

  FullSourceLoc FSL(Loc, SM);
  std::string FileName = getFilePath(Context->getBuildDirectory(), FSL.getFileEntry()->getName().str());
  JObj["location"]["file"] = FileName;
  JObj["location"]["line"] = FSL.getLineNumber();
  JObj["location"]["column"] = FSL.getColumnNumber();

  FullSourceLoc RelativeFSL(RelativeLoc, SM);
  JObj["location"]["relativeLoc"]["file"] = RelativeFSL.getFileEntry()->getName().str();
  JObj["location"]["relativeLoc"]["line"] = RelativeFSL.getLineNumber();
  JObj["location"]["relativeLoc"]["column"] = RelativeFSL.getColumnNumber();

  Json.push_back(JObj);
}
} // namespace crulet
} // namespace clang