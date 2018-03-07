#include "JsonBugReporter.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Basic/FileManager.h"

namespace clang {
namespace crulet {

void JsonBugReporter::create(std::string filename){
  JsonOFS.open(filename, std::ios::out);
  if(!JsonOFS.is_open()){
    llvm::errs() << "The file could not be opened: " << filename << "\n\n";
  }
}

void JsonBugReporter::addElement(std::string CheckerName, std::string Msg, 
                             DiagnosticsEngine &DE, SourceManager &SM, SourceLocation Loc, 
                             DiagnosticIDs::Level Level){
  nlohmann::json JObj;
  JObj["type"] = CheckerName;
  JObj["description"] = Msg;

  if(Level == DiagnosticIDs::Warning){
    JObj["level"] = "Warning";
  }

  FullSourceLoc FSL(Loc, SM);
  JObj["location"]["fileID"] = FSL.getFileID().getHashValue();
  JObj["location"]["file"] = FSL.getFileEntry()->getName().str();
  JObj["location"]["line"] = FSL.getLineNumber();
  JObj["location"]["column"] = FSL.getColumnNumber();

  Json.push_back(JObj);
  // JsonOFS << JObj.dump();
}

void JsonBugReporter::close(){
  JsonOFS << Json.dump();
  JsonOFS.close();
}

} // namespace crulet
} // namespace clang