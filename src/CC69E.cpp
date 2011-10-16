//============================================================================
// Name        : CC69E
// Author      : Juan Silva
// Version     : 0.9b
// Copyright   : GLP
// Description : Particle recognition software.
//============================================================================

#include "Arguments/ArgsProcessor.h"
#include "Image/MyImageFactory.h"
#include "Utils/MyLogger.h"
#include "Algorithm/Algorithm.h"
#include "Algorithm/AlgorithmFactory.h"
#include "Algorithm/MyPeak.h"
#include "Output/Output.h"
#include "Output/OutputFactory.h"

using namespace std;

int main(int argc, char* argv[]) {
	MyLogger *mylog = MyLogger::getInstance();
	ArgsProcessor *proc = ArgsProcessor::getInstance();
	proc->setArgs(argc, argv);

	if(proc->hasKey("-debugwf")){
		mylog->setPriority(log4cpp::Priority::DEBUG);
		mylog->logFileData(true);
	}
	if(proc->hasKey("-debug"))
		mylog->setPriority(log4cpp::Priority::DEBUG);
	if(proc->hasKey("-silent"))
		mylog->setPriority(log4cpp::Priority::FATAL);
	if(proc->hasKey("-chrono"))
		mylog->setPriority(log4cpp::Priority::NOTICE);

	mylog->log()->notice(">> Welcome to Ptracking C++/CUDA <<");

	MyImage img = MyImageFactory::makeImgFromFile(proc->getArgAsString("-i"));	// ~670 milisegundos

	Algorithm *alg = AlgorithmFactory::select(proc->getAlgorithmType());
	alg->setData(img.matrix());
	vector<MyPeak> peaks = alg->run(proc->getContainer());
	delete alg;

	Output *out = OutputFactory::makeOutputGenerator(proc->getOutputType());
	if(proc->hasKey("-out"))
		out->writeData(&peaks, proc->getArgAsString("-out"));
	if(proc->hasKey("-outbin"))
		out->writeData(&peaks, proc->getArgAsString("-outbin"));
	if(!proc->hasKey("-out") && !proc->hasKey("-outbin"))
		out->writeData(&peaks, "");

	mylog->log()->notice(">> Ptracking C++/CUDA Finished<<");
	return EXIT_SUCCESS;
}
