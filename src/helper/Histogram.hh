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

#ifndef HISTOGRAM_HH
#define HISTOGRAM_HH

#include "TMath.h"
#include "TString.h"
#include "TObject.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TVirtualPad.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"
#include "time.h"

#include "src/helper/Tools.hh"
#include "src/helper/Verbose.hh"



class Histogram{

public:

	// Member Functions

	Histogram();
	virtual ~Histogram();
	virtual void Initialize(TString, Verbose *, HistogramMode = unpublished);

	TCanvas * CreateCanvas(std::string, int = 600, int = 975, bool = true);
	void SetCanvasMargin(TCanvas *, float = 0.15, float = 0.12, float = 0.03, float = 0.07);

	void CreateRatioPad();

	void SetDefaultH1DStyle();
	void SetDefaultH2DStyle();
	void SetDefaultRatioPlotStyle();
	void SetFakeRatioMapStyle(TH2F *);

	bool Write(TCanvas *);

	HistogramMode kMode;
	TString kName;
	TString kOutputPath;
	Verbose * kVerbose;
	
};


#endif
