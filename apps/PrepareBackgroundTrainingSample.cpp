// Martin Duy Tat 25th Februrary 2021
/**
 * PrepareBackgroundTrainingSample takes in a datasample ROOT file from DaVinci and saves new ROOT file with a background training sample for the BDT
 * The cuts applied are the standard base cuts and a high mass sideband cut on the \f$B\f$ mass
 * @param 1 Number of input files
 * @param 2 If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
 * @param Filename of output ROOT file
 */

