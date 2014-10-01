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


#include "src/helper/Histogram.hh"






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CLASS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
Histogram::Histogram(){
	/*
	constructs the Histogram class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
Histogram::~Histogram(){
	/*
	destructs the Histogram class
	paramters: none
	return: none
	*/

}


//____________________________________________________________________________
void Histogram::Initialize(TString name, Verbose * verbosity, HistogramMode mode){
	/*
	initializes the Histogram class
	paramters: none
	return: none
	*/
	
	kVerbose = verbosity;
	kVerbose -> Class("Histogram");

	kName = name;
	kMode = mode;

}



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR SETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


// done in H1D and H2D sub-classes


/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR READING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


// done in H1D and H2D sub-classes


/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR HISTOGRAM OPTIONS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
TCanvas * Histogram::CreateCanvas(std::string canvas_name, int width, int height, bool set_margin){
	/*
  	creates a canvas with given width, height and sets margin, if needed
  	parameters: canvas_name, width, height, set_margin (true if default margin shall be set, false else)
  	return: the canvas
  	*/

	TCanvas * new_canvas = new TCanvas(Tools::ConvertStdStringToCString(canvas_name), "C", width, height);
	new_canvas -> SetTicks(1, 1);
	SetCanvasMargin(new_canvas);
	
	return new_canvas;
 
}


//____________________________________________________________________________
void Histogram::SetCanvasMargin(TCanvas* canvas, float bottom, float left, float right, float top){
	/*
  	sets the margin of a canvas
  	parameters: canvas, bottom, left, right, top
  	return: none
  	*/

	canvas -> SetBottomMargin(bottom);
	canvas -> SetLeftMargin  (left);
	canvas -> SetRightMargin (right);
	canvas -> SetTopMargin   (top);

}


//____________________________________________________________________________
bool Histogram::Write(TCanvas * canvas){
	/*
  	writes a given canvas (hence the histogram on it, hopefully) to the disk
  	parameters: canvas
  	return: true (if writing was successful), false (else)
  	*/

	// this wants to be improved in such a way, that it actually will return false if we fail to write the canvas

	std::cout << "attempting to write " << kOutputPath << kName << std::endl;

	//TString store = kName;
	//kName = "testname";

	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".png"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".pdf"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".root"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".C"));

	//kName = store;

	return true;

}



