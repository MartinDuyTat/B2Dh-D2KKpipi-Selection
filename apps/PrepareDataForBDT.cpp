// Martin Duy Tat 25th Februrary 2021
/**
 * PrepareDataForBDT takes in a datasample ROOT file from DaVinci and saves new ROOT file with all the base cuts before a BDT is applied
 * The cuts applied are the standard base cuts, including a cut on the \f$B\f$ mass to reduce the file size
 * @param 1 Number of input files
 * @param 2 If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
 * @param Filename of output ROOT file
 */

