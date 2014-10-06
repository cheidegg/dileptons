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


#include "src/helper/DataSample.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
DataSample::DataSample(Label sample_name, std::string sample_path, std::string info_file_path, Verbose * verbosity){
	/* 
	constructs the DataSample class 
	parameters: sample_name (name of the sample), sample_path (path to the root file) 
	return: none
	*/

	kVerbose = verbosity;
	kVerbose -> Class("DataSample");
	Initialize();
	CheckFile(sample_path);
	SetParametersFromInfoFile(sample_name, sample_path, info_file_path);

}


//____________________________________________________________________________
DataSample::~DataSample(){
	/* 
	destructs the DataSample class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void DataSample::Initialize(){
	/* 
	initializes the DataSample class
	parameters: none
	return: none
	*/


}


//____________________________________________________________________________
void DataSample::CheckFile(std::string file_path){
	/*
	checks if the given ROOT file exists and can be opened
	parameters: file_path (path to the ROOT file)
	return: none
	*/
	
	TFile * root_file = TFile::Open(Tools::ConvertStdStringToTString(file_path));
	if(root_file == NULL) kVerbose -> ErrorAndExit(10);

}


//____________________________________________________________________________
void DataSample::SetParametersFromInfoFile(Label sample_name, std::string sample_path, std::string info_file_path){
	/*
	sets the name of the sample to a given value
	parameters: newname (name to be set)
	return: none
	*/

	TString data_set_name;
	float cross_section;
	TString sample_type;
	bool found_it = false;

	std::vector<std::vector<TString> > matrix = OtherInput::ReadMatrixFromListFile(info_file_path);

	for(int i = 0; i < matrix.size(); ++i){
		if(matrix[i][1] == sample_name) {
			data_set_name = matrix[i][2];
			cross_section = matrix[i][3].Atof();
			sample_type   = matrix[i][4];
			found_it      = true;
		}
	}

	if(!found_it) kVerbose->ErrorAndExit(8);

	SetName(sample_name);
	SetCrossSection(cross_section);
	SetDataSetName(data_set_name);
	SetPath(Tools::ConvertStdStringToTString(sample_path));
	SetTypeFromTString(sample_type);

}




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR SETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void DataSample::SetCrossSection(float new_value){
	/*
	sets the cross section of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kCrossSection = new_value;

}


//____________________________________________________________________________
void DataSample::SetDataSetName(TString new_value){
	/*
	sets the data set name of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kDataSetName = new_value;

}


//____________________________________________________________________________
void DataSample::SetEventWeight(float luminosity){
	/*
	computes and sets the event weight of the sample to a value depending on the
	luminosity that is provided; note that certain variables need to have been
	set already before calling this funciton!
	parameters: luminosity (luminosity of the run)
	return: none
	*/

	if(kType == mc) kEventWeight = kCrossSection * luminosity / (kMaxEntries > 0 ? kMaxEntries : kTotEntries);
	else            kEventWeight = 1.;

}


//____________________________________________________________________________
void DataSample::SetLineColor(TString new_value){
	/*
	sets the default ROOT line color of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kLineColor = new_value;

}


//____________________________________________________________________________
void DataSample::SetLineStyle(TString new_value){
	/*
	sets the default ROOT line style of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kLineStyle = new_value;

}


//____________________________________________________________________________
void DataSample::SetMaxEntries(Long64_t new_value){
	/*
	sets the maximum number of entries of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/


	if(new_value > 0) kMaxEntries = new_value;

}


//____________________________________________________________________________
void DataSample::SetName(TString new_value){
	/*
	sets the name of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kName = new_value;
}


//____________________________________________________________________________
void DataSample::SetPath(TString new_value){
	/*
	sets the file path of the sample to a given value
	parameters: new_value (new value to be set)
	return: none
	*/

	kPath = new_value;

}


//____________________________________________________________________________
void DataSample::SetTotEntries(Long64_t new_value){
	/*
	sets the total number of entries of the sample to a given value
	parameters: new_value (number of entries to be set)
	return: none
	*/

	TH1F * event_count = (TH1F*) kRootFile -> Get("EventCount");

	if(new_value > 0) kTotEntries = new_value;
	else              kTotEntries = (Long64_t) event_count -> GetEntries();

}


//____________________________________________________________________________
void DataSample::SetType(SampleType new_value){
	/*
	sets the type of the sample to a given value
	parameters: new_value
	return: none
	*/

	kType = new_value;

}


//____________________________________________________________________________
void DataSample::SetTypeFromTString(TString new_value){
	/*
	sets the type of the sample to a given value
	parameters: new_value (new value as TString)
	return: none
	*/

	kType = Tools::ConvertTStringToSampleType(new_value);

}


/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR GETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
float DataSample::GetCrossSection(){
	/*
	returns the cross section of the sample
	parameters: none
	return: CrossSection
	*/

	return kCrossSection;

}


//____________________________________________________________________________
TString DataSample::GetDataSetName(){
	/*
	returns the data set name of the sample
	parameters: none
	return: DataSetName
	*/

	return kDataSetName;

}


//____________________________________________________________________________
float DataSample::GetEventWeight(){
	/*
	returns the event weight of the sample
	parameters: none
	return: EventWeight
	*/

	return kEventWeight;

}


//____________________________________________________________________________
TString DataSample::GetLineColor(){
	/*
	returns the default ROOT line color of the sample
	parameters: none
	return: LineColor
	*/

	return kLineColor;

}


//____________________________________________________________________________
TString DataSample::GetLineStyle(){
	/*
	returns the default ROOT line style of the sample
	parameters: none
	return: LineStyle
	*/

	return kLineStyle;

}


//____________________________________________________________________________
Long64_t DataSample::GetMaxEntries(){
	/*
	returns the maximum number of entries of the sample
	parameters: none
	return: MaxEntries
	*/

	return kMaxEntries;

}


//____________________________________________________________________________
TString DataSample::GetName(){
	/*
	returns the name of the sample
	parameters: none
	return: Name
	*/

	return kName;
}


//____________________________________________________________________________
TString DataSample::GetPath(){
	/*
	returns the file path of the sample
	parameters: none
	return: Path
	*/

	return kPath;

}


TTree * DataSample::GetTree(){

	return kRootTree;

}


//____________________________________________________________________________
Long64_t DataSample::GetTotEntries(){
	/*
	returns the total number of entries of the sample
	parameters: none
	return: TotEntries
	*/

	return kTotEntries;

}


//____________________________________________________________________________
SampleType DataSample::GetType(){
	/*
	returns the sample type of the sample
	parameters: none
	return: Type
	*/

	return kType;

}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR USING THE SAMPLES                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void DataSample::CloseTree(){
	/*
	closes and deletes the ROOT tree and file
	parameters: none
	return: none
	*/

	kRootTree -> Delete();

}


//____________________________________________________________________________
void DataSample::OpenTree(){
	/*
	opens the ROOT file and reads the ROOT tree
	parameters: none
	return: none
	*/

	kRootFile = TFile::Open(kPath);
	if(kRootFile == NULL) kVerbose -> ErrorAndExit();

	kRootTree = (TTree *) kRootFile -> Get("Analysis");
	kRootTree -> ResetBranchAddresses();
	Base::Initialize(kRootTree);

	SetTotEntries();

	CloseTree();

}







