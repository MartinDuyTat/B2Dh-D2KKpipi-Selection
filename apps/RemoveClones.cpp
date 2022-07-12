// Martin Duy Tat 12th July 2022
/**
 * RemoveClones is an application that removes candidates that are clones
 * It loops over all D daughter tracks and removes all tracks with an opening angle that is larger than 0.03 degrees
 * @param 1 ROOT filename with data sample
 * @param 2 ROOT filename with output sample
 */

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include"TChain.h"
#include"TMath.h"
#include"TTree.h"
#include"TFile.h"
#include"Math/Vector3Dfwd.h"
#include"Math/DisplacementVector3D.h"

using Vector = ROOT::Math::XYZVector;

int main(int argc, char *argv[]) {
  if(argc != 3) {
    std::cout << "Please input 2 arguments\n";
    return 0;
  }
  std::cout << "Removing clones\n";
  std::cout << "Loading data...\n";
  TChain Chain("DecayTree");
  Chain.Add(argv[1]);
  TFile File(argv[2], "RECREATE");
  TTree *Tree = Chain.CloneTree(0);
  std::map<std::string, double> Variables;
  std::vector<std::string> Daughters{"h1", "h2", "h3", "h4"};
  std::vector<std::string> MomentumVariables{"PX", "PY", "PZ"};
  for(const auto &Daughter : Daughters) {
    for(const auto &Var : MomentumVariables) {
      const std::string Name = "Bu_constD0PV_D0_" + Daughter + "_" + Var;
      Variables.insert({Name, 0.0});
      Chain.SetBranchAddress(Name.c_str(), &Variables[Name]);
    }
  }
  std::cout << "Data ready\n";
  std::cout << "Searching through data for clones...\n";
  for(int i = 0; i < Chain.GetEntries(); i++) {
    Chain.GetEntry(i);
    std::vector<Vector> P;
    for(const auto &Daughter : Daughters) {
      const std::string Name = "Bu_constD0PV_D0_" + Daughter + "_";
      P.push_back(Vector(Variables[Name + "PX"],
			 Variables[Name + "PY"],
			 Variables[Name + "PZ"]));
    }
    bool IsClone = false;
    for(int ii = 0; ii < 4; ii++) {
      for(int jj = 0; jj < ii; jj++) {
	const auto UnitVector1 = P[ii].Unit();
	const auto UnitVector2 = P[jj].Unit();
	const double CosTheta = UnitVector1.Dot(UnitVector2);
	const double Theta = TMath::ACos(CosTheta)*180.0/TMath::Pi();
	if(Theta < 0.03) {
	  IsClone = true;
	  break;
	}
      }
      if(IsClone) {
	break;
      }
    }
    if(!IsClone) {
      Tree->Fill();
    }
  }
  std::cout << "No more clones!\n";
  Tree->Write();
  File.Close();
  return 0;
}
