// Martin Duy Tat 11th June 2021
/**
 * CheckEventNumbers is an application that takes in either one or two datasets and checks how many multiple candidates there are and how many events they have in common
 * @param 1 BDT cut
 * @param 2 Text file with paths of all the data samples
 * @param 3 Second text file with paths of all the data samples
 */

#include<iostream>
#include<string>
#include<cstdlib>
#include"EventNumbers.h"

int main(int argc, char *argv[]) {
  if(argc != 3 && argc != 4) {
    std::cout << "Please input 2 or 3 arguments\n";
    return 0;
  }
  std::cout << "Counting multiple candidates of first dataset\n";
  EventNumbers eventNumbers{std::string(argv[2]), std::atof(argv[1])};
  eventNumbers.CountMultipleCandidates();
  if(argc == 4) {
    std::cout << "Counting multiple candidates of second dataset\n";
    EventNumbers eventNumbers2{std::string(argv[3]), std::atof(argv[1])};
    eventNumbers2.CountMultipleCandidates();
    std::cout << "Checking event numbers in common\n";
    eventNumbers.CompareEvents(eventNumbers2);
  }
  return 0;
}
