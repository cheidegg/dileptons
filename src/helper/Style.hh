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

#ifndef STYLE_HH
#define STYLE_HH

#include "TString.h"
#include "TObject.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TVirtualPad.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "src/helper/CustomTypes.hh"
#include "src/helper/Tools.hh"


namespace Style{

	TCanvas * CreateCanvas(std::string, int = 600, int = 975, bool = true);
	void SetCanvas(TCanvas *, std::string, int = 975, int = 600, bool = true); 
	void SetCanvasMargin(TCanvas *, float = 0.15, float = 0.12, float = 0.03, float = 0.07);

	void CreateRatioPad();

	void SetDefaultH1DStyle();
	void SetDefaultH2DStyle();
	void SetDefaultRatioPlotStyle();
	void SetFakeRatioMapStyle(TH2F *);

	
}


#endif
