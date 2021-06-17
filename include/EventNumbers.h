// Martin Duy Tat 11th June 2021
/**
 * EventNumbers is a class that stores all the event numbers of a dataset after the final selection and stores all the event numbers in the signal region
 * Two EventNumbers classes can be compared to check how much overlap there is between the selection inside the signal region
 * The number of occurences of an event number is also stored so that the number of multiple candidates can be studied
 */

#ifndef EVENTNUMBERS
#define EVENTNUMBERS

#include<string>
#include<map>
#include"RtypesCore.h"

class EventNumbers {
  public:
    /**
     * Constructor that takes in a text filename containing the filenames of all ROOT files with final selection
     * @param Filename File containing all filenames fo dataset
     * @param BDTCut BDT cut
     */
    EventNumbers(const std::string &Filename, double BDTCut);
    /**
     * Function that compares two datasets and checks how many events they have in common inside the signal region (intersection) and the total number of events inside the signal region (union)
     * @param rhs Another EventNumbers object to compare with
     */
    void CompareEvents(const EventNumbers &rhs) const;
    /**
     * Function that counts the number of multiple candidates
     */
    void CountMultipleCandidates() const;
  private:
    /**
     * Map of event numbers and the number of occurences
     */
    std::map<ULong64_t, int> m_EventNumbers;
};

#endif
