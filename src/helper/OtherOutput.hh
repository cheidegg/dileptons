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

#ifndef OTHEROUTPUT_HH
#define OTHEROUTPUT_HH

#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"

#include "src/helper/Tools.hh"



namespace OtherOutput{

	bool CloseTreeAndWrite();
	bool OpenTreeToWrite(TString, int, TString);
	void PrintUsage();
	bool WriteToTextFile(TString, TString, TString);
	
}


#endif
