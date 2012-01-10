//============================================================================
// Name        : PTrack2
// Author      : Juan Silva
// Version     : 1.1
// Copyright   : GLP
// Description : Particle recognition software.
//============================================================================

#include <vector>
#include "Arguments/ArgsProcessor.h"
#include "Image/MyImageFactory.h"
#include "Utils/MyLogger.h"
#include "Algorithm/AlgorithmExecutor.h"
#include "Algorithm/MyPeak.h"
#include "Output/Output.h"
#include "Output/OutputFactory.h"

using namespace std;

/*! \mainpage PTrack2 C++/Cuda
 *
 * \section intro_sec Introdución
 *
 * Esta página contiene todo lo necesario para entender cada una de las funciones, relaciones y algunos patrones de diseño que se usan en PTrack2. <br/>
 * Para más información acerca del uso, instalacion y recursos necesarios visita el <a href="http://trac.assembla.com/particle-tracking-2">Trac</a>
 *
 */

int main(int argc, char* argv[]) {
	MyLogger *mylog = MyLogger::getInstance();

	//****************************
	// Procesa e interpreta los
	// argumentos entregados
	//****************************
	ArgsProcessor *proc = ArgsProcessor::getInstance();
	proc->setArgs(argc, argv);

	//****************************
	// Establece el nivel de log
	//****************************
	if(proc->hasKey("-debugwf")){
		mylog->setPriority(log4cpp::Priority::DEBUG);
		mylog->logFileData(true);
	}
	if(proc->hasKey("-silent"))
		mylog->setPriority(log4cpp::Priority::FATAL);
	if(proc->hasKey("-chrono"))
		mylog->setPriority(log4cpp::Priority::NOTICE);
	if(proc->hasKey("-debug"))
		mylog->setPriority(log4cpp::Priority::DEBUG);

	mylog->log()->notice(">> Welcome to Ptracking C++/CUDA <<");

	bool use_threads = true;
	if(proc->getContainer()->existParam("-nothreads"))
		use_threads = false;

	AlgorithmExecutor aExec;
	aExec.select(proc->getAlgorithmType());
	aExec.setParams(proc->getContainer());
	aExec.setThreads(use_threads);
	vector<MyPeak> peaks = aExec.execute();

	//****************************
	// Generar el archivo de salida
	//****************************
	Output *out = OutputFactory::makeOutputGenerator(proc->getOutputType());
	out->writeData(&peaks, proc->getOutputString());

	delete out;

	//****************************
	// Desplegar imagen si se desea
	//****************************
	if(proc->hasKey("-display")){
		MyImage img;
		if(proc->hasKey("-cut"))
			img = MyImageFactory::makeImgFromFile(proc->getArgAsString("-i"), proc->getArgAsInt("-cut"));	// ~670 --> ~430 (2 threads) milisegundos
		else
			img = MyImageFactory::makeImgFromFile(proc->getArgAsString("-i"));
		img.display(&peaks);
	}

	mylog->log()->notice(">> Ptracking C++/CUDA Finished <<");
	return EXIT_SUCCESS;
}
