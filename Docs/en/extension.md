#Extend PTrack2

In order to extend the functionality of PTrack2 is good to know how the software works.
##PTrack2 Operation

##Adding a new algorithm

First we need to establish the algorithm type that we are going to build modifying the enumeration **AlgorithmType** located in the file ***AlgorithmType.h***. In this case we will call the new Algorithm type as ***MyNewAlgorithm_Algorithm***.
```cpp
enum AlgorithmType{
	Chi2_Algorithm,
	Chi2HD_Algorithm,
#ifdef CHI2CUDA
	Chi2HDCuda_Algorithm,
#endif
	MyNewAlgorithm_Algorithm,
	None_Algorithm
};

```

Next is necessary to extend the class **Algorithm** as follow.
```cpp
#include "Algorithm.h"

class MyNewAlgorithm: public Algorithm {

/**
 * Private variables of the algorithm
 */
private:
	double _data1;
	int _data2;
	string _data3;
	MyMatrix<double> _myImage;

/**
 * Obligatory extension
 */
public:

	/**
	 * Return the values that accept this algorithm.
	 * @return All the parameters that accept this algorithm to execute.
	 */
	static ArgObj myArgs();

	/**
	 * Establish the data to be processed.
	 * @param pc Parameter that uses this algorithm in order to be executed.
	 */
	void setData(ParameterContainer *pc);

	/**
	 * Execute the algorithm of least-squares fitting to detect peaks.
	 * @return MyPeak Vector representing the peaks found.
	 */
	vector<MyPeak> run();
};

ArgObj MyNewAlgorithm::myArgs(){
	ArgObj mynewalgorithm;
	mynewalgorithm.type = MyNewAlgorithm_Algorithm;						// Type of the new algorithm
	mynewalgorithm.argkey = "mynewalg";							// How it should be called in order to execute
	mynewalgorithm.description = "Magick particle detection algorithm. ";			// Algorithm description 
	mynewalgorithm.example = "mynewalg -img MyImage.tif -d1 9.87 -d2 1 -d3 'Hello World' ";	// A typical execution example

	/* Acceptable parameter */
	KeyTreat img;				// Argument
	img.key = "-img";			// How should be called
	img.description = "Image to read.";	// Short description

	/* Add how should be treated */
	img.treat.push_back(Require_Treat);		// Required argument for operating, without it, the algorithm cannot be executed
	img.treat.push_back(Followed_String_Treat);	// Must be followed by a string
	mynewalgorithm.keys_treats.push_back(img);	// Store the argument


	KeyTreat d1;
	d1.key = "-d1";
	d1.description = "Diameter of an ideal particle. (Default = 9.87).";
	d1.treat.push_back(Followed_Double_Treat);
	mynewalgorithm.keys_treats.push_back(d1);

	KeyTreat d2;
	d2.key = "-d2";
	d2.description = "Diameter of an ideal particle. (Default = 5).";
	d2.treat.push_back(Followed_Int_Treat);
	mynewalgorithm.keys_treats.push_back(d2);

	KeyTreat d3;
	d3.key = "-d3";
	d3.description = "Welcome message";
	d3.treat.push_back(Followed_String_Treat);
	mynewalgorithm.keys_treats.push_back(d3);

	/* Return the algorithm arguments */
	return mynewalgorithm;
}

void MyNewAlgorithm::setData(ParameterContainer *pc){
	_data1 = 9.87;					// Default value if applicable
	if(pc->existParam("-d1"))			// If the parameter –d1 exists
		_data1 = pc->getParamAsDouble("-d1");	// Establish the parameter as double.

	_data2 = 1.84;
	if(pc->existParam("-d2"))
		_data2 = pc->getParamAsInt("-d2");

	_data3 = "Welcome";
	if(pc->existParam("-d3"))
		_data3 = pc->getParamAsString("-d3");

	_myImage = MyImageFactory::makeRawImgFromFile(pc->getParamAsString("-img"));
}

/**
 *******************************
 * Executing the Algorithm
 *******************************
 */
vector<MyPeak> MyNewAlgorithm::run(){
	MyLogger::log()->notice("[MyNewAlgorithm] Running My Magick Algorithm");
	vector<MyPeak> peaks;

	// Do magic here

	return peaks;
}
```

Once extended the class, we need to modify some functions in ***AlgorithmExecutor*** as follow.
```cpp
#include "MyNewAlgorithm.h"

vector<ArgObj> AlgorithmExecutor::getAllArguments(){
	vector<ArgObj> ret;
	...

	ret.push_back(MyNewAlgorithm::myArgs());	// Include new arguments
	return ret;
}

AlgorithmType AlgorithmExecutor::translate(string alg){
	MyLogger::log()->debug("[AlgorithmExecutor][translate] Translating string Algorithm type: %s", alg.c_str());
	...

	// Translate the text argument into a type.
	if(alg.compare("mynewalg")==0){
		MyLogger::log()->debug("[AlgorithmExecutor][translate] Translated to: MyNewAlgorithm_Algorithm");
		ret = MyNewAlgorithm_Algorithm;
	}

	return ret;
}

void AlgorithmExecutor::select(AlgorithmType type){
	if(selected != 0)
		delete selected;

	switch (type) {
		...
		case MyNewAlgorithm_Algorithm:
			MyLogger::log()->info("[AlgorithmExecutor][select] Magick particle detection algorithm selected");
			selected = new MyNewAlgorithm();
			break;
	}
}

```

And that’s it.
