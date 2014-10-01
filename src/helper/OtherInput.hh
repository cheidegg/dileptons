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

#ifndef OTHERINPUT_HH
#define OTHERINPUT_HH

#include <TROOT.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "src/helper/Tools.hh"


namespace OtherInput {

	std::vector<TString> ReadColumnFromListFile(std::string, int = 0);
	TString ReadFromTextFile(std::string);
	std::vector<std::vector<TString> > ReadMatrixFromListFile(std::string, TString = "\t", int = 0);
	TH1F * ReadTH1FFromROOTFile(TString, TString, TString);
	TH2F * ReadTH2FFromROOTFile(TString, TString, TString);
	std::vector<TString> ReadRowFromListFile(std::string, int = 0);



}

#endif
