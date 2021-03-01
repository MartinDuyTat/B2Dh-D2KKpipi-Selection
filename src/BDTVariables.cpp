// Martin Duy Tat 1st March 2021

#include"BDTVariables.h"
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<fstream>

std::string BDTVariables::DetermineTransformation(std::string Expression) {
  if(Expression.substr(0, 7) == "log(1 -") {
    // If transformation is "log(1 - x)
    // Remove first 8 characters and last character to get variable name
    std::string variable = Expression.erase(0, 8);
    variable.erase(variable.size() - 1);
    return "log(1 - x) " + variable;
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
    return "log(min(x, y)) " + variable1 + " " + variable2;
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
    return "log(max(x, y)) " + variable1 + " " + variable2;
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
  std::ifstream TrainingVariablesFiles(Filename);
  if(TrainingVariablesFile.is_open()) {
    std::string line;
    while(std::getline(TrainingVariablesFile, line)) {
      std::string ParsedLine = DetermineTransformation(line);
      std::string transformation;
      std::istringstream ss(ParsedLine);
      ss >> transformation;
      if(transformation == "None" || transformation == "log(1 - x)" || transformation == "log(x)") {
	std::string variable;
	ss >> variable;
	m_Variables.push_back(std::vector<std::string>{transformation, line, variable});
      } else if(transformation == "log(min(x, y))" || transformation == "log(max(x, y))") {
	std::string variable1, variable2;
	ss >> variable1;
	ss >> variable2;
	m_Variables.push_back(std::vector<std::string>{transformation, line, variable1, variable2});
      }
    }
  }
}
