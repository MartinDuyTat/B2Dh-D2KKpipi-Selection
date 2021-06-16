// Martin Duy Tat 11th June 2021
/**
 * CheckEventNumbers is an application that takes in either one or two datasets and checks how many multiple candidates there are and how many events they have in common
 */

#include<iostream>
#include<string>
#include"EventNumbers.h"

int main(int argc, char *argv[]) {
  if(argc != 2 && argc != 3) {
    std::cout << "Please input 1 or 2 arguments\n";
    return 0;
  }
  std::cout << "Counting multiple candidates of first dataset\n";
  EventNumbers eventNumbers{std::string(argv[1])};
  eventNumbers.CountMultipleCandidates();
  if(argc == 3) {
    std::cout << "Counting multiple candidates of second dataset\n";
    EventNumbers eventNumbers2{std::string(argv[2])};
    eventNumbers2.CountMultipleCandidates();
    std::cout << "Checking event numbers in common\n";
    eventNumbers.CompareEvents(eventNumbers2);
  }
  return 0;
}
