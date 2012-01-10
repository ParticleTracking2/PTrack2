/*
 * AlgorithmTypes.h
 *
 *  Created on: 09/01/2012
 *      Author: juanin
 */

#ifndef ALGORITHMTYPES_H_
#define ALGORITHMTYPES_H_

/**
 * Tipos de algoritmos implementados actualmente
 */
enum AlgorithmType{
	Chi2_Algorithm,
	Chi2HD_Algorithm,
#ifdef CHI2CUDA
	Chi2HDCuda_Algorithm,
#endif
	None_Algorithm
};


#endif /* ALGORITHMTYPES_H_ */
