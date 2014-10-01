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

#ifndef H2D_HH
#define H2D_HH

#include "src/helper/Histogram.hh"



class H2D: public Histogram{

public:

	// Member Functions

	H2D(int, Verbose *, HistogramMode = unpublished, bool = true);
	virtual ~H2D();
	virtual void Initialize(int, bool);
	virtual void SetMajorParameters(TString, TString);

	void SetHistogramMode(HistogramMode);
	void SetName(TString);
	void SetOutputPath(TString);
	
	HistogramMode GetHistogramMode();
	TString GetName();
	TString GetOutputPath();
	TH2F * GetTH2();

	void Divide(H2D*, Option_t* = "");
	void Fill(float, float);
	void Fill(float, float, float);
	void SetBins(int, float, float, int, float, float);
	void SetBins(std::vector<Double_t>, std::vector<Double_t>);
	void SetSumw2();	

	bool Write();


private:

	TCanvas * kCanvas;
	TString kRootFilePath;
	TH2F * kTH2;
	
};


#endif
