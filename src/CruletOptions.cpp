#include "CruletOptions.h"

namespace clang {
namespace crulet {

void CruletOptions::parseCheckOptions(std::string OptStr){
  int start = 0;
  OptStr += ",";
  for(unsigned int i = 0; i < OptStr.size(); i++){
    if(OptStr[i] == ','){
      std::string item = OptStr.substr(start, i-start);
      start = i+1;

      if(item.empty()) continue;

      if(item[0] == '-'){
        item = item.substr(1);
        if(!item.empty()){
          EnabledCheckerMap[item] = false;
        }
      }else{
        EnabledCheckerMap[item] = true;
      }
    }
  }
}

bool CruletOptions::isCheckerEnabled(std::string ModuleName, std::string CheckerName){
  std::string Name = ModuleName + "-" + CheckerName;
  if(EnabledCheckerMap.find(Name) != EnabledCheckerMap.end()){
    return EnabledCheckerMap[Name];
  }else if(EnabledCheckerMap.find(ModuleName + "-*") != EnabledCheckerMap.end()){
    return EnabledCheckerMap[ModuleName + "-*"];
  }else if(EnabledCheckerMap.find("*") != EnabledCheckerMap.end()){
    return true;
  }
  return false;
}

} // namespace crulet
} // namespace clang
