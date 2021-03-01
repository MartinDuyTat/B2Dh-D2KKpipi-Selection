// Martin Duy Tat 1st March 2021
/**
 * BDTVariables is a class that stores the branch variables of a TTree that were used to train a BDT and connects them to a TMVA::Reader
 * The constructor takes a filename of a text file with the BDT training variables
 */

#ifndef BDTVARIABLES
#define BDTVARIABLES

#include<string>
#include<vector>
#include<map>
#include"TTree.h"
#include"TMVA/Reader.h"

class BDTVariables {
  public:
    /**
     * DetermineTransformation takes in a string with a mathematical expression and determines what the variable transformation is
     * Only "None", "log(x)", "log(1 - x)", "log(max(x, y))" and "log(min(x, y))" is currently supported
     * @param Expression Mathematical expression we want to determine the transformation of
     * @return A space separated list of strings, where the first string identifies the transformation (as described above), the second string is the variable name and the third string is the second variable in the "log(max(x, y))" and "log(min(x, y))" cases
     */
    std::string DetermineTransformation(std::string Expression);
    /**
     * Constructor that stores all the training variables
     * @param Filename Filename of text file with BDT training variables
     */
    BDTVariables(std::string Filename);
    /**
     * Function that sets all the branch addresses of the TTree to the corresponding variables in m_TreeVariables
     * @param Tree TTree with the data before applying the BDT
     */
    void SetTreeBranchAddresses(TTree *Tree);
    /**
     * Function that sets all the branch addresses of the TMVA::Reader to the corresponding variables in m_ClassifierVariables
     * @param Classifier TMVA::Reader object with the BDT
     */
    void SetClassifierBranchAddresses(TMVA::Reader *Classifier);
    /**
     * Function that calculates all the variables in the classifier
     */
    void UpdateVariables();
  private:
    /**
     * Vector of variable names, organized so that each entry is a vector of 3 or 4 strings
     * The first string is the transformation, the second string is the full BDT training variable with transformations, the third and fourth are variable names of the TTree
     */
    std::vector<std::vector<std::string>> m_Variables;
    /**
     * Map that stores the names and values of TTree variables
     */
    std::map<std::string, Double_t> m_TreeVariables;
    /**
     * Map that stores the names and values of the TMVA::Reader variables
     */
    std::map<std::string, Float_t> m_ClassifierVariables;
};

#endif
