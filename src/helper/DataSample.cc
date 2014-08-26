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

using namespace std;



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
DataSample::DataSample(TString sample_name, TString sample_path){
	/* 
	constructs the DataSample Class 
	parameters: samplename (name of the sample), samplepath (path to the root file), 
	            crosssection (cross section of the sample), sampletype (either data or mc)
	return: none
	*/

	CheckFile(sample_path);
	SetParameters(sample_name);

}


//____________________________________________________________________________
DataSample::~DataSample(){
	/* 
	destructs the DataSample Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void DataSample::CheckFile(TString file_path){
	/*
	checks if the given ROOT file exists and can be opened
	parameters: file_path (path to the ROOT file)
	return: none
	*/
	
	root_file = TFile::Open(file_path);
	if(root_file == NULL) Tools::PrintErrorAndExit(9);

}


//____________________________________________________________________________
void DataSample::SetParametersFromInfoFile(TString sample_name){
	/*
	sets the name of the sample to a given value
	parameters: newname (name to be set)
	return: none
	*/

	TString data_set_name;
	TString cross_section;
	TString sample_type;
	bool found_it = false;

	std::vector<std::vector<TString> > matrix = Tools::ReadFromInfoFile(kInfoFolder + kInfoFileDataSamples);

	for(int i = 0; i < matrix[0].size(); ++i){
		if(matrix[1][i] == sample_name) {
			data_set_name = matrix[2][i];
			cross_section = matrix[3][i];
			sample_type   = matrix[4][i];
			found_it      = true;
		}
	}

	if(!found_it) Tools::PrintErrorAndExit(8);

	SetName(sample_name);
	SetDataSetName(data_set_name);
	SetCrossSection(cross_section);
	SetSampleType(sample_type);

}




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR SETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void DataSample::SetCrossSection(float cross_section){
	/*
	sets the cross section of the sample to a given value
	parameters: cross_section (cross section to be set)
	return: none
	*/

	CrossSection = cross_section;

}


//____________________________________________________________________________
void DataSample::SetDataSetName(TString newname){
	/*
	sets the data set name of the sample to a given value
	parameters: newname (name to be set)
	return: none
	*/

	DataSetName = newname;

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

	if(Type == mc) EventWeight = CrossSection * luminosity / (MaxEntries > 0 ? MaxEntries : TotEntries);
	else           EventWeight = 1.;

}


//____________________________________________________________________________
void DataSample::SetLineColor(TString line_color){
	/*
	sets the default ROOT line color of the sample to a given value
	parameters: line_color (line color to be set)
	return: none
	*/

	LineColor = line_color;

}


//____________________________________________________________________________
void DataSample::SetLineStyle(TString line_style){
	/*
	sets the default ROOT line style of the sample to a given value
	parameters: line_style (line style to be set)
	return: none
	*/

	LineStyle = line_style;

}


//____________________________________________________________________________
void DataSample::SetMaxEntries(Long64_t max_entries){
	/*
	sets the maximum number of entries of the sample to a given value
	parameters: max_entries (number of entries to be set)
	return: none
	*/


	if(max_entries > 0) MaxEntries = max_entries;

}


//____________________________________________________________________________
void DataSample::SetName(TString new_name){
	/*
	sets the name of the sample to a given value
	parameters: new_name (name to be set)
	return: none
	*/

	Name = new_name;
}


//____________________________________________________________________________
void DataSample::SetPath(TString new_path){
	/*
	sets the file path of the sample to a given value
	parameters: new_path (path to be set)
	return: none
	*/

	Path = new_path;

}


//____________________________________________________________________________
void DataSample::SetTotEntries(Long64_t tot_entries = 0){
	/*
	sets the total number of entries of the sample to a given value
	parameters: tot_entries (number of entries to be set)
	return: none
	*/

	TH1F * EventCount = (TH1F*) RootFile->Get("EventCount");

	if(tot_entries > 0) TotEntries = tot_entries;
	else                TotEntries = EventCount->GetEntries();

}


//____________________________________________________________________________
void DataSample::SetType(SampleType new_type){
	/*
	sets the sample type of the sample to a given value
	parameters: new_type (type to be set)
	return: none
	*/

	Type = new_type;

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

	return CrossSection;

}


//____________________________________________________________________________
TString DataSample::GetDataSetName(){
	/*
	returns the data set name of the sample
	parameters: none
	return: DataSetName
	*/

	return DataSetName;

}


//____________________________________________________________________________
float DataSample::GetEventWeight(){
	/*
	returns the event weight of the sample
	parameters: none
	return: EventWeight
	*/

	return EventWeight;

}


//____________________________________________________________________________
TString DataSample::GetLineColor(){
	/*
	returns the default ROOT line color of the sample
	parameters: none
	return: LineColor
	*/

	return LineColor;

}


//____________________________________________________________________________
TString DataSample::GetLineStyle(){
	/*
	returns the default ROOT line style of the sample
	parameters: none
	return: LineStyle
	*/

	return LineStyle;

}


//____________________________________________________________________________
Long64_t DataSample::GetMaxEntries(){
	/*
	returns the maximum number of entries of the sample
	parameters: none
	return: MaxEntries
	*/

	return MaxEntries;

}


//____________________________________________________________________________
TString DataSample::GetName(){
	/*
	returns the name of the sample
	parameters: none
	return: Name
	*/

	return Name;
}


//____________________________________________________________________________
TString DataSample::GetPath(){
	/*
	returns the file path of the sample
	parameters: none
	return: Path
	*/

	return Path;

}


//____________________________________________________________________________
Long64_t DataSample::GetTotEntries(){
	/*
	returns the total number of entries of the sample
	parameters: none
	return: TotEntries
	*/

	return TotEntries;

}


//____________________________________________________________________________
SampleType DataSample::GetType(){
	/*
	returns the sample type of the sample
	parameters: none
	return: Type
	*/

	return Type;

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

	delete RootFile, RootTree;

}


//____________________________________________________________________________
void DataSample::GetTreeEntry(Long64_t entry){
	/*
	returns a given entry of the ROOT tree
	parameters: entry (index of the entry to be returned)
	return: none
	*/

	RootTree -> GetEntry(entry);

}


//____________________________________________________________________________
void DataSample::OpenTree(){
	/*
	opens the ROOT file and reads the ROOT tree
	parameters: none
	return: none
	*/

	RootFile = TFile::Open(Path);
	if(RootFile == NULL) Tools::PrintErrorAndExit(9);

	RootTree = (TTree *) RootFile->Get("Analysis");
	RootTree -> ResetBranchAddresses();
	Init(RootTree);

	SetTotEntries();

}







