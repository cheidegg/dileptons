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


#include "src/helper/H1D.hh"






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CLASS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
H1D::H1D(int creation_time, Verbose * verbosity, HistogramMode mode, bool set_sumw2){
	/*
	constructs the H1D class
	parameters: none
	return: none
	*/

	kVerbose = verbosity;
	kVerbose -> Class("H1D");
	Initialize(creation_time, mode, set_sumw2);

}


//____________________________________________________________________________
H1D::~H1D(){
	/*
	destructs the H1D class
	paramters: none
	return: none
	*/

}


//____________________________________________________________________________
void H1D::Initialize(int creation_time, HistogramMode mode, bool set_sumw2){
	/*
	initializes the H1D class
	paramters: creation_time (time since program start in miliseconds), mode (the
	           mode of the histogram), set_sumw2 (true if we set sumw2, false else)
	return: none
	*/

	kMode = mode;
	
	std::string time_id = Tools::ConvertIntToStdString(creation_time);

	kTH1 = new TH1F(Tools::ConvertStdStringToCString("TH1_" + time_id), "H", 1, 0, 1);

	if(set_sumw2) 
		SetSumw2();

}


//____________________________________________________________________________
void H1D::SetMajorParameters(TString output_path, TString name){
	/*
	sets all major parameters of the histogram
	parameters: output_path, name
	return: none
	*/
	
	kOutputPath = output_path;
	kName       = name;
	
}






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR SETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void H1D::SetHistogramMode(HistogramMode new_value){
	/*
	sets the mode of the histogram to a new value
	parameters: new_value
	return: none
	*/

	kMode = new_value;

}


//____________________________________________________________________________
void H1D::SetName(TString new_value){
	/*
	sets the name of the histogram to a new value
	parameters: new_value
	return: none
	*/

	kName = new_value;

}


//____________________________________________________________________________
void H1D::SetOutputPath(TString new_value){
	/*
	sets the output path of the histogram to a new value
	parameters: new _value
	return: none
	*/

	kOutputPath = new_value;

}



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR READING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
HistogramMode H1D::GetHistogramMode(){
	/*
	returns the mode of the histogram
	parameters: none
	return: kMode
	*/

	return kMode;

}


//____________________________________________________________________________
TString H1D::GetName(){
	/*
	returns the unique name of the output
	parameters: none
	return: kName
	*/
	
	return kName;

}


//____________________________________________________________________________
TString H1D::GetOutputPath(){
	/*
	returns the unique name of the output
	parameters: none
	return: kOutputPath
	*/
	
	return kOutputPath;

}


//____________________________________________________________________________
TH1F * H1D::GetTH1(){
	/*
	returns the TH1F of the histogram
	parameters: none
	return: kTH1
	*/

	return kTH1;

}




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR HISTOGRAM OPTIONS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void H1D::Divide(H1D * denominator_histogram, Option_t* option){
	/*
	divides the THx of the current histogram instance by the THx of a given histogram instance
	paramters: denominator_histogram (another instance of Histogram containing the denominator
	           THx), option (option to the ROOT Divide command)
	return: none
	*/ 

	kTH1 -> Divide(kTH1, denominator_histogram -> GetTH1(), 1, 1, option);

}


//____________________________________________________________________________
void H1D::Fill(float variable_x){
	/*
	fills the TH1F of the histogram
	parameters: variable_x
	return: none
	*/

	kTH1 -> Fill(variable_x);

}


//____________________________________________________________________________
void H1D::Fill(float variable_x, float event_weight){
	/*
	fills the TH1F of the histogram
	parameters: variable_x, event_weight
	return: none
	*/

	//std::cout << "filling " << kName << " at position " << variable_x << " (" << event_weight << ")" << std::endl;

	kTH1 -> Fill(variable_x, event_weight);

}


//____________________________________________________________________________
void H1D::SetBins(int bins_x_number, float bins_x_minimum, float bins_x_maximum){
	/*
  	sets the bins of the histogram
  	parameters: bins_x_number, bins_x_minimum, bins_x_maximum
  	return: none
  	*/

	kTH1 -> SetBins(bins_x_number, bins_x_minimum, bins_x_maximum);

} 


//____________________________________________________________________________
void H1D::SetBins(std::vector<Double_t> bins_x){
	/*
	sets the bins of the histogram
	parameters: bins_x (vector of all bin separations)
	return: none
	*/

	kTH1 -> SetBins(bins_x.size() - 1, &bins_x[0]);
}


//____________________________________________________________________________
void H1D::SetSumw2(){
	/*
  	sets sumw2
  	parameters: none
  	return: none
  	*/

	kTH1 -> Sumw2();
}


//____________________________________________________________________________
bool H1D::Write(TCanvas * canvas){
	/*
  	writes the histogram to the disk
  	parameters: none
  	return: true (if written successfully), false (else)
  	*/

	kTH1 -> Draw();
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".png"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".pdf"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".root"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".C"));

	return true;

}




