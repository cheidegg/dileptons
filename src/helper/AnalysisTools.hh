/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Dileptons Analysis Framework                                         **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#ifndef ANALYSISTOOLS_HH
#define ANALYSISTOOLS_HH

#include <TROOT.h>
#include <TString.h>
#include <TMath.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <time.h>

#include "src/helper/CustomTypes.hh"
#include "src/helper/Debug.hh"


namespace AnalysisTools {

	float Absolute(float);
	float AngleAddition(float, float);
	float AngleSubtraction(float, float);
	float DeltaPhi(float, float);
	float DeltaR(float, float, float, float);
	float Maximum(std::vector<float>);
	float Minimum(std::vector<float>);
	float Sum(std::vector<float>);

}

#endif
