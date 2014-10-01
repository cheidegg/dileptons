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

#ifndef H1D_HH
#define H1D_HH

#include "src/helper/Histogram.hh"



class H1D: public Histogram{

public:

	// Member Functions

	H1D(int, Verbose *, HistogramMode = unpublished, bool = true);
	virtual ~H1D();
	virtual void Initialize(int, bool);
	virtual void SetMajorParameters(TString, TString);

	void SetHistogramMode(HistogramMode);
	void SetName(TString);
	void SetOutputPath(TString);
	
	HistogramMode GetHistogramMode();
	TString GetName();
	TString GetOutputPath();
	TH1F * GetTH1();

	void Divide(H1D*, Option_t* = "");
	void Fill(float);
	void Fill(float, float);
	void SetBins(int, float, float);
	void SetBins(std::vector<Double_t>);
	void SetSumw2();	

	bool Write();


private:

	TCanvas * kCanvas;
	TString kRootFilePath;
	TH1F * kTH1;
	
};


#endif
