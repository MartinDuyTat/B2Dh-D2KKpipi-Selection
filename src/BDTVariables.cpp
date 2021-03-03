// Martin Duy Tat 1st March 2021

#include"BDTVariables.h"
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>
#include<fstream>
#include"TTree.h"
#include"TMath.h"
#include"TMVA/Reader.h"

std::string BDTVariables::DetermineTransformation(std::string Expression) {
  if(Expression.substr(0, 7) == "log(1 -") {
    // If transformation is "log(1 - x)
    // Remove first 8 characters and last character to get variable name
    std::string variable = Expression.erase(0, 8);
    variable.erase(variable.size() - 1);
    return "log(1-x) " + variable;
  } else if(Expression.substr(0, 8) == "log(min(") {
    // If transformation is "log(min(x, y))
    // First split up string by whitespace
    std::istringstream ss(Expression);
    std::string FirstPart, SecondPart;
    ss >> FirstPart;
    ss >> SecondPart;
    // Remove first 8 characters and last character of first part
    std::string variable1 = FirstPart.erase(0, 8);
    variable1.erase(variable1.size() - 1);
    // Remove last 2 characters of second part
    std::string variable2 = SecondPart.erase(SecondPart.size() - 2);
    return "log(min(x,y)) " + variable1 + " " + variable2;
  } else if(Expression.substr(0, 8) == "log(max(") {
    // If transformation is "log(max(x, y))
    // First split up string by whitespace
    std::istringstream ss(Expression);
    std::string FirstPart, SecondPart;
    ss >> FirstPart;
    ss >> SecondPart;
    // Remove first 8 characters and last character of first part
    std::string variable1 = FirstPart.erase(0, 8);
    variable1.erase(variable1.size() - 1);
    // Remove last 2 characters of second part
    std::string variable2 = SecondPart.erase(SecondPart.size() - 2);
    return "log(max(x,y)) " + variable1 + " " + variable2;
  } else if(Expression.substr(0, 4) == "log(") {
    // If transformation is "log(x)
    // Remove first 4 characters and last character to get varables name
    std::string variable = Expression.erase(0, 4);
    variable.erase(variable.size() - 1);
    return "log(x) " + variable;
  } else {
    // If there is no transformation
    return "None " + Expression;
  }
}

BDTVariables::BDTVariables(std::string Filename) {
  std::ifstream TrainingVariablesFile(Filename);
  if(TrainingVariablesFile.is_open()) {
    std::string line;
    while(std::getline(TrainingVariablesFile, line)) {
      std::string ParsedLine = DetermineTransformation(line);
      std::string transformation;
      std::istringstream ss(ParsedLine);
      ss >> transformation;
      if(transformation == "None" || transformation == "log(1-x)" || transformation == "log(x)") {
	std::string variable;
	ss >> variable;
	m_Variables.push_back(std::vector<std::string>{transformation, line, variable});
	// If variable is from DecayTreeFitter, it's of Float_t type, need to save this separately
	if(line.find("constD0PV") == std::string::npos) {
	  m_TreeVariables.insert({variable, 0.0});
	} else {
	  m_TreeVariablesF.insert({variable, 0.0});
	}
	m_ClassifierVariables.insert({line, 0.0});
      } else if(transformation == "log(min(x,y))" || transformation == "log(max(x,y))") {
	std::string variable1, variable2;
	ss >> variable1;
	ss >> variable2;
	m_Variables.push_back(std::vector<std::string>{transformation, line, variable1, variable2});
	m_TreeVariables.insert({variable1, 0.0});
	m_TreeVariables.insert({variable2, 0.0});
	m_ClassifierVariables.insert({line, 0.0});
      }
    }
  }
}

void BDTVariables::SetTreeBranchAddresses(TTree *Tree) {
  for(auto Variables_iter = m_Variables.begin(); Variables_iter != m_Variables.end(); Variables_iter++) {
    // If variable is from DecayTreeFitter, it's of Float_t type, need to save this separately
    if((*Variables_iter)[2].find("constD0PV") == std::string::npos) {
      Tree->SetBranchAddress((*Variables_iter)[2].c_str(), &m_TreeVariables[(*Variables_iter)[2]]);
    } else {
      Tree->SetBranchAddress((*Variables_iter)[2].c_str(), &m_TreeVariablesF[(*Variables_iter)[2]]);
    }
    if((*Variables_iter)[0] == "log(min(x, y))" || (*Variables_iter)[0] == "log(max(x, y))") {
      Tree->SetBranchAddress((*Variables_iter)[3].c_str(), &m_TreeVariables[(*Variables_iter)[3]]);
    }
  }
}

void BDTVariables::SetClassifierBranchAddresses(TMVA::Reader *Classifier) {
  for(auto Variables_iter = m_Variables.begin(); Variables_iter != m_Variables.end(); Variables_iter++) {
    Classifier->AddVariable((*Variables_iter)[1], &m_ClassifierVariables[(*Variables_iter)[1]]);
  }
}

void BDTVariables::UpdateVariables() {
  for(auto Variables_iter = m_Variables.begin(); Variables_iter != m_Variables.end(); Variables_iter++) {
    if((*Variables_iter)[0] == "None") {
      m_ClassifierVariables[(*Variables_iter)[1]] = m_TreeVariables[(*Variables_iter)[2]];
    } else if((*Variables_iter)[0] == "log(x)") {
      if((*Variables_iter)[2].find("constD0PV") == std::string::npos) {
	m_ClassifierVariables[(*Variables_iter)[1]] = TMath::Log(m_TreeVariables[(*Variables_iter)[2]]);
      } else {
	m_ClassifierVariables[(*Variables_iter)[1]] = TMath::Log(m_TreeVariablesF[(*Variables_iter)[2]]);
      }
    } else if((*Variables_iter)[0] == "log(1-x)") {
      m_ClassifierVariables[(*Variables_iter)[1]] = TMath::Log(1 - m_TreeVariables[(*Variables_iter)[2]]);
    } else if((*Variables_iter)[0] == "log(min(x,y))") {
      m_ClassifierVariables[(*Variables_iter)[1]] = TMath::Log(std::min(m_TreeVariables[(*Variables_iter)[2]], m_TreeVariables[(*Variables_iter)[3]]));
    } else if((*Variables_iter)[0] == "log(max(x,y))") {
      m_ClassifierVariables[(*Variables_iter)[1]] = TMath::Log(std::max(m_TreeVariables[(*Variables_iter)[2]], m_TreeVariables[(*Variables_iter)[3]]));
    }
  }
}
