/*
 * AlgorithmFactory.cpp
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */

#include "AlgorithmFactory.h"

Algorithm *AlgorithmFactory::select(AlgorithmType type){
	Algorithm *ret = new Algorithm();
	switch (type) {
		case Chi2_Algorithm:
			MyLogger::log()->info("[AlgorithmFactory][select] Chi2 Algorithm selected");
			return new Chi2Algorithm();
			break;
		case Chi2HD_Algorithm:
			MyLogger::log()->info("[AlgorithmFactory][select] Chi2 High Density Algorithm selected");
			return new Chi2HDAlgorithm();
			break;
		case None_Algorithm:
			MyLogger::log()->info("[AlgorithmFactory][select] No Algorithm selected");
			return ret;
			break;
	}
	return ret;
}
