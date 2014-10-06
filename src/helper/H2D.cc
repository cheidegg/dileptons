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


#include "src/helper/H2D.hh"






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CLASS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
H2D::H2D(int creation_time, Verbose * verbosity, HistogramMode mode, bool set_sumw2){
	/*
	constructs the H2D class
	parameters: none
	return: none
	*/

	kVerbose = verbosity;
	kVerbose -> Class("H2D");
	Initialize(creation_time, mode, set_sumw2);

}


//____________________________________________________________________________
H2D::~H2D(){
	/*
	destructs the H2D class
	paramters: none
	return: none
	*/

}


//____________________________________________________________________________
void H2D::Initialize(int creation_time, HistogramMode mode, bool set_sumw2){
	/*
	initializes the H2D class
	paramters: creation_time (time since program start in miliseconds), mode (the
	           mode of the histogram), set_sumw2 (true if we set sumw2, false else)
	return: none
	*/

	kMode = mode;
	
	std::string time_id = Tools::ConvertIntToStdString(creation_time);

	kTH2 = new TH2F(Tools::ConvertStdStringToCString("TH2_" + time_id), "H", 1, 0, 1, 1, 0, 1);

	if(set_sumw2)
		SetSumw2();

}


//____________________________________________________________________________
void H2D::SetMajorParameters(TString output_path, TString name){
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
void H2D::SetHistogramMode(HistogramMode new_value){
	/*
	sets the mode of the histogram to a new value
	parameters: new_value
	return: none
	*/

	kMode = new_value;

}


//____________________________________________________________________________
void H2D::SetName(TString new_value){
	/*
	sets the name of the histogram to a new value
	parameters: new_value
	return: none
	*/

	kName = new_value;

}


//____________________________________________________________________________
void H2D::SetOutputPath(TString new_value){
	/*
	sets the output path of the histogram to a new value
	parameters: new_value
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
HistogramMode H2D::GetHistogramMode(){
	/*
	returns the mode of the histogram
	parameters: none
	return: kMode
	*/

	return kMode;

}


//____________________________________________________________________________
TString H2D::GetName(){
	/*
	returns the unique name of the output
	parameters: none
	return: kName
	*/
	
	return kName;

}


//____________________________________________________________________________
TString H2D::GetOutputPath(){
	/*
	returns the unique name of the output
	parameters: none
	return: kOutputPath
	*/
	
	return kOutputPath;

}


//____________________________________________________________________________
TH2F * H2D::GetTH2(){
	/*
	returns the TH2F of the histogram
	parameters: none
	return: kTH2
	*/

	return kTH2;

}




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR HISTOGRAM OPTIONS                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void H2D::Divide(H2D * denominator_histogram, Option_t* option){
	/*
	divides the THx of the current histogram instance by the THx of a given histogram instance
	paramters: denominator_histogram (another instance of Histogram containing the denominator
	           THx), option (option to the ROOT Divide command)
	return: none
	*/ 

	kTH2 -> Divide(kTH2, denominator_histogram -> GetTH2(), 1, 1, option);

}


//____________________________________________________________________________
void H2D::Fill(float variable_x, float variable_y){
	/*
	fills the TH2F of the histogram
	parameters: variable_x, variable_y
	return: none
	*/

	kTH2 -> Fill(variable_x, variable_y);

}


//____________________________________________________________________________
void H2D::Fill(float variable_x, float variable_y, float event_weight){
	/*
	fills the TH2F of the histogram
	parameters: variable_x, variable_y, event_weight
	return: none
	*/

	kTH2 -> Fill(variable_x, variable_y, event_weight);

}


//____________________________________________________________________________
void H2D::SetBins(int bins_x_number, float bins_x_minimum, float bins_x_maximum, int bins_y_number, float bins_y_minimum, float bins_y_maximum){
	/*
	sets the bins of the histogram
	parameters: bins_x_number, bins_x_minimum, bins_x_maximum, 
	            bins_y_number, bins_y_minimum, bins_y_maximum
	return: none
	*/

	kTH2 -> SetBins(bins_x_number, bins_x_minimum, bins_x_maximum, bins_y_number, bins_y_minimum, bins_y_maximum);

} 


//____________________________________________________________________________
void H2D::SetBins(std::vector<Double_t> bins_x, std::vector<Double_t> bins_y){
	/*
	sets the bins of the histogram
	parameters: bins_x (vector of all bin separations)
	return: none
	*/

	kTH2 -> SetBins(bins_x.size()-1, &bins_x[0], bins_y.size()-1, &bins_y[0]);

}


//____________________________________________________________________________
void H2D::SetSumw2(){
	/*
	sets sumw2
	parameters: none
	return: none
	*/

	kTH2 -> Sumw2();
}


//____________________________________________________________________________
bool H2D::Write(TCanvas * canvas){
	/*
	writes the histogram to the disk
	parameters: canvas (the canvas to write)
	return: true (if written successfully), false (else)
	*/

	std::cout << "managed to get here " << std::endl;
	canvas -> ls();

	kTH2 -> Draw();
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".png"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".pdf"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".root"));
	canvas -> SaveAs(Tools::ConvertStdStringToCString(Tools::ConvertTStringToStdString(kOutputPath) + Tools::ConvertTStringToStdString(kName) + ".C"));

	return true;
}


