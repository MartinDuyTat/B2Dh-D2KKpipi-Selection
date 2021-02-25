// Martin Duy Tat 25th Februrary 2021
/**
 * PrepareSignalTrainingSample takes in an MC sample ROOT file from DaVinci and saves new ROOT file with a signal training sample for the BDT
 * The cuts applied are the standard base cuts and MC truth matching cuts
 * @param 1 Number of input files
 * @param 2 If there's a single input file, input full path name, otherwise input the path name without the number and file extension (e.g. if filenames are myfile0.root, myfile1.root, etc input myfile)
 * @param Filename of output ROOT file
 */

