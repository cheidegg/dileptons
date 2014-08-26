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


#include "src/head/Dileptons.hh"

using namespace std;
using boost::filesystem;



/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
Dileptons::Dileptons(TString configfile){
	/* 
	constructs the Dileptons Class 
	parameters: configfile (path to configuration file)
	return: none
	*/

	Initialize();
	CheckResources();
	LoadConfigurationFile(configfile);
	CheckConfiguration();

}


//____________________________________________________________________________
Dileptons::~Dileptons(){
	/* 
	destructs the Dileptons Class
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Dileptons::Initialize(){
	/*
	initializes the Dileptons class, defining standard values of certain 
        variables
	parameters: none
	return: none
	*/

	kUserName       = Tools::GetUserName();

	kInfoFolder     = "info/";
	kInputFolder    = "input/";
	kOutputFolder   = "output/";
	kTemplateFolder = "templates/";

	kInfoFileBasicKinematicObjects      = "basic_kinematic_objects.txt";
	kInfoFileDataSamples                = "data_samples.txt";
	kInfoFileKinematicElectronVariables = "kinematic_electron_variables.txt";
	kInfoFileKinematicEventVariables    = "kinematic_event_variables.txt";
	kInfoFileKinematicJetVariables      = "kinematic_jet_variables.txt";
	kInfoFileKinematicMuonVariables     = "kinematic_muon_variables.txt";
	kInfoFileKinematicPhotonVariables   = "kinematic_photon_variables.txt";
	kInfoFileKinematicTauVariables      = "kinematic_tau_variables.txt";
	kInfoFileModuleGroups               = "module_groups.txt";
	kInfoFileModuleListAnalysis         = "module_list_analysis.txt";
	kInfoFileSystemMessages             = "system_messages.txt";

	kTemplateFileTag                    = "tag.sh";

}


//____________________________________________________________________________
void Dileptons::CheckConfiguration(){
	/*
	checks if the given configuration obeys all rules (e.g. if the AKROSD
	strings are legal), if all variables are given and if their values make 
	at least some sense (i.e. if their values are within allowed limits),
	and returns error message and exists the code in case something is illegal
	parameters: none
	return: none
	*/



	for(int i = 0; i < cDVDefinitions.size(); ++i) 
		if(!AKROSD::CheckStringForDefinedVariables(cDVDefinitions[i], cOSDefinitions)) 
			Tools::PrintErrorAndExit();

	for(int i = 0; i < cESDefinitions.size(); ++i) 
		if(!AKROSD::CheckStringForEventSelection(cESDefinitions[i], cOSDefinitions)) 
			Tools::PrintErrorAndExit();

	for(int i = 0; i < cOSDefinitions.size(); ++i) 
		if(!AKROSD::CheckStringForObjectSelection(cOSDefinitions[i])) 
			Tools::PrintErrorAndExit();

}


//____________________________________________________________________________
void Dileptons::CheckResources(){
	/*
	checks if all resources are available, i.e. all info files, templates, 
	input and ouput directories, config file, and returns error message and 
	exits the code in case something is missing 
	parameters: none
	return: none
	*/
	

	// Since we want to use predefined error messages, we need to make sure the error messages file exists.
	if(access(kInfoFolder + kInfoFileErrorMessages, F_OK && R_OK) != 0){
		cerr << "The info file containing error messages cannot be found or reading is not permitted." << endl;
		cerr << "Please provide this info file with correct name, location and permission in order to run Dileptons." << endl;
		exit(1);
	}

	// check existence of directories
	if(!exists(kInfoFolder))      Tools::PrintErrorAndExit();
	if(!exists(kInputFolder))     Tools::PrintErrorAndExit();
	if(!exists(kOutputFolder))    Tools::PrintErrorAndExit();
	if(!exists(kTemplatesFolder)) Tools::PrintErrorAndExit();

	// check existence and permissions of info files
	if(access(kInfoFolder + kInfoFileBasicKinematicObjects     , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileDataSamples               , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicElectronVariables, F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicEventVariables   , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicJetVariables     , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicMuonVariables    , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicPhotonVariables  , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileKinematicTauVariables     , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileModuleGroups              , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileModuleListAnalysis        , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();
	if(access(kInfoFolder + kInfoFileSystemMessages            , F_OK && R_OK) != 0) Tools::PrintErrorAndExit();


	// checks write permission of output folder by creating an empty txt file and deleting it right after
	// note: the read permissions of the input folder are checked at a later point in time, where
	// the given samples are read. if they cannot be read, there will be an error
	


	

}


//____________________________________________________________________________
void Dileptons::CopyOutputOnAFSWebspace(){
	/*
	copies configplot and modules onto AFS webspace
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Dileptons::CreateCopyableConfigurationFile(TString configfile){
	/*
	creates a copyable configuration file out of a given version; copyable
	means that we strip off all comments and empty lines, we order the 
	variables according to their type (n,v,m,...) and name, we sort the
	statements in every AKROSD string and rename the config file; this is
	an essential step for the input-output management as we make configurations
	comparable 
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Dileptons::CreateOutputStructure(){
	/*
	creates the entire output structure (confplot and modules) in the local
	output-folder and copies the respective templates
	parameters: none
	return: none
	*/

}


//____________________________________________________________________________
void Dileptons::LoadConfigurationFile(TString configuration_file){
	/*
	loads the configuration file and reads the configuration variables
	parameters: configuratoin_file (path to the configuration file)
	return: none
	*/

	char buffer[1000];
	char symbol[1], type[20], name[100], value[500], comment[300];

	ifstream IN(configfile);
	if(!IN.is_open()) Tools::PrintErrorAndExit(5);

	while(IN.getline(buffer, 1000, '\n')){

		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;

		if(sscanf(buffer, "%s\t%s\t\t%s\t\t%s\t\t%s", symbol, type, name, value, comment) <= 3) continue;


		if(symbol == 'n'){
			if      (type == "TString" && name == "UserName"  ) cUserName      = value;
			else if (type == "TString" && name == "InputPath" ) cInputPath     = value;
			else if (type == "TString" && name == "OutputPath") cOutputPath    = value;
			else if (type == "TString" && name == "AFSPath"   ) cAFSPath       = value;
			else if (type == "int"     && name == "Verbose"   ) cVerbose       = value.Atoi();
			else if (type == "TString" && name == "Mode"      ) cMode          = value;
			else if (type == "TString" && name == "RunOn"     ) cRunOn         = value;
			else if (type == "TString" && name == "Modules"   ) cModules       = value;
			else if (type == "int"     && name == "ModuleList") cModuleList    = value.Atoi();
		}

		if(symbol == 'v'){
			else if (type == "float"   && name == "Luminosity") cLuminosity    = value.Atof();
		}

		if(symbol == 'o'){
			if      (type == "AKROSD"  && name != ""          ) cOSDefinitions[name] = value;
		}

		if(symbol == 'd'){
			if      (type == "AKROSD"  && name != ""          ) cDVDefinitions[name] = value;
		}

		if(symbol == 'e'){
			if      (type == "AKROSD"  && name != ""          ) cESDefinitions[name] = value;
		}

		if(symbol == 's'){
			if      (type == "TString" && name != ""          ) cSamples[name]       = new DataSample(name, value);
		}

		if(symbol == 'm'){
			if      (type == "int"     && name != ""          ) cSamples[name].SetMaxEntries(value.Atoi());
		}
			
	}
}


//_____________________________________________________________________________________
void Dileptons::TagCode(TString version, TString configplot) {
	/*
	uses a template to create a lightweight tag automatically after running	the code
	paramters: version (current version number), configplot (current configplot)
	return: none
	*/
	
	TString template_text;
	ifstream template_file;
	template_file.open(kTemplateFolder + kTemplateFileTag);
	
	if(template_file.is_open())
		while(TString line = getline(template_file, line))
			strcat(template_text, line);
		
		template_file.close();
		
		template_text.ReplaceAll("VERSION", version);
		template_text.ReplaceAll("CONFIGPLOT", configplot);
		
		ofstream execute_file;
		execute_file.open("tag.sh");
		execute_file << template_text;
		execute_file.close();
		
		system("chmod 0755 tag.sh")
		system("bash tag.sh");
		system("rm tag.sh");
	
	}
}







/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR DOING PHYSICS                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool Dileptons::KinematicRegionSelection(AKROSD regionselection){
	/*
	implementing the AKROSD selection for a given kinematic region
	parameters: eventselection (AKROSD string that determines the selection for the event)
	return: true (if event is selected), false (else)
	*/ 


	// event quantities using lepton selection

	if(ElPt->size() > 0) {
		for(int j=0; j < ElPt->size(); ++j){

			for() { // loop over all electron-derived objects
				++NumberOf[""];
				++NumberOf[""];
				IndexOf[""] = j;
			}

			if(ElectronSelection(j)) {
				++NumberOf[Electrons];
				++NumberOfLeptons;
				IndexOfElectron.push_back(j);
			}
			if(LooseElectronSelection(j)) {
				++NumberOfLooseElectrons;
				++NumberOfLooseLeptons;
				IndexOfLooseElectron.push_back(j);
			}
			if(TightElectronSelection(j)) {
				++NumberOfTightElectrons;
				++NumberOfTightLeptons;
				IndexOfTightElectron.push_back(j);
			}
			if(VetoElectronSelection(j)) {
				++NumberOfVetoElectrons;
				++NumberOfVetoLeptons;
				IndexOfVetoElectron.push_back(j);
			}		
		}
	}

	if(MuPt->size() > 0) {
		for(int j=0; j < MuPt->size(); ++j){
			if(MuonSelection(j)) {
				++NumberOfMuons;
				++NumberOfLeptons;
				IndexOfMuon.push_back(j);
			}
			if(LooseMuonSelection(j)) {
				++NumberOfLooseMuons;
				++NumberOfLooseLeptons;
				IndexOfLooseMuon.push_back(j);
			}
			if(TightMuonSelection(j)) {
				++NumberOfTightMuons;
				++NumberOfTightLeptons;
				IndexOfTightMuon.push_back(j);
			}		
			if(VetoMuonSelection(j)) {
				++NumberOfVetoMuons;
				++NumberOfVetoLeptons;
				IndexOfVetoMuon.push_back(j);
			}
		}
	}



	// event quantities using jet selection

	if(JetRawPt->size() > 0) {
		for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){

			if(AwayJetSelection(thisjet)) {
				++NumberOfAwayJets;
				IndexOfAwayJet.push_back(thisjet);
			}
			if(BJetSelection(thisjet)) {
				++NumberOfBJets;
				IndexOfBJet.push_back(thisjet);
			}
			if(JetSelection(thisjet)) {
				++NumberOfJets;
				IndexOfJet.push_back(thisjet);
			}
		}
	}



	// event quantities using other variables

	float DeltaPhiAwayJetLepton = Util::DeltaPhi(JetPhi->at(jet), LepPhi->at(lep));



	// perform event selection from AKROSD string




	return false;

}


//____________________________________________________________________________
bool Dileptons::DefinedEventVariable(AKROSD eventdefinition){
	/*
	implements the definition of devined event variables via AKROSD string
	parameters: eventdefinition (AKROSD string that determines the definition of the variable)
	return: true (if object is selected), false (else)
	*/ 



	// perform object selection from AKROSD string


	return false;

}


//____________________________________________________________________________
bool Dileptons::KinematicObjectSelection(AKROSD objectselection){
	/*
	implementing the AKROSD selection for a given kinematic object
	parameters: objectselection (AKROSD string that determines the selection for the object)
	return: true (if object is selected), false (else)
	*/ 



	// perform object selection from AKROSD string


	return false;

}






























//____________________________________________________________________________
void Fakerates::doStuff(){
	
	TString OutputFilename = fOutputDir + fName + "_ratios.root";
	if(!Util::dirExists(fOutputDir)) Util::MakeOutputDir(fOutputDir);
	TFile *pFile = new TFile(OutputFilename, "RECREATE");
	
	if(fDataType == 1 || fDataType == 2) {
		loop(pFile);
	}
}


//____________________________________________________________________________
void Fakerates::loop(TFile* pFile){
	/* 
	does the main procedure looping over all events
	parameters: none
	return: none
	*/

	Long64_t ntot = 0;

	// define histograms
	bookHistos();

	// open input file and read the tree
	TFile * file_ = TFile::Open(fInputFile);
	if(file_ == NULL ) {
		cout << "*******************************************************" << endl;
		cout << " ERROR: THE FILE YOU ARE TRYING TO READ ISN'T OPEN. CHECK IT'S EXISTENCE!!!" << endl;
		cout << " exiting ...                                            " << endl;
		cout << "*******************************************************" << endl;
		exit(0);
	}
	TTree * tree_ = (TTree *) file_->Get("Analysis"); // tree name has to be named "Analysis"
	tree_->ResetBranchAddresses();
	Init(tree_);
	Long64_t tot_events = tree_->GetEntriesFast();
   
	// calculate the eventweight
	TH1F * EventCount = (TH1F*) file_->Get("EventCount");
	Double_t Ngen = EventCount->GetEntries();
	if(!fIsData) fLumiweight = fXSec * fLuminosity / (fMaxSize>0?fMaxSize:Ngen);
	else fLumiweight = 1.;
	cout << " going to loop over " << (fMaxSize>0?fMaxSize:Ngen) << " events..." << endl;
	cout << " eventweight is " << fLumiweight << endl;


	int mu(-1), jet(-1);


	// loop on events in the tree
	for (Long64_t jentry=0; jentry<tot_events; jentry++) {
		if(jentry > (fMaxSize>0?fMaxSize:Ngen)) break;
		//printProgress(jentry,tot_events,fName);

		tree_->GetEntry(jentry);
		ntot++;

		float eventweight = fLumiweight;
		if(!fIsData && fPUweight) eventweight *= PUWeight;

		//smearAllJets(); // Jet-Energy Smearing, leave commented for snyching

		if(fClosure) {
			fillFRPlotsTTBar(eventweight);
		}
		else {
			fillFRPlots(eventweight);
			//fillHLTPlots(eventweight);
		}
	}

	cout << " mu: nevents passing lepton selection: " << fCutflow_afterLepSel << endl;
	cout << " mu: nevents passing jet    selection: " << fCutflow_afterJetSel << endl;
	cout << " mu: nevents passing MET    selection: " << fCutflow_afterMETCut << endl;
	cout << " mu: nevents passing MT     selection: " << fCutflow_afterMTCut  << endl;
	cout << " i just looped on " << ntot << " events." << endl;

	cout << " fCounter_all             = " << fCounter_all        << " (" << (float) fCounter_all        / (float) fCounter_all << ") " << endl;
	cout << " fCounter_trigger         = " << fCounter_trigger    << " (" << (float) fCounter_trigger    / (float) fCounter_all << ") " << endl;
	cout << " fCounter_loose           = " << fCounter_loose      << " (" << (float) fCounter_loose      / (float) fCounter_all << ") " << endl;
	cout << " fCounter_veto            = " << fCounter_veto       << " (" << (float) fCounter_veto       / (float) fCounter_all << ") " << endl;
	cout << " fCounter_jet (40)        = " << fCounter_jet        << " (" << (float) fCounter_jet        / (float) fCounter_all << ") " << endl;
	cout << " fCounter_jet (30)        = " << fCounter_jet30      << " (" << (float) fCounter_jet30      / (float) fCounter_all << ") " << endl;
	cout << " fCounter_met             = " << fCounter_met        << " (" << (float) fCounter_met        / (float) fCounter_all << ") " << endl;
	cout << " fCounter_mt              = " << fCounter_mt         << " (" << (float) fCounter_mt         / (float) fCounter_all << ") " << endl;
	cout << " fCounter_CERN_small      = " << fCounter_CERN_small << " (" << (float) fCounter_CERN_small / (float) fCounter_all << ") " << endl;
	cout << " fCounter_CERN_large      = " << fCounter_CERN_large << " (" << (float) fCounter_CERN_large / (float) fCounter_all << ") " << endl;
	cout << " fCounter_origin (ttbar)  = " << fCounter_origin     << " (" << (float) fCounter_origin     / (float) fCounter_all << ") " << endl;


	delete file_, tree_;

	// write histograms in output file
	writeHistos(pFile);
	pFile->Close();

}


//____________________________________________________________________________
float Fakerates::getSigmaMC(float Pt, float Eta) {
  
	float N, S, m;

	if( fabs(Eta) < 0.5 ) {
		N = 3.96859;
		S = 0.18348;
		m = 0.62627;
	} 
	else if( fabs(Eta) < 1. ) {
		N = 3.55226;
		S = 0.24026;
		m = 0.52571;
	} 
	else if( fabs(Eta) < 1.5) {
		N = 4.54826;
		S = 0.22652;
		m = 0.58963;
	} 
	else if( fabs(Eta) < 2. ) {
		N = 4.62622;
		S = 0.23664;
		m = 0.48738;
	} 
	else if( fabs(Eta) < 2.5) {
		N = 2.53324;
		S = 0.34306;
		m = 0.28662;
	} 
	else if( fabs(Eta) < 3. ) {
		N = -3.33814;
		S = 0.73360;
		m = 0.08264;
	} 
	else if( fabs(Eta) < 5. ) {
		N = 2.95397;
		S = 0.11619;
		m = 0.96086;
	}

	return sqrt((N * fabs(N) ) + (S * S) * pow(Pt, m + 1));
}


//____________________________________________________________________________
void Fakerates::smearAllJets(){

	if(!fIsData){
	
		TLorentzVector TLV_Jet_old, TLV_Jet_new, TLV_MET;
		TLV_MET.SetPtEtaPhiM(getMET(),0,getMETPhi(),0);

		for(int i=0; i<JetPt->size(); ++i){

			float sigmaMC = getSigmaMC( JetPt->at(i), JetEta->at(i) ) / JetPt->at(i);
			float factor  = fRandom -> Gaus( 1.0, sigmaMC );  
		
			TLV_Jet_old.SetPtEtaPhiE(JetPt->at(i), JetEta->at(i), JetPhi->at(i), JetEnergy->at(i));
			TLV_MET += TLV_Jet_old;

			JetPt->at(i) = JetPt->at(i) * factor;
	
			TLV_Jet_new.SetPtEtaPhiE(JetPt->at(i), JetEta->at(i), JetPhi->at(i), JetEnergy->at(i));
			TLV_MET -= TLV_Jet_new;
		}

		setMET(TLV_MET.Pt());
		setMETPhi(TLV_MET.Phi());
	}
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getLepPt() {
	/*
	return Pt of the lepton
	parameters: none
	return: Pt
	*/

	if(fDataType == 2) return ElPt;
	else               return MuPt;
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getOpLepPt() {
	/*
	return Pt of the opposite flavor lepton
	parameters: none
	return: Pt
	*/

	if(fDataType == 2) return MuPt;
	else               return ElPt;
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getLepEta() {
	/*
	return Eta of the lepton
	parameters: none
	return: Eta
	*/
	if(fDataType == 2) return ElEta;
	else               return MuEta;
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getLepPhi() {
	/*
	return Phi of the lepton
	parameters: none
	return: Phi
	*/
	if(fDataType == 2) return ElPhi;
	else               return MuPhi;
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getLepPFIso() {
	/*
	return Iso of the lepton
	parameters: none
	return: Iso
	*/
	if(fDataType == 2) return ElPFIso;
	else               return MuPFIso;
}


//____________________________________________________________________________
std::vector<float, std::allocator<float> >* Fakerates::getLepD0() {
	/*
	return D0 of the lepton
	parameters: none
	return: D0
	*/

	if(fDataType == 2) return ElD0;
	else               return MuD0;
}


//____________________________________________________________________________
std::vector<bool, std::allocator<bool> >* Fakerates::getLepIsPrompt() {
	/*
	return IsPrompt of the lepton
	parameters: none
	return: ID
	*/

	if(fDataType == 2) return ElIsPrompt;
	else               return MuIsPrompt;
}


//____________________________________________________________________________
void Fakerates::setLepIsPrompt(int index, bool newvalue) {
	/*
	set the value of IsPrompt of the lepton
	parameters: index (index of the lepton), newvalue (new value to be set)
	return: none
	*/

	if(fDataType == 2) ElIsPrompt->at(index) = newvalue;
	else               MuIsPrompt->at(index) = newvalue;
}


//____________________________________________________________________________
//std::vector<int, std::allocator<int> >* Fakerates::getLepID() {
//	/*
//	return ID of the lepton
//	parameters: none
//	return: ID
//	*/
//
//	if(fDataType == 2) return ElID;
//	else               return MuID;
//}


//____________________________________________________________________________
std::vector<int, std::allocator<int> >* Fakerates::getLepMID() {
	/*
	return MID of the lepton
	parameters: none
	return: MID
	*/

	if(fDataType == 2) return ElMID;
	else               return MuMID;
}


//____________________________________________________________________________
std::vector<int, std::allocator<int> >* Fakerates::getLepGMID() {
	/*
	return GMID of the lepton
	parameters: none
	return: GMID
	*/

	if(fDataType == 2) return ElGMID;
	else               return MuGMID;
}


//____________________________________________________________________________
bool Fakerates::isFRRegionLepEvent(int &lep, int &jet, float jetcut, bool count = false){
	/*
	checks, whether the event contains exactly one lepton and at least one away-jet in the calibration region
	parameters: &lep (address of lepton index), &jet (address of away-jet index), jetcut
	return: true (if muon is in calibration region), false (else)
	*/ 

	std::vector<int> looselep_inds;
	std::vector<int> awayjet_inds;
	std::vector<float, std::allocator<float> >* LepPt    = getLepPt();
	std::vector<float, std::allocator<float> >* LepEta   = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi   = getLepPhi();
	std::vector<float, std::allocator<float> >* OpLepPt  = getOpLepPt();
	int nloose(0), nveto_add(0);
	int nawayjets(0), jetind(-1);

	if(count) ++fCounter_all;

	//cout << "start FRRegionLepEvent" << endl;


	// Event fails HLT muon trigger (if data) then return false
	if(fLepTriggerMC || fIsData) {
		if      (fLepTrigger == "Mu17"   && !HLT_MU17              ) { return false; }
		else if (fLepTrigger == "Mu24"   && !HLT_MU24              ) { return false; }
		else if (fLepTrigger == "Mu40"   && !HLT_MU40              ) { return false; }
		else if (fLepTrigger == "Ele8"   && !HLT_ELE8_TIGHT        ) { return false; }
		else if (fLepTrigger == "Ele17"  && !HLT_ELE17_TIGHT       ) { return false; }
		else if (fLepTrigger == "Ele17J" && !HLT_ELE17_JET30_TIGHT ) { return false; }
		else                                                         {               }
	}

	if(count) ++fCounter_trigger;


	// muon Pt is not reasonable then return false
	if(LepPt->size() < 1) return false;


	// count numbers of loose and veto muons in the event
	for(int j=0; j < LepPt->size(); ++j){
		if(isLooseLepton(j) && LepPt->at(j) > fLepPtCut){
			nloose++;
			lep = j;
			looselep_inds.push_back(j);		
		}
		else if(isLooseLepton(j) && LepPt->at(j) > 10.){
			++nveto_add;
		}

		for(int k=0; k < OpLepPt->size(); ++k)
			if(isLooseOpLepton(k) && OpLepPt->at(k) > 10.)
				++nveto_add;
	}


	// require exactly one loose muon and no additional veto muons
	if(nloose    != 1) return false;

	if(count) ++fCounter_loose;
	
	
	fCutflow_afterLepSel++;
	if(nveto_add != 0) return false;

	if(count) ++fCounter_veto;


	//if(count) cout << Form("%d\t%d\t%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\t%.2f\t%.2f", Run, Lumi, Event, LepPt->at(lep), getJetPt(getAwayJet(lep)), isTightLepton(lep), 0.0, -99.0, getMET(), getMT(lep)) << endl;


	// Jet Pt is not reasonable then return false
	if(JetRawPt->size() < 1) return false;


	// count the number of away jets
	for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){
		if(!isGoodJet(thisjet, jetcut, fAwayJetBTagCut)) continue;
		if(Util::GetDeltaR(JetEta->at(thisjet), LepEta->at(lep), JetPhi->at(thisjet), LepPhi->at(lep)) < 1.0 ) continue;
		nawayjets++;
		awayjet_inds.push_back(thisjet);
	}


	// no away jet found then return false 
	if(awayjet_inds.size() < 1) return false;
	fCutflow_afterJetSel++;

	if(count) ++fCounter_jet;
	if(jetcut==30.) ++fCounter_jet30;


	// set jet index on the hardest jet
	jet = awayjet_inds[0];
	if(awayjet_inds.size() > 1)
		for(int thisjet=0; thisjet < nawayjets; ++thisjet)
			if(getJetPt(awayjet_inds[thisjet]) > getJetPt(jet) ) jet = awayjet_inds[thisjet];


	// phi cut
	if(fAwayJetDPhiCut > 0. && Util::DeltaPhi(JetPhi->at(jet), LepPhi->at(lep)) < fAwayJetDPhiCut) return false;


    return true;

}


//____________________________________________________________________________
bool Fakerates::isFRRegionLepEventTTBar(int origin = 0){
	/*
	checks, whether the event is ok or not
	parameters: none
	return: true (if event is ok), false (else)
	*/ 
	

	// Event fails HLT muon trigger (if data) then return false
	if(fLepTriggerMC || fIsData) {
		if      (fLepTrigger == "Mu17"   && !HLT_MU17              ) { return false; }
		else if (fLepTrigger == "Mu24"   && !HLT_MU24              ) { return false; }
		else if (fLepTrigger == "Mu40"   && !HLT_MU40              ) { return false; }
		else if (fLepTrigger == "Ele8"   && !HLT_ELE8_TIGHT        ) { return false; }
		else if (fLepTrigger == "Ele17"  && !HLT_ELE17_TIGHT       ) { return false; }
		else if (fLepTrigger == "Ele17J" && !HLT_ELE17_JET30_TIGHT ) { return false; }
		else                                                         {               }
	}



	return true;
}


//____________________________________________________________________________
int Fakerates::getLeptonOrigin(int mid, int gmid, int id = 0){
	/*
	returns the original quark flavor of the lepton
	parameters: mid (mother id), gmid (grandmother id)
	return: (0 is reserved for all), 1 (W, prompt), 2 (bottom), 3 (charm), 4 (other, light-flavor), 5 (other, unidentified)
	*/ 

	int mother           = (int) fabs(mid);
	int grandmother      = (int) fabs(gmid);
	int mother_3dig      = mother % 1000;
	int grandmother_3dig = grandmother % 1000;

	if      (mother == 24 || grandmother == 24                                                               ) return 1;
	else if (mother == 5 || grandmother == 5                                                                 ) return 2;
	else if (grandmother >= 5000 && grandmother <= 5999                                                      ) return 2;
	else if ((grandmother < 1000 || grandmother > 9999) && grandmother_3dig >= 500 && grandmother_3dig <= 599) return 2;
	else if (mother >= 5000 && mother <= 5999                                                                ) return 2;
	else if ((mother < 1000 || mother > 9999) && mother_3dig >= 500 && mother_3dig <= 599                    ) return 2;
	else if (mother == 4 || grandmother == 4                                                                 ) return 3;
	else if (grandmother >= 4000 && grandmother <= 4999                                                      ) return 3;
	else if ((grandmother < 1000 || grandmother > 9999) && grandmother_3dig >= 400 && grandmother_3dig <= 499) return 3;
	else if (mother >= 4000 && mother <= 4999                                                                ) return 3;
	else if ((mother < 1000 || mother > 9999) && mother_3dig >= 400 && mother_3dig <= 499                    ) return 3;
	else if (grandmother == 1 || grandmother == 2 || grandmother == 3                                        ) return 4;
	else if (mother == 1 || mother == 2 || mother == 3                                                       ) return 4;
	else if ((mother > 999 || mother < 10000) && mother_3dig >= 100 && mother_3dig <= 399                    ) return 4;
	else if (mother == 6 || grandmother == 6                                                                 ) return 1;
	else return 5;//cout << "MID: " << mother << " GMID: " << grandmother << endl;

	//if      (grandmother == 4                                                                                ) return 2;
	//else if (grandmother == 5                                                                                ) return 1;
	//else if (grandmother == 1 || grandmother == 2 || grandmother == 3                                        ) return 3;
	//else if (grandmother >= 4000 && grandmother <= 4999                                                      ) return 2;
	//else if (grandmother >= 5000 && grandmother <= 5999                                                      ) return 1;
	//else if ((grandmother < 1000 || grandmother > 9999) && grandmother_3dig >= 400 && grandmother_3dig <= 499) return 2;
	//else if ((grandmother < 1000 || grandmother > 9999) && grandmother_3dig >= 500 && grandmother_3dig <= 599) return 1;
	//else if (mother == 24                                                                                    ) return 6;
	//else if (mother >= 4000 && mother <= 4999                                                                ) return 2;
	//else if (mother >= 5000 && mother <= 5999                                                                ) return 1;
	//else if ((mother < 1000 || mother > 9999) && mother_3dig >= 400 && mother_3dig <= 499                    ) return 2;
	//else if ((mother < 1000 || mother > 9999) && mother_3dig >= 500 && mother_3dig <= 599                    ) return 1;
	//else if ((mother > 999 || mother < 10000) && mother_3dig >= 100 && mother_3dig <= 399                    ) return 3;
	//else if (mother == 6 || grandmother == 6                                                                 ) return 4;
	//else if (grandmother == 24                                                                               ) return 6;
	//else return 5; //cout << "MID: " << mother << " GMID: " << grandmother << endl;

	return 5;
}


//____________________________________________________________________________
bool Fakerates::isLooseMuon(int index){
	/* 
	checks, if the muon is loose
	parameters: index (index of the particle)
	return: true (if muon is loose), false (else)
	*/

	if(MuPt->at(index) < 10.) return false;
	if(!MuIsLoose->at(index)) return false;
	//if(fabs(MuD0->at(index)) > 0.1) return false;
	if(fLepD0Cut > 0.0 && fabs(MuD0->at(index)) > fLepD0Cut) return false; // leave this commented for synching!!
	if(fCSA14 && MuIso03SumPt->at(0)/MuPt->at(0) > 0.4)      return false;
	
	return true;
}


//____________________________________________________________________________
bool Fakerates::isLooseElectron(int index){
	/* 
	checks, if the electron is loose
	parameters: index (index of the particle)
	return: true (if electron is loose), false (else)
	*/

	if(ElPt->at(index) < 10.) return false;
	if(!ElIsLoose->at(index)) return false;
	if(ElPFIso->at(index) > 0.6) return false;

	return true;
}


//____________________________________________________________________________
bool Fakerates::isLooseLepton(int index){
	/* 
	checks, if the lepton is loose
	parameters: index (index of the particle)
	return: true (if lepton is loose), false (else)
	*/

	if(fDataType == 2) return isLooseElectron(index);
	else               return isLooseMuon(index);

}


//____________________________________________________________________________
bool Fakerates::isLooseOpLepton(int index){
	/* 
	checks, if the lepton of opposite flavor is loose
	parameters: index (index of the particle)
	return: true (if lepton is loose), false (else)
	*/

	if(fDataType == 2) return isLooseMuon(index);
	else               return isLooseElectron(index);

}


//____________________________________________________________________________
bool Fakerates::isLooseMuonTTBar(int index){
	/* 
	checks, if the muon in the ttbar sample is loose
	parameters: index (index of the particle)
	return: true (if muon is loose), false (else)
	*/

	if(!isLooseMuon(index)) return false;

	return true;
}


//____________________________________________________________________________
bool Fakerates::isLooseElectronTTBar(int index){
	/* 
	checks, if the electron in the ttbar sample is loose
	parameters: index (index of the particle)
	return: true (if electron is loose), false (else)
	*/

	if(!isLooseElectron(index)) return false;

	return true;
}

//____________________________________________________________________________
bool Fakerates::isLooseLeptonTTBar(int index){
	/* 
	checks, if the lepton in the ttbar sample is loose
	parameters: index (index of the particle)
	return: true (if lepton is loose), false (else)
	*/

	if(fDataType == 2) return isLooseElectronTTBar(index);
	else               return isLooseMuonTTBar(index);
}


//____________________________________________________________________________
bool Fakerates::isTightMuon(int index){
	/* 
	checks, if the muon is tight
	parameters: index (index of the particle)
	return: true (if muon is tight), false (else)
	*/

	if(!isLooseMuon(index)) return false;
	if(!MuIsTight->at(index)) return false;
	if(fLepIsoCut > 0.0 && fabs(MuPFIso->at(index)) > fLepIsoCut) return false; // leave this commented for synching!!

	return true;
}


//____________________________________________________________________________
bool Fakerates::isTightElectron(int index){
	/* 
	checks, if the electron is tight
	parameters: index (index of the particle)
	return: true (if electron is tight), false (else)
	*/

	if(!isLooseElectron(index)) return false;
	if(!ElIsTight->at(index)) return false;
	if(ElPFIso->at(index) > 0.15) return false;
	if(fLepIsoCut > 0.0 && fabs(ElPFIso->at(index)) > fLepIsoCut) return false; // leave this commented for synching!!

	return true;
}


//____________________________________________________________________________
bool Fakerates::isTightLepton(int index){
	/* 
	checks, if the lepton is tight
	parameters: index (index of the particle)
	return: true (if lepton is tight), false (else)
	*/

	if(fDataType == 2) return isTightElectron(index);
	else               return isTightMuon(index);
}


//____________________________________________________________________________
bool Fakerates::isTightMuonTTBar(int index){
	/* 
	checks, if the muon in the ttbar sample is tight
	parameters: index (index of the particle)
	return: true (if muon is tight), false (else)
	*/

	if(!isTightMuon(index)) return false;

	return true;
}


//____________________________________________________________________________
bool Fakerates::isTightElectronTTBar(int index){
	/* 
	checks, if the electron in the ttbar sample is tight
	parameters: index (index of the particle)
	return: true (if electron is tight), false (else)
	*/

	if(!isTightElectron(index)) return false;

	return true;
}


//____________________________________________________________________________
bool Fakerates::isTightLeptonTTBar(int index){
	/* 
	checks, if the lepton in the ttbar sample is tight
	parameters: index (index of the particle)
	return: true (if lepton is tight), false (else)
	*/

	if(fDataType == 2) return isTightElectronTTBar(index);
	else               return isTightMuonTTBar(index);

}


//____________________________________________________________________________
float Fakerates::getJetPt(int index) {
	/* 
	select the right JetPt according to the level of correction
	parameters: index (index of the jet)
	return: JetPt or JetRawPt of the jet
	*/

	if(fJetCorrection) return JetPt->at(index);
	else               return JetRawPt->at(index);
}


//____________________________________________________________________________
void Fakerates::setMET(float newvalue){
	/* 
	set the right MET according to the level of correction
	parameters: newvalue (value to be set)
	return: MET or MET1
	*/

	if(fJetCorrection) pfMET1 = newvalue;
	else               pfMET  = newvalue;
}


//____________________________________________________________________________
void Fakerates::setMETPhi(float newvalue){
	/* 
	set the right METPhi according to the level of correction
	parameters: newvalue (value to be set)
	return: none
	*/

	if(fJetCorrection) pfMET1Phi = newvalue;
	else               pfMETPhi  = newvalue;
}


//____________________________________________________________________________
float Fakerates::getMET(){
	/* 
	select the right MET according to the level of correction
	parameters: none
	return: MET or MET1
	*/

	if(fJetCorrection) return pfMET1;
	else               return pfMET;
}


//____________________________________________________________________________
float Fakerates::getMETPhi(){
	/* 
	select the right METPhi according to the level of correction
	parameters: none
	return: METPhi or MET1Phi
	*/

	if(fJetCorrection) return pfMET1Phi;
	else               return pfMETPhi;
}


//____________________________________________________________________________
float Fakerates::getMT(int index) {
	/*
	computes MT of the event
	parameters: index (index of the lepton)
	return: MT
	*/

	float pt   = -1;
	float dphi = -1.;
	std::vector<float, std::allocator<float> >* LepPt  = getLepPt();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();

	dphi = Util::DeltaPhi(getMETPhi(), LepPhi->at(index));
	pt   = LepPt->at(index);

	return TMath::Sqrt( 2 * getMET() * pt * (1. - TMath::Cos(dphi)) );
}


//____________________________________________________________________________
bool Fakerates::passesMETCut(float value_met = 20., int sign = 0){
	/* 
	checks, if the event passes the MET cut
	parameters: value_met (cut value), sign (0 cut above, 1 cut below)
	return: true (if event passes the cuts), false (else)
	*/

	if(sign == 1 && getMET() < value_met) return false;
	if(sign == 0 && getMET() > value_met) return false;
	return true;
}


//____________________________________________________________________________
bool Fakerates::passesMTCut(int index){
	/* 
	checks, if the event passes the 20GeV MT cut
	parameters: index (index of the lepton)
	return: true (if event passes the cuts), false (else)
	*/

	float value_mt  = 20.;

	if(getMT(index) > value_mt) return false;

	return true;
}


//____________________________________________________________________________
bool Fakerates::passesUpperMETMT(int index, bool count = false){
	/* 
	checks, if the event passes upper MET and MT cuts
	parameters: index (index of the particle)
	return: true (if event passes the cuts), false (else)
	*/

	//cout << "start passesUpperMETMT" << endl;
	//cout << "check 9" << endl;
    if(!passesMETCut()) return false;
    fCutflow_afterMETCut++;	

	if(count) ++fCounter_met;

	//cout << "check 10" << endl;
    if(!passesMTCut(index)) return false;
    fCutflow_afterMTCut++;
	
	if(count) ++fCounter_mt;

	//cout << "check 11" << endl;
	
	return true;
}


//____________________________________________________________________________
bool Fakerates::isGoodJet(int j, float pt = 0., float btag = 0.){
	/*
	checks, if the given jet passes certain cuts defining it as a "good" jet
	parameters: j (jet index), pt (cut on pt), btag (btag cut)
	return: true (if jet is good), false (else)
	*/     

	float minDR = 0.4;
	std::vector<float, std::allocator<float> >* LepEta = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();

	// if pt too low, eta too large, jet beta star too large then return false
	if(pt  >0. && getJetPt(j)       < pt  ) return false;
	if(btag>0. && JetCSVBTag->at(j) < btag) return false;
	if(fabs(JetEta->at(j)) > 2.5          ) return false;

	// if(JetBetaStar->at(j) > 0.2*TMath::Log(NVrtx-0.67)) return false; // value for jets with eta < 2.5

	// jet-lepton cleaning: if a loose lepton with dR too small found then return false

	bool isClosest = false;


	// clean w/r/t loose electrons
	for(int el = 0; el < ElPt->size(); ++el){
		if(!isLooseElectron(el) || ElPt->at(el) < 10.) continue;

		float closestDR  = 99.;
		int   closestInd =  -1;

		for(int thisjet = 0; thisjet < JetPt->size(); ++thisjet){
			float dr = Util::GetDeltaR(ElEta->at(el), JetEta->at(thisjet), ElPhi->at(el), JetPhi->at(thisjet));
			if(dr < closestDR) {
				closestDR  = dr;
				closestInd = thisjet;
			}
		}

		if(closestInd == j && closestDR < minDR) isClosest = true;

	}

	if(isClosest) return false; // don't run on muons if already closest to a loose electron

	// clean w/r/t loose muons
	for(int mu = 0; mu < MuPt->size(); ++mu){
		if(!isLooseMuon(mu) || MuPt->at(mu) < 10.) continue;

		float closestDR  = 99.;
		int   closestInd =  -1;

		for(int thisjet = 0; thisjet < JetPt->size(); ++thisjet){
			float dr = Util::GetDeltaR(MuEta->at(mu), JetEta->at(thisjet), MuPhi->at(mu), JetPhi->at(thisjet));
			if(dr < closestDR) {
				closestDR  = dr;
				closestInd = thisjet;
			}
		}

		if(closestInd == j && closestDR < minDR) isClosest = true;

	}

	if(isClosest) return false; //no good jet if closest to a loose lepton
	return true;
}


//____________________________________________________________________________
float Fakerates::getLargestCSV(){
	/* 
	get largest CSV B-Tag in the event
	parameters: none
	return: csv
	*/

	float maxcsv = 0.;
 
	for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet)
		if(JetCSVBTag->at(thisjet) > maxcsv) maxcsv = JetCSVBTag->at(thisjet);

	return maxcsv;
}


//____________________________________________________________________________
int Fakerates::getAwayJet(int lep = 0){
	/*
	get information about the away jet with largest Pt
	parameters: info (0 = jetind, 1 = dR, 2 = Pt), lep (lepton index)
	return: info
	*/

	int nawayjets(0), jetind(0);
	std::vector<int> awayjet_inds;
	std::vector<float, std::allocator<float> >* LepEta = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();
	
	for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){
		if(!isGoodJet(thisjet, fJetPtCut)) continue;
		if(Util::GetDeltaR(JetEta->at(thisjet), LepEta->at(lep), JetPhi->at(thisjet), LepPhi->at(lep)) < 1.0 ) continue;
		nawayjets++;
		awayjet_inds.push_back(thisjet);
    }

	if(awayjet_inds.size() == 0) return 0;

	jetind = awayjet_inds[0];
	if(awayjet_inds.size() > 1)
		for(int thisjet=0; thisjet < nawayjets; ++thisjet)
			if(getJetPt(awayjet_inds[thisjet]) > getJetPt(jetind) ) jetind = awayjet_inds[thisjet];

	return jetind;
}


//____________________________________________________________________________
float Fakerates::getAwayJetDR(int lep = 0){
	/*
	get dR of away jet to given lepton
	parameters: lep (lepton index)
	return: dR
	*/

	std::vector<float, std::allocator<float> >* LepEta = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();

	int jetind = getAwayJet(lep);
	return Util::GetDeltaR(JetEta->at(jetind), LepEta->at(lep), JetPhi->at(jetind), LepPhi->at(lep));

}


//____________________________________________________________________________
int Fakerates::getClosestJet(int lep = 0){
	/*
	get index of the closest jet to given lepton
	parameters: lep (lepton index)
	return: jetind (closest jet index)
	*/

	int jetind(0);
	std::vector<float, std::allocator<float> >* LepEta = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();
	
	for(int thisjet=0; thisjet < JetPt->size(); ++thisjet)
		if(Util::GetDeltaR(JetEta->at(thisjet), LepEta->at(lep), JetPhi->at(thisjet), LepPhi->at(lep)) < Util::GetDeltaR(JetEta->at(jetind), LepEta->at(lep), JetPhi->at(jetind), LepPhi->at(lep)) ) jetind = thisjet;

	return jetind;

}


//____________________________________________________________________________
float Fakerates::getClosestJetDR(int lep = 0){
	/*
	return the dR of the closest jet to the given lepton
	parameter: lep (lepton index)
	return: dR
	*/

	std::vector<float, std::allocator<float> >* LepEta = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi = getLepPhi();

	int jetind = getClosestJet(lep);	
	return Util::GetDeltaR(JetEta->at(jetind), LepEta->at(lep), JetPhi->at(jetind), LepPhi->at(lep));

}


//____________________________________________________________________________
float Fakerates::getHT(){
	/*
	compute the scalar sum HT of Pt of good jets and return it
	parameters: none
	return: HT
	*/
	
	float HT(0.);
	
	for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){
		if(!isGoodJet(thisjet, fJetPtCut)) continue;
		HT += getJetPt(thisjet);
	}

	return HT;
}



//____________________________________________________________________________
int Fakerates::getNJets(int btag = 0){
	/*
	counts the number of jets and b-tagged jets
	parameters: btag (0 = any jet, 1 = b tagged jet)
	return: number of jets
	*/

	int njets(0), nbjets(0);
	
	for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){
		if(!isGoodJet(thisjet, fJetPtCut)) continue;
		njets++;
		if(JetCSVBTag->at(thisjet)<0.679) continue;
		nbjets++;
	}

	if(btag==1) return nbjets;
	return njets;
}


//____________________________________________________________________________
bool Fakerates::fillFHist(float LepPt){
	/*
	checks, if the bins below 40GeV of h_FLoose and h_FTight shall be filled or 
	not, depending on the choice of trigger used
	parameters: LepPt (pt of the lepton)
	return: true (if entry to be filled), false (else)
	*/

	if(fLepTrigger != "none" && LepPt <= fPlotThreshold) return false;

	return true;

}


//____________________________________________________________________________
void Fakerates::fillFHistTTBar(TH2F *&Hist, float LepPt, float LepEta, float eventweight){
	/*
	checks, if the bins below 40GeV of h_FLoose and h_FTight shall be filled or 
	not, depending on the choice of trigger used, and then fills the bins of the histogram
	parameters: Hist (TH2 to be filled), LepPt (pt of the lepton), LepEta (eta of the lepton), eventweight (eventweight)
	return: true (if entry to be filled), false (else)
	*/


	if( LepPt > fFRbinspt.back() ){
		int fillbin = Hist ->FindBin(fFRbinspt.back() - 0.5, fabs(LepEta));
		Hist ->AddBinContent(fillbin, eventweight);
	}
	else{
		//if(fillFHist(LepPt))
			Hist ->Fill(LepPt, fabs(LepEta), eventweight);
	}

}


//____________________________________________________________________________
void Fakerates::fillHLTPlots(float fEventweight = 1.0){
	/* 
	   Let's use this function to measure purities for the different triggers that 
	   we use and also to measure the FR measured with every-single trigger. 
	   parameters: none
	   return:
	*/ 
	
	int lep(-1), jet(-1);
	std::vector<int> looselep_inds;
	std::vector<int> awayjet_inds;
	std::vector<float, std::allocator<float> >* LepPt    = getLepPt();
	std::vector<float, std::allocator<float> >* LepEta   = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi   = getLepPhi();
	std::vector<float, std::allocator<float> >* LepPFIso = getLepPFIso();
	std::vector<float, std::allocator<float> >* LepD0    = getLepD0();
	int nloose(0), nveto_add(0);
	int ngoodjets20(0), nawayjets20(0),ngoodjets30(0), nawayjets30(0),ngoodjets40(0), nawayjets40(0);
	int jetind(-1);
	
	
	/// FOR MUONS FOR THE MOMENT
	for(int tr=0; tr<iNTRIGS; tr++) {

		if(PassesHLT(tr)) { 
	
			fillPurities(tr,0., fEventweight);  
	      
			// muon Pt is not reasonable then return false
			if(MuPt->size() > 0)  {
		
				if(!fCSA14 || MuIso03SumPt->at(0)/MuPt->at(0) < 0.4) { // FOR 2015 SCENARIO
						
					fillPurities(tr,1., fEventweight);
					h_Purity_LepPt[tr] -> Fill(MuPt->at(0), fEventweight); 
					
					// count numbers of loose and veto muons in the event 
					float ptcut = -1;
					if (tr == iHLTMU5 ) ptcut =  5.;
					if (tr == iHLTMU8 ) ptcut =  8.;
					if (tr == iHLTMU12) ptcut = 12.;
					if (tr == iHLTMU17) ptcut = 17.;
					if (tr == iHLTMU24) ptcut = 24.;
					if (tr == iHLTMU40) ptcut = 40.;
					
					for(int j=0; j < MuPt->size(); ++j){
						if(nloose==0){
							//if(MuPt              ->at(j) < ptcut) continue; fillPurities(tr, 2. , fEventweight);
							//if(fabs(MuEta->at(j))        > 2.4  ) continue; 
							//if(MuIsGlobalMuon    ->at(j) == 0   ) continue; fillPurities(tr, 3. , fEventweight);
							//if(MuIsPFMuon        ->at(j) == 0   ) continue; fillPurities(tr, 4. , fEventweight);
							//if(MuNChi2           ->at(j) > 10   ) continue; fillPurities(tr, 5. , fEventweight);
							//if(MuNGlMuHits       ->at(j) < 1    ) continue; fillPurities(tr, 6. , fEventweight);
							//if(MuNMatchedStations->at(j) < 2    ) continue; fillPurities(tr, 7. , fEventweight); 
							//if(MuDz              ->at(j) > 0.2  ) continue; fillPurities(tr, 8. , fEventweight);
							//if(MuD0              ->at(j) > 0.2  ) continue; fillPurities(tr, 9. , fEventweight);
							//if(MuNPxHits         ->at(j) < 1    ) continue; fillPurities(tr, 10., fEventweight);
							//if(MuNSiLayers       ->at(j) < 6    ) continue; fillPurities(tr, 11., fEventweight);
							//if(MuPFIso           ->at(j) > 1.0  ) continue; fillPurities(tr, 12., fEventweight);
						}
						lep = j;
						nloose++;
						looselep_inds.push_back(j);		 
			
						//   if(!isLooseLepton(j)) continue;
						if(isLooseLepton(j) && MuPt->at(j) < fLepPtCut) nveto_add++;
						
					}
				  
			
					// require exactly one loose muon and no additional veto muons
					if(nloose == 1 && nveto_add == 0) {
			
						fillPurities(tr,13., fEventweight);
				    
						// Jet Pt is not reasonable then return false
						if(JetRawPt->size() > 0) {
			
							fillPurities(tr,14., fEventweight);
							h_Purity_JetRawPt[tr] -> Fill(JetRawPt->at(0), fEventweight);
		      
							// count the number of away jets
							for(int thisjet=0; thisjet < JetRawPt->size(); ++thisjet){
								if(!isGoodJet(thisjet, 20., fAwayJetBTagCut)) continue;
								ngoodjets20++;
								if(Util::GetDeltaR(JetEta->at(thisjet), MuEta->at(lep), JetPhi->at(thisjet), MuPhi->at(lep)) > 1.0 ) nawayjets20++;
								
								if(!isGoodJet(thisjet, 30., fAwayJetBTagCut)) continue;
								ngoodjets30++;
								if(Util::GetDeltaR(JetEta->at(thisjet), MuEta->at(lep), JetPhi->at(thisjet), MuPhi->at(lep)) > 1.0 ) nawayjets30++;
								
								if(!isGoodJet(thisjet, fJetPtCut, fAwayJetBTagCut)) continue;
								ngoodjets40++;
								if(Util::GetDeltaR(JetEta->at(thisjet), MuEta->at(lep), JetPhi->at(thisjet), MuPhi->at(lep)) > 1.0 ) nawayjets40++;
							}
		      
							if(ngoodjets20 > 0) {
	
								fillPurities(tr,15., fEventweight);
								h_Purity_JetPt   [tr] -> Fill(JetPt->at(0), fEventweight);
								h_Purity_DRLepJet[tr] -> Fill(Util::GetDeltaR(JetEta->at(0), MuEta->at(lep), JetPhi->at(0), MuPhi->at(lep)), fEventweight);
	
								if(nawayjets20 > 0) {

									fillPurities(tr,16., fEventweight);

		  							h_Purity_MET     [tr] -> Fill(getMET(),   fEventweight);
		  							h_Purity_MT      [tr] -> Fill(getMT(lep), fEventweight);
		  
									if(passesMETCut()){

										fillPurities(tr,17., fEventweight);
		    							if(passesMTCut(lep)) fillPurities(tr, 18., fEventweight);
										
									}
								}
							}

							if(ngoodjets30 > 0) {

								fillPurities(tr,19., fEventweight);
								if(nawayjets30 > 0) {

									fillPurities(tr,20., fEventweight); 
									if(passesMETCut()){

										fillPurities(tr,21., fEventweight);
										if(passesMTCut(lep)) fillPurities(tr,22., fEventweight);
		    
									}
								}
							}

							if(ngoodjets40 > 0) {

								fillPurities(tr,23., fEventweight);
								if(nawayjets40 > 0) {

									fillPurities(tr,24., fEventweight);
									if(passesMETCut()){

										fillPurities(tr,25., fEventweight);
										if(passesMTCut(lep)) fillPurities(tr,26., fEventweight);
										
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	
	////////////////////////////////////////////////// 
	///// CALCULATE FR...
	////////////////////////////////////////////////
	//++ get number of fakeables per trigger
	TString LepTrigger_tmp = fLepTrigger;
	fLepTrigger = "";  // deactivate trigger requirement in isFRRegionLepEvent
	
	if (isFRRegionLepEvent(lep, jet, fJetPtCut)){

		// loose leptons
		if(passesUpperMETMT(lep)) {
			if (HLT_MU5) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU5 ], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU5]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU5]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
			if (HLT_MU8) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU8 ], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU8]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU8]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
			if (HLT_MU12) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU12], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU12]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU12]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
			if (HLT_MU17) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU17], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU17]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU17]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
			if (HLT_MU24) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU24], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU24]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU24]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
			if (HLT_MU40) {
				fill2DWithoutOF(h_FLoose_trig[iHLTMU40], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
				h_Loose_LepPt_trig [iHLTMU40]->Fill(LepPt->at(lep), fEventweight);
				h_Loose_LepEta_trig[iHLTMU40]->Fill(fabs(LepEta->at(lep)), fEventweight);
			}
		}
		
		// Tight leptons
		if(isTightLepton(lep)) {

			if(passesUpperMETMT(lep)) {

				if (HLT_MU5) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU5 ], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU5]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU5]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}
				if (HLT_MU8) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU8 ], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU8]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU8]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}
				if (HLT_MU12) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU12], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU12]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU12]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}
				if (HLT_MU17) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU17], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU17]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU17]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}	
				if (HLT_MU24) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU24], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU24]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU24]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}
				if (HLT_MU40) {
					fill2DWithoutOF(h_FTight_trig[iHLTMU40], LepPt->at(lep), fabs(LepEta->at(lep)), fEventweight);
					h_Tight_LepPt_trig [iHLTMU40]->Fill(LepPt->at(lep), fEventweight);
					h_Tight_LepEta_trig[iHLTMU40]->Fill(fabs(LepEta->at(lep)), fEventweight);
				}
			}
		}
	}
	fLepTrigger = LepTrigger_tmp;  // reactivate trigger requirement in isFRRegionLepEvent

}


//____________________________________________________________________________
void Fakerates::fillFRPlots(float eventweight = 1.0){
	/* 
	create plos for muons and electrons
	parameters: none
	return: none
	*/


	int lep(-1), jet(-1);
	std::vector<float, std::allocator<float> >* LepPt    = getLepPt();
	std::vector<float, std::allocator<float> >* LepEta   = getLepEta();
	std::vector<float, std::allocator<float> >* LepPhi   = getLepPhi();
	std::vector<float, std::allocator<float> >* LepPFIso = getLepPFIso();
	std::vector<float, std::allocator<float> >* LepD0    = getLepD0();


	if(isFRRegionLepEvent(lep, jet, 30.)) {
		if(passesUpperMETMT(lep)) {
			h_Loose_LepEta_30 ->Fill(fabs(LepEta->at(lep)), eventweight);
			h_Loose_LepPt_30  ->Fill(LepPt->at(lep)       , eventweight);
			if(isTightLepton(lep)){
				h_Tight_LepEta_30 ->Fill(fabs(LepEta->at(lep)), eventweight);
				h_Tight_LepEta_30 ->Fill(LepPt->at(lep)       , eventweight);
			}
		}
	}

	if(isFRRegionLepEvent(lep, jet, 40.)) {
		if(passesUpperMETMT(lep)) {
			h_Loose_LepEta_40 ->Fill(fabs(LepEta->at(lep)), eventweight);
			h_Loose_LepPt_40  ->Fill(LepPt->at(lep)       , eventweight);
			if(isTightLepton(lep)) {
				h_Tight_LepEta_40 ->Fill(fabs(LepEta->at(lep)), eventweight);
				h_Tight_LepPt_40  ->Fill(LepPt->at(lep)       , eventweight);
			}
		}
	}

	if(isFRRegionLepEvent(lep, jet, 50.)) {
		if(passesUpperMETMT(lep)) {
			h_Loose_LepEta_50 ->Fill(fabs(LepEta->at(lep)), eventweight);
			h_Loose_LepPt_50  ->Fill(LepPt->at(lep)       , eventweight);
			if(isTightLepton(lep)) {
				h_Tight_LepEta_50 ->Fill(fabs(LepEta->at(lep)), eventweight);
				h_Tight_LepPt_50  ->Fill(LepPt->at(lep)       , eventweight);
			}
		}
	}

	if(isFRRegionLepEvent(lep, jet, 60.)) {
		if(passesUpperMETMT(lep)) {
			h_Loose_LepEta_60 ->Fill(fabs(LepEta->at(lep)), eventweight);
			h_Loose_LepPt_60  ->Fill(LepPt->at(lep)       , eventweight);
			if(isTightLepton(lep)){
				h_Tight_LepEta_60 ->Fill(fabs(LepEta->at(lep)), eventweight);
				h_Tight_LepPt_60  ->Fill(LepPt->at(lep)       , eventweight);
			}
		}
	}


	// leptons, first loose, then tight
	if(isFRRegionLepEvent(lep, jet, fJetPtCut, true)){

		if(passesUpperMETMT(lep, true)) {
 
			h_Loose_AwayJetDR ->Fill(getAwayJetDR(lep)    , eventweight);
			h_Loose_AwayJetPt ->Fill(getJetPt(getAwayJet(lep))   , eventweight);
			h_Loose_ClosJetDR ->Fill(getClosestJetDR(lep) , eventweight);
			h_Loose_ClosJetPt ->Fill(getJetPt(getClosestJet(lep)), eventweight);

			h_Loose_HT        ->Fill(getHT()              , eventweight);
			h_Loose_LepEta    ->Fill(fabs(LepEta->at(lep)), eventweight);
			h_Loose_LepIso    ->Fill(LepPFIso->at(lep)    , eventweight);
			h_Loose_LepPt     ->Fill(LepPt->at(lep)       , eventweight);

			h_Loose_MaxJPt    ->Fill(getJetPt(jet)        , eventweight);
			h_Loose_NBJets    ->Fill(getNJets(1)          , eventweight);
			h_Loose_NJets     ->Fill(getNJets()           , eventweight);
			
			h_Loose_NVertices ->Fill((NVrtx>40)?40:NVrtx  , eventweight);
			h_Loose_NVertices1->Fill((NVrtx>30)?30:NVrtx  , eventweight);

			h_Loose_D0        ->Fill(LepD0->at(lep)       , eventweight);
			h_Loose_MaxJCPt   ->Fill(JetPt->at(jet)       , eventweight); // always corrected Jet Pt!
			h_Loose_MaxJRPt   ->Fill(JetRawPt->at(jet)    , eventweight); // always raw Jet Pt!
			h_Loose_MaxJCSV   ->Fill(getLargestCSV()      , eventweight); 

			h_Loose_JCPtJEta  ->Fill(fabs(JetEta->at(jet)), JetPt->at(jet), eventweight);
			h_Loose_JRPtJEta  ->Fill(fabs(JetEta->at(jet)), JetRawPt->at(jet), eventweight);
			h_Loose_JCPtJPt   ->Fill(JetPt->at(jet), JetPt->at(jet), eventweight);
			h_Loose_JRPtJPt   ->Fill(JetPt->at(jet), JetRawPt->at(jet), eventweight);


			for(int thisjet = 0; thisjet < JetRawPt->size(); ++thisjet) {

				h_Loose_AllJCPt   ->Fill(JetPt->at(thisjet)       , eventweight);
				h_Loose_AllJRPt   ->Fill(JetRawPt->at(thisjet)    , eventweight);
				h_Loose_AllJEta   ->Fill(fabs(JetEta->at(thisjet)), eventweight);
				h_Loose_AllJCSV   ->Fill(JetCSVBTag->at(thisjet)  , eventweight);

				h_Loose_DJPtJEta  ->Fill(fabs(JetEta->at(thisjet)), (JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
				h_Loose_FJPtJEta  ->Fill(fabs(JetEta->at(thisjet)), (JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
				h_Loose_DJPtJPt   ->Fill(JetPt->at(thisjet),        (JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
				h_Loose_FJPtJPt   ->Fill(JetPt->at(thisjet),        (JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);

				int i = h_Loose_DFZoomEta ->FindBin(fabs(JetEta->at(thisjet)));
				if(fDFbinseta[0]<=fabs(JetEta->at(thisjet)) && fabs(JetEta->at(thisjet))<fDFbinseta[fDFn_binseta-1]){
				
					if(fDFbinspt[0]<=JetPt->at(thisjet) && JetPt->at(thisjet)<fDFbinspt[fDFn_binspt-1]){
						int j = h_Loose_DFZoomPt  ->FindBin(JetPt->at(thisjet));
						h_Loose_DJPtZoomC[(i-1)*(fDFn_binspt-1) + j - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
						h_Loose_FJPtZoomC[(i-1)*(fDFn_binspt-1) + j - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
					}

					if(fDFbinspt[0]<=JetRawPt->at(thisjet) && JetRawPt->at(thisjet)<fDFbinspt[fDFn_binspt-1]){
						int k = h_Loose_DFZoomPt  ->FindBin(JetRawPt->at(thisjet));
						h_Loose_DJPtZoomR[(i-1)*(fDFn_binspt-1) + k - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
						h_Loose_FJPtZoomR[(i-1)*(fDFn_binspt-1) + k - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
					}
				}
			}

			if( LepPt->at(lep) >  fFRbinspt.back() ){
				int fillbin = h_FLoose->FindBin(fFRbinspt.back()-0.5, fabs(LepEta->at(lep)));
				h_FLoose->AddBinContent(fillbin, eventweight);
			}
			else{
				if(fillFHist(LepPt->at(lep)))
					h_FLoose->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);
			}

// cout << Form("%d\t%d\t%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\t%.2f", Run, Lumi, Event, LepPt->at(mu), getJetPt(getAwayJet(mu)), isTightMuon(mu), getAwayJetDR(mu), getMET(), getMT(0, mu)) << endl;
//	if(LepPt->at(lep)>=35. && LepPt->at(lep)<45. && fabs(LepEta->at(lep))>=2. && fabs(LepEta->at(lep))<2.5)
//	cout << Form("%d\t%d\t%d\t%.2f\t%d\t%.2f\t%.2f", Run, Lumi, Event, LepPt->at(lep), isTightLepton(lep), getMET(), getMT(lep)) << endl;

 		}

		if(passesMTCut(lep))    h_Loose_MET            ->Fill(getMET()            , eventweight);
		                        h_Loose_METnoMTCut     ->Fill(getMET()            , eventweight);
		if(passesMETCut())      h_Loose_MT             ->Fill(getMT(lep)          , eventweight);
		if(passesMETCut(20,1))  h_Loose_MTMET20        ->Fill(getMT(lep)          , eventweight);
		if(passesMETCut(30,1))  h_Loose_MTMET30        ->Fill(getMT(lep)          , eventweight);
		if(passesMETCut(20,1))  h_Loose_NVerticesMET20 ->Fill((NVrtx>40)?40:NVrtx , eventweight);
		
		if(passesMETCut(20)){
			h_FLoose_CERN_small ->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);
			++fCounter_CERN_small;
		}
		if(passesMETCut(45,1) && passesMETCut(80)){
			h_FLoose_CERN_large ->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);
			++fCounter_CERN_large;
		}

		if(passesMTCut(lep) && fFRMETbinseta[0]<=fabs(LepEta->at(lep)) && fabs(LepEta->at(lep))<fFRMETbinseta[fFRMETn_binseta-1]){
			if(fFRMETbinspt[0]<=LepPt->at(lep) && LepPt->at(lep)<fFRMETbinspt[fFRMETn_binspt-1]){
				int i = h_Loose_FRMETZoomEta ->FindBin(fabs(LepEta->at(lep)));
				int j = h_Loose_FRMETZoomPt  ->FindBin(LepPt->at(lep));
				h_Loose_METZoom[(i-1)*(fFRMETn_binspt-1) + j - 1] ->Fill((getMET()), eventweight);
			}
		}


		// tight leptons
		if(isTightLepton(lep)) {

			if(passesUpperMETMT(lep)) {
  
				h_Tight_AwayJetDR ->Fill(getAwayJetDR(lep)     , eventweight);
				h_Tight_AwayJetPt ->Fill(getJetPt(getAwayJet(lep))    , eventweight);
				h_Tight_ClosJetDR ->Fill(getClosestJetDR(lep)  , eventweight);
				h_Tight_ClosJetPt ->Fill(getJetPt(getClosestJet(lep)) , eventweight);

				h_Tight_HT        ->Fill(getHT()               , eventweight);
				h_Tight_LepEta    ->Fill(fabs(LepEta->at(lep)) , eventweight);
				h_Tight_LepIso    ->Fill(LepPFIso->at(lep)     , eventweight);
				h_Tight_LepPt     ->Fill(LepPt->at(lep)        , eventweight);

				h_Tight_MaxJPt    ->Fill(getJetPt(jet)         , eventweight);
				h_Tight_NBJets    ->Fill(getNJets(1)           , eventweight);
				h_Tight_NJets     ->Fill(getNJets()            , eventweight);
				h_Tight_NVertices ->Fill((NVrtx>40)?40:NVrtx   , eventweight);
				h_Tight_NVertices1->Fill((NVrtx>30)?30:NVrtx   , eventweight);

				h_Tight_D0        ->Fill(LepD0->at(lep)        , eventweight);
				h_Tight_MaxJCPt   ->Fill(JetPt->at(jet)        , eventweight); // always corrected Jet Pt!
				h_Tight_MaxJRPt   ->Fill(JetRawPt->at(jet)     , eventweight); // always raw Jet Pt!
				h_Tight_MaxJCSV   ->Fill(getLargestCSV()       , eventweight); 

				h_Tight_JCPtJEta  ->Fill(fabs(JetEta->at(jet)) , JetPt->at(jet)    , eventweight);
				h_Tight_JRPtJEta  ->Fill(fabs(JetEta->at(jet)) , JetRawPt->at(jet) , eventweight);
				h_Tight_JCPtJPt   ->Fill(JetPt->at(jet)        , JetPt->at(jet)    , eventweight);
				h_Tight_JRPtJPt   ->Fill(JetPt->at(jet)        , JetRawPt->at(jet) , eventweight);

				for(int thisjet = 0; thisjet < JetRawPt->size(); ++thisjet) {
					h_Tight_AllJCPt   ->Fill(JetPt->at(thisjet)       , eventweight);
					h_Tight_AllJRPt   ->Fill(JetRawPt->at(thisjet)    , eventweight);
					h_Tight_AllJEta   ->Fill(fabs(JetEta->at(thisjet)), eventweight);
					h_Tight_AllJCSV   ->Fill(JetCSVBTag->at(thisjet)  , eventweight);

					h_Tight_DJPtJEta ->Fill(fabs(JetEta->at(thisjet)), (JetPt->at(thisjet)-JetRawPt->at(thisjet))                      , eventweight);
					h_Tight_FJPtJEta ->Fill(fabs(JetEta->at(thisjet)), (JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
					h_Tight_DJPtJPt  ->Fill(JetPt->at(thisjet)       , (JetPt->at(thisjet)-JetRawPt->at(thisjet))                      , eventweight);
					h_Tight_FJPtJPt  ->Fill(JetPt->at(thisjet)       , (JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
				
					int i = h_Tight_DFZoomEta ->FindBin(fabs(JetEta->at(thisjet)));
					if(fDFbinseta[0]<=fabs(JetEta->at(thisjet)) && fabs(JetEta->at(thisjet))<fDFbinseta[fDFn_binseta-1]){
				
						if(fDFbinspt[0]<=JetPt->at(thisjet) && JetPt->at(thisjet)<fDFbinspt[fDFn_binspt-1]){
							int j = h_Tight_DFZoomPt  ->FindBin(JetPt->at(thisjet));
							h_Tight_DJPtZoomC[(i-1)*(fDFn_binspt-1) + j - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
							h_Tight_FJPtZoomC[(i-1)*(fDFn_binspt-1) + j - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
						}

						if(fDFbinspt[0]<=JetRawPt->at(thisjet) && JetRawPt->at(thisjet)<fDFbinspt[fDFn_binspt-1]){
							int k = h_Tight_DFZoomPt  ->FindBin(JetRawPt->at(thisjet));
							h_Tight_DJPtZoomR[(i-1)*(fDFn_binspt-1) + k - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet)),                       eventweight);
							h_Tight_FJPtZoomR[(i-1)*(fDFn_binspt-1) + k - 1] ->Fill((JetPt->at(thisjet)-JetRawPt->at(thisjet))/JetRawPt->at(thisjet), eventweight);
						}
					}
				}

				if( LepPt->at(lep) >  fFRbinspt.back()){
					int fillbin = h_FTight->FindBin(fFRbinspt.back()-0.5, fabs(LepEta->at(lep)));
					h_FTight->AddBinContent(fillbin, eventweight);
				}
				else{
					if(fillFHist(LepPt->at(lep)))
						h_FTight->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);
				}

//	if(L//epPt->at(lep)>=35. && LepPt->at(lep)<45. && fabs(LepEta->at(lep))>=2. && fabs(LepEta->at(lep))<2.5)
//	cout// << Form("%d\t%d\t%d\t%.2f\t%d\t%.2f\t%.2f", Run, Lumi, Event, LepPt->at(lep), isTightLepton(lep), getMET(), getMT(lep)) << endl;

			}

			if(passesMTCut(lep))    h_Tight_MET        -> Fill(getMET()               , eventweight);
			                        h_Tight_METnoMTCut -> Fill(getMET()               , eventweight);
			if(passesMETCut())      h_Tight_MT         -> Fill(getMT(lep)             , eventweight);
			if(passesMETCut(20,1))  h_Tight_MTMET20    -> Fill(getMT(lep)             , eventweight);
			if(passesMETCut(30,1))  h_Tight_MTMET30    -> Fill(getMT(lep)             , eventweight);
			if(passesMETCut(20,1))  h_Tight_NVerticesMET20 ->Fill((NVrtx>40)?40:NVrtx , eventweight);

			if(passesMETCut(20))
				h_FTight_CERN_small ->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);
		
			if(passesMETCut(45,1) && passesMETCut(80))
				h_FTight_CERN_large ->Fill(LepPt->at(lep), fabs(LepEta->at(lep)), eventweight);

			if(passesMTCut(lep) && fFRMETbinseta[0]<=fabs(LepEta->at(lep)) && fabs(LepEta->at(lep))<fFRMETbinseta[fFRMETn_binseta-1]){
				if(fFRMETbinspt[0]<=LepPt->at(lep) && LepPt->at(lep)<fFRMETbinspt[fFRMETn_binspt-1]){
					int i = h_Tight_FRMETZoomEta ->FindBin(fabs(LepEta->at(lep)));
					int j = h_Tight_FRMETZoomPt  ->FindBin(LepPt->at(lep));
					h_Tight_METZoom[(i-1)*(fFRMETn_binspt-1) + j - 1] ->Fill((getMET()), eventweight);
				}
			}
		}
	}

	h_FRatio->Divide(h_FTight, h_FLoose);

}


//____________________________________________________________________________
void Fakerates::fillFRPlotsTTBar(float eventweight = 1.0){
	/* 
	create plos for muons and electrons
	parameters: none
	return: none
	*/


	int lep(-1), jet(-1);
	std::vector<float, std::allocator<float> >* LepPt    = getLepPt();
	std::vector<float, std::allocator<float> >* LepEta   = getLepEta();
	std::vector<float, std::allocator<float> >* LepPFIso = getLepPFIso();
	//std::vector<int, std::allocator<int> >* LepID        = getLepID();
	std::vector<int, std::allocator<int> >* LepMID       = getLepMID();
	std::vector<int, std::allocator<int> >* LepGMID      = getLepGMID();

	++fCounter_all;



	// Checks for Trigger

	if(!isFRRegionLepEventTTBar()) return; 

	++fCounter_trigger;



	// fill Plots for all loose leptons in the event

	for(int j=0; j < LepPt->size(); ++j){


		// loose lepton

		if(!isLooseLeptonTTBar(j)) continue;

		int thisorigin = getLeptonOrigin(LepMID->at(j), LepGMID->at(j));

		if(thisorigin == 1) setLepIsPrompt(j, true);
		else                setLepIsPrompt(j, false);
	
		h_Loose_Provenance ->Fill(0);
		h_Loose_Provenance ->Fill(thisorigin);
		
		fillFHistTTBar(h_FLoose_0, LepPt->at(j), LepEta->at(j), eventweight);

		if     (thisorigin == 1) fillFHistTTBar(h_FLoose_1, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 2) fillFHistTTBar(h_FLoose_2, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 3) fillFHistTTBar(h_FLoose_3, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 4) fillFHistTTBar(h_FLoose_4, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 5) fillFHistTTBar(h_FLoose_5, LepPt->at(j), LepEta->at(j), eventweight);

		if     (thisorigin != 1) h_Loose_LepIso   ->Fill(LepPFIso->at(j), eventweight);
		h_Loose_LepIso_0   ->Fill(LepPFIso->at(j), eventweight);

		if     (thisorigin == 1) h_Loose_LepIso_1 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 2) h_Loose_LepIso_2 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 3) h_Loose_LepIso_3 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 4) h_Loose_LepIso_4 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 5) h_Loose_LepIso_5 ->Fill(LepPFIso->at(j), eventweight);

		bool istight = isTightLeptonTTBar(j);

		if(!istight && JetPt->size()>0 && !strstr(fName, "qcd")) {
	
			h_Loose_ClosJetPt_0   ->Fill(getJetPt(getClosestJet(j)), eventweight);

			if     (thisorigin == 1) h_Loose_ClosJetPt_1 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 2) h_Loose_ClosJetPt_2 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 3) h_Loose_ClosJetPt_3 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 4) h_Loose_ClosJetPt_4 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 5) h_Loose_ClosJetPt_5 ->Fill(getJetPt(getClosestJet(j)), eventweight);

		}

		if(!istight) {
			h_Loose_ProvenanceLNT ->Fill(0);
			h_Loose_ProvenanceLNT ->Fill(thisorigin);
		}

		//cout << Form("%d\t%d\t%d\t%.2f\t%d", Run, Lumi, Event, LepPt->at(j), isTightLeptonTTBar(j)) << endl;
	

		// tight lepton

		if(!isTightLeptonTTBar(j)) continue;
	
		h_Tight_Provenance ->Fill(0);
		h_Tight_Provenance ->Fill(thisorigin);
		
		fillFHistTTBar(h_FTight_0, LepPt->at(j), LepEta->at(j), eventweight);

		if     (thisorigin == 1) fillFHistTTBar(h_FTight_1, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 2) fillFHistTTBar(h_FTight_2, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 3) fillFHistTTBar(h_FTight_3, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 4) fillFHistTTBar(h_FTight_4, LepPt->at(j), LepEta->at(j), eventweight);
		else if(thisorigin == 5) fillFHistTTBar(h_FTight_5, LepPt->at(j), LepEta->at(j), eventweight);

		if     (thisorigin != 1) h_Tight_LepIso   ->Fill(LepPFIso->at(j), eventweight);
		h_Tight_LepIso_0   ->Fill(LepPFIso->at(j), eventweight);

		if     (thisorigin == 1) h_Tight_LepIso_1 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 2) h_Tight_LepIso_2 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 3) h_Tight_LepIso_3 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 4) h_Tight_LepIso_4 ->Fill(LepPFIso->at(j), eventweight);
		else if(thisorigin == 5) h_Tight_LepIso_5 ->Fill(LepPFIso->at(j), eventweight);
	
		if(JetPt->size()>0 && !strstr(fName, "qcd")) {
	
			h_Tight_ClosJetPt_0   ->Fill(getJetPt(getClosestJet(j)), eventweight);

			if     (thisorigin == 1) h_Tight_ClosJetPt_1 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 2) h_Tight_ClosJetPt_2 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 3) h_Tight_ClosJetPt_3 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 4) h_Tight_ClosJetPt_4 ->Fill(getJetPt(getClosestJet(j)), eventweight);
			else if(thisorigin == 5) h_Tight_ClosJetPt_5 ->Fill(getJetPt(getClosestJet(j)), eventweight);
		}	
	}


	// do the same thing after event selection (AES) for single lepton events

	if(isFRRegionLepEvent(lep, jet, fJetPtCut)){
		if(passesUpperMETMT(lep)) {
			int thisorigin = getLeptonOrigin(LepMID->at(lep), LepGMID->at(lep));

			h_Loose_ProvenanceAES ->Fill(0);
			h_Loose_ProvenanceAES ->Fill(thisorigin);

			if(strstr(fName, "qcd")) {
				h_Loose_ClosJetPt_0   ->Fill(getJetPt(getClosestJet(lep)), eventweight);

				if     (thisorigin == 1) h_Loose_ClosJetPt_1 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
				else if(thisorigin == 2) h_Loose_ClosJetPt_2 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
				else if(thisorigin == 3) h_Loose_ClosJetPt_3 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
				else if(thisorigin == 4) h_Loose_ClosJetPt_4 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
				else if(thisorigin == 5) h_Loose_ClosJetPt_5 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
			}


			if(isTightLeptonTTBar(lep)){
				h_Tight_ProvenanceAES ->Fill(0);
				h_Tight_ProvenanceAES ->Fill(thisorigin);
			
				if(strstr(fName, "qcd")) {
					h_Tight_ClosJetPt_0   ->Fill(getJetPt(getClosestJet(lep)), eventweight);

					if     (thisorigin == 1) h_Tight_ClosJetPt_1 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
					else if(thisorigin == 2) h_Tight_ClosJetPt_2 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
					else if(thisorigin == 3) h_Tight_ClosJetPt_3 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
					else if(thisorigin == 4) h_Tight_ClosJetPt_4 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
					else if(thisorigin == 5) h_Tight_ClosJetPt_5 ->Fill(getJetPt(getClosestJet(lep)), eventweight);
				}
			}
		}
	}
}



//____________________________________________________________________________
void Fakerates::bookHistos(){
	/*
	define histograms and binning
	parameters: none
	return: none
	*/ 

	std::vector<float> nvrtx_bins;
	nvrtx_bins.push_back( 0.);
	nvrtx_bins.push_back( 5.);
	nvrtx_bins.push_back(10.);
	nvrtx_bins.push_back(15.);
	nvrtx_bins.push_back(20.);
	nvrtx_bins.push_back(25.);
	nvrtx_bins.push_back(30.);
	nvrtx_bins.push_back(31.);
	int nvrtx_nbins = nvrtx_bins.size();

	h_FRatio             = new TH2F("h_FRatio"            , "FRatio", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FRatio           ->Sumw2(); 

	h_FLoose             = new TH2F("h_FLoose"            , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose           ->Sumw2(); 
	h_FLoose_CERN_small  = new TH2F("h_FLoose_CERN_small" , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_CERN_small->Sumw2(); 
	h_FLoose_CERN_large  = new TH2F("h_FLoose_CERN_large" , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_CERN_large->Sumw2(); 

	h_FLoose_0            = new TH2F("h_FLoose_0"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_0  ->Sumw2(); 
	h_FLoose_1            = new TH2F("h_FLoose_1"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_1  ->Sumw2(); 
	h_FLoose_2            = new TH2F("h_FLoose_2"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_2  ->Sumw2(); 
	h_FLoose_3            = new TH2F("h_FLoose_3"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_3  ->Sumw2(); 
	h_FLoose_4            = new TH2F("h_FLoose_4"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_4  ->Sumw2(); 
	h_FLoose_5            = new TH2F("h_FLoose_5"           , "FLoose", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FLoose_5  ->Sumw2(); 
 	
	h_Loose_LepIso_0      = new TH1F("h_Loose_LepIso_0"     , "Loose_LepIso_0"    , 20, 0 , 1.0); h_Loose_LepIso_0     ->Sumw2();
	h_Loose_LepIso_1      = new TH1F("h_Loose_LepIso_1"     , "Loose_LepIso_1"    , 20, 0 , 1.0); h_Loose_LepIso_1     ->Sumw2();
	h_Loose_LepIso_2      = new TH1F("h_Loose_LepIso_2"     , "Loose_LepIso_2"    , 20, 0 , 1.0); h_Loose_LepIso_2     ->Sumw2();
	h_Loose_LepIso_3      = new TH1F("h_Loose_LepIso_3"     , "Loose_LepIso_3"    , 20, 0 , 1.0); h_Loose_LepIso_3     ->Sumw2();
	h_Loose_LepIso_4      = new TH1F("h_Loose_LepIso_4"     , "Loose_LepIso_4"    , 20, 0 , 1.0); h_Loose_LepIso_4     ->Sumw2();
	h_Loose_LepIso_5      = new TH1F("h_Loose_LepIso_5"     , "Loose_LepIso_5"    , 20, 0 , 1.0); h_Loose_LepIso_5     ->Sumw2();
	
	h_Loose_ClosJetPt_0   = new TH1F("h_Loose_ClosJetPt_0"  , "Loose_ClosJetPt_0" , 10, 20, 120); h_Loose_ClosJetPt_0  ->Sumw2(); 
	h_Loose_ClosJetPt_1   = new TH1F("h_Loose_ClosJetPt_1"  , "Loose_ClosJetPt_1" , 10, 20, 120); h_Loose_ClosJetPt_1  ->Sumw2(); 
	h_Loose_ClosJetPt_2   = new TH1F("h_Loose_ClosJetPt_2"  , "Loose_ClosJetPt_2" , 10, 20, 120); h_Loose_ClosJetPt_2  ->Sumw2(); 
	h_Loose_ClosJetPt_3   = new TH1F("h_Loose_ClosJetPt_3"  , "Loose_ClosJetPt_3" , 10, 20, 120); h_Loose_ClosJetPt_3  ->Sumw2(); 
	h_Loose_ClosJetPt_4   = new TH1F("h_Loose_ClosJetPt_4"  , "Loose_ClosJetPt_4" , 10, 20, 120); h_Loose_ClosJetPt_4  ->Sumw2(); 
	h_Loose_ClosJetPt_5   = new TH1F("h_Loose_ClosJetPt_5"  , "Loose_ClosJetPt_5" , 10, 20, 120); h_Loose_ClosJetPt_5  ->Sumw2(); 

	h_Loose_ClosJetPtLNT_0 = new TH1F("h_Loose_ClosJetPtLNT_0"  , "Loose_ClosJetPtLNT_0" , 10, 20, 120); h_Loose_ClosJetPtLNT_0  ->Sumw2(); 
	h_Loose_ClosJetPtLNT_1 = new TH1F("h_Loose_ClosJetPtLNT_1"  , "Loose_ClosJetPtLNT_1" , 10, 20, 120); h_Loose_ClosJetPtLNT_1  ->Sumw2(); 
	h_Loose_ClosJetPtLNT_2 = new TH1F("h_Loose_ClosJetPtLNT_2"  , "Loose_ClosJetPtLNT_2" , 10, 20, 120); h_Loose_ClosJetPtLNT_2  ->Sumw2(); 
	h_Loose_ClosJetPtLNT_3 = new TH1F("h_Loose_ClosJetPtLNT_3"  , "Loose_ClosJetPtLNT_3" , 10, 20, 120); h_Loose_ClosJetPtLNT_3  ->Sumw2(); 
	h_Loose_ClosJetPtLNT_4 = new TH1F("h_Loose_ClosJetPtLNT_4"  , "Loose_ClosJetPtLNT_4" , 10, 20, 120); h_Loose_ClosJetPtLNT_4  ->Sumw2(); 
	h_Loose_ClosJetPtLNT_5 = new TH1F("h_Loose_ClosJetPtLNT_5"  , "Loose_ClosJetPtLNT_5" , 10, 20, 120); h_Loose_ClosJetPtLNT_5  ->Sumw2(); 

	h_Loose_Provenance    = new TH1F("h_Loose_Provenance"   , "Loose_Provenance"   , 6 , 0 , 6  );
	h_Loose_ProvenanceLNT = new TH1F("h_Loose_ProvenanceLNT", "Loose_ProvenanceLNT", 6 , 0 , 6  );
	h_Loose_ProvenanceAES = new TH1F("h_Loose_ProvenanceAES", "Loose_ProvenanceAES", 6 , 0 , 6  );

	h_Loose_FRZoomEta     = new TH1F("h_Loose_FRZoomEta"    , "Loose_FRZoomEta"   , fFRn_binseta-1   , &fFRbinseta[0]   ); // empty, just to use binning
	h_Loose_FRZoomPt      = new TH1F("h_Loose_FRZoomPt"     , "Loose_FRZoomPt"    , fFRn_binspt-1    , &fFRbinspt[0]    ); // empty, just to use binning
	h_Loose_FRMETZoomEta  = new TH1F("h_Loose_FRMETZoomEta" , "Loose_FRMETZoomEta", fFRMETn_binseta-1, &fFRMETbinseta[0]); // empty, just to use binning
	h_Loose_FRMETZoomPt   = new TH1F("h_Loose_FRMETZoomPt"  , "Loose_FRMETZoomPt" , fFRMETn_binspt-1 , &fFRMETbinspt[0] ); // empty, just to use binning

	float eta_min = 0. , eta_max = 2.4;
	float pt_min  = 10., pt_max  = 70.;
	int   eta_bin = 12 , pt_bin  = 20 ;

	h_Loose_LepPt         = new TH1F("h_Loose_LepPt"        , "Loose_LepPt"     , pt_bin  , pt_min  , pt_max ); h_Loose_LepPt     -> Sumw2();
	h_Loose_LepEta        = new TH1F("h_Loose_LepEta"       , "Loose_LepEta"    , eta_bin , eta_min , eta_max); h_Loose_LepEta    -> Sumw2();
 	h_Loose_LepIso        = new TH1F("h_Loose_LepIso"       , "Loose_LepIso"    , 20      ,   0     , 1.0    ); h_Loose_LepIso    -> Sumw2();
	h_Loose_D0            = new TH1F("h_Loose_D0"           , "Loose_D0"        , 20      ,   0     , 0.2    ); h_Loose_D0        -> Sumw2();

	h_Loose_LepEta_30     = new TH1F("h_Loose_LepEta_30"    , "Loose_LepEta_30" , eta_bin , eta_min , eta_max); h_Loose_LepEta_30 -> Sumw2();
	h_Loose_LepEta_40     = new TH1F("h_Loose_LepEta_40"    , "Loose_LepEta_40" , eta_bin , eta_min , eta_max); h_Loose_LepEta_40 -> Sumw2();
	h_Loose_LepEta_50     = new TH1F("h_Loose_LepEta_50"    , "Loose_LepEta_50" , eta_bin , eta_min , eta_max); h_Loose_LepEta_50 -> Sumw2();
	h_Loose_LepEta_60     = new TH1F("h_Loose_LepEta_60"    , "Loose_LepEta_60" , eta_bin , eta_min , eta_max); h_Loose_LepEta_60 -> Sumw2();

	h_Loose_LepPt_30      = new TH1F("h_Loose_LepPt_30"     , "Loose_LepPt_30"  , pt_bin  , pt_min  , pt_max ); h_Loose_LepPt_30  -> Sumw2();
	h_Loose_LepPt_40      = new TH1F("h_Loose_LepPt_40"     , "Loose_LepPt_40"  , pt_bin  , pt_min  , pt_max ); h_Loose_LepPt_40  -> Sumw2();
	h_Loose_LepPt_50      = new TH1F("h_Loose_LepPt_50"     , "Loose_LepPt_50"  , pt_bin  , pt_min  , pt_max ); h_Loose_LepPt_50  -> Sumw2();
	h_Loose_LepPt_60      = new TH1F("h_Loose_LepPt_60"     , "Loose_LepPt_60"  , pt_bin  , pt_min  , pt_max ); h_Loose_LepPt_60  -> Sumw2();

	h_Loose_HT            = new TH1F("h_Loose_HT"           , "Loose_HT"        , 10      ,  0      , 400    ); h_Loose_HT        -> Sumw2();
	h_Loose_MET           = new TH1F("h_Loose_MET"          , "Loose_MET"       , 10      ,  0      , 100    ); h_Loose_MET       -> Sumw2();
	h_Loose_METnoMTCut    = new TH1F("h_Loose_METnoMTCut"   , "Loose_METnoMTCut", 10      ,  0      , 100    ); h_Loose_METnoMTCut-> Sumw2();
	h_Loose_MT            = new TH1F("h_Loose_MT"           , "Loose_MT"        , 10      ,  0      , 100    ); h_Loose_MT        -> Sumw2();
	h_Loose_MTMET20       = new TH1F("h_Loose_MTMET20"      , "Loose_MTMET20"   , 20      ,  0      , 200    ); h_Loose_MTMET20   -> Sumw2();
	h_Loose_MTMET30       = new TH1F("h_Loose_MTMET30"      , "Loose_MTMET30"   , 20      ,  0      , 200    ); h_Loose_MTMET30   -> Sumw2();

	h_Loose_MaxJPt        = new TH1F("h_Loose_MaxJPt"       , "Loose_MaxJPt"    , 10      ,  20     , 120    ); h_Loose_MaxJPt    -> Sumw2();
	h_Loose_MaxJCPt       = new TH1F("h_Loose_MaxJCPt"      , "Loose_MaxJCPt"   , 10      ,  20     , 120    ); h_Loose_MaxJCPt   -> Sumw2();
	h_Loose_MaxJRPt       = new TH1F("h_Loose_MaxJRPt"      , "Loose_MaxJRPt"   , 10      ,  20     , 120    ); h_Loose_MaxJRPt   -> Sumw2();
	h_Loose_MaxJCSV       = new TH1F("h_Loose_MaxJCSV"      , "Loose_MaxJCSV"   , 20      ,  0      , 1.0    ); h_Loose_MaxJCSV   -> Sumw2();

	h_Loose_AllJRPt       = new TH1F("h_Loose_AllJRPt"      , "Loose_AllJRPt"   , 15      ,  0      , 150    ); h_Loose_AllJRPt   -> Sumw2();
	h_Loose_AllJCPt       = new TH1F("h_Loose_AllJCPt"      , "Loose_AllJCPt"   , 15      ,  0      , 150    ); h_Loose_AllJCPt   -> Sumw2();
	h_Loose_AllJEta       = new TH1F("h_Loose_AllJEta"      , "Loose_AllJEta"   , 12      ,  0      , 2.4    ); h_Loose_AllJEta   -> Sumw2();
	h_Loose_AllJCSV       = new TH1F("h_Loose_AllJCSV"      , "Loose_AllJCSV"   , 20      ,  0      , 1.0    ); h_Loose_AllJCSV   -> Sumw2();

	//h_Loose_AllJEtatest1  = new TH1F("h_Loose_AllJEtatest1" , "Loose_AllJEtatest1", 12    ,  0      , 2.4    ); h_Loose_AllJEtatest1 -> Sumw2();
	//h_Loose_AllJEtatest2  = new TH1F("h_Loose_AllJEtatest2" , "Loose_AllJEtatest2", 12    ,  0      , 2.4    ); h_Loose_AllJEtatest2 -> Sumw2();
	//h_Loose_AllJEtatest3  = new TH1F("h_Loose_AllJEtatest3" , "Loose_AllJEtatest3", 12    ,  0      , 2.4    ); h_Loose_AllJEtatest3 -> Sumw2();

	h_Loose_NBJets        = new TH1F("h_Loose_NBJets"       , "Loose_NBJets"    , 3       ,  0      , 3      ); h_Loose_NBJets     -> Sumw2();
	h_Loose_NJets         = new TH1F("h_Loose_NJets"        , "Loose_NJets"     , 5       ,  1      , 6      ); h_Loose_NJets      -> Sumw2();
	h_Loose_NVertices     = new TH1F("h_Loose_NVertices"    , "Loose_NVertices" , 40      ,  0      , 40     ); h_Loose_NVertices  -> Sumw2();
	h_Loose_NVertices1    = new TH1F("h_Loose_NVertices1"   , "Loose_NVertices1", nvrtx_nbins-1, &nvrtx_bins[0]); h_Loose_NVertices1 -> Sumw2();
	h_Loose_NVerticesMET20= new TH1F("h_Loose_NVerticesMET20", "Loose_NVerticesMET20", 40 , 0       , 40     ); h_Loose_NVerticesMET20 -> Sumw2();

	h_Loose_AwayJetDR     = new TH1F("h_Loose_AwayJetDR"    , "Loose_AwayJetDR" , 15      ,  0      , 6      ); h_Loose_AwayJetDR  -> Sumw2();
	h_Loose_AwayJetPt     = new TH1F("h_Loose_AwayJetPt"    , "Loose_AwayJetPt" , 10      ,  20     , 120    ); h_Loose_AwayJetPt  -> Sumw2();
	h_Loose_ClosJetDR     = new TH1F("h_Loose_ClosJetDR"    , "Loose_ClosJetDR" , 15      ,  0      , 1      ); h_Loose_ClosJetDR  -> Sumw2();
	h_Loose_ClosJetPt     = new TH1F("h_Loose_ClosJetPt"    , "Loose_ClosJetPt" , 10      ,  20     , 120    ); h_Loose_ClosJetPt  -> Sumw2();

	h_Loose_JCPtJEta      = new TH2F("h_Loose_JCPtJEta"     , "Loose_JCPtJEta"  , eta_bin, eta_min, eta_max, 10, 20, 120); h_Loose_JCPtJEta->Sumw2();
	h_Loose_JRPtJEta      = new TH2F("h_Loose_JRPtJEta"     , "Loose_JRPtJEta"  , eta_bin, eta_min, eta_max, 10, 20, 120); h_Loose_JRPtJEta->Sumw2();
	h_Loose_JCPtJPt       = new TH2F("h_Loose_JCPtJPt"      , "Loose_JCPtJPt"   , pt_bin,  pt_min,  pt_max,  10, 20, 120); h_Loose_JCPtJPt ->Sumw2();
	h_Loose_JRPtJPt       = new TH2F("h_Loose_JRPtJPt"      , "Loose_JRPtJPt"   , pt_bin,  pt_min,  pt_max,  10, 20, 120); h_Loose_JRPtJPt ->Sumw2();

	h_Loose_DJPtJEta      = new TH2F("h_Loose_DJPtJEta"     , "Loose_DJPtJEta"  , eta_bin, eta_min, eta_max, 30, -30, 30); h_Loose_DJPtJEta->Sumw2();
	h_Loose_FJPtJEta      = new TH2F("h_Loose_FJPtJEta"     , "Loose_FJPtJEta"  , eta_bin, eta_min, eta_max, 30, -1, 1);   h_Loose_FJPtJEta->Sumw2();
	h_Loose_DJPtJPt       = new TH2F("h_Loose_DJPtJPt"      , "Loose_DJPtJPt"   , pt_bin,  pt_min,  pt_max,  30, -30, 30); h_Loose_DJPtJPt ->Sumw2();
	h_Loose_FJPtJPt       = new TH2F("h_Loose_FJPtJPt"      , "Loose_FJPtJPt"   , pt_bin,  pt_min,  pt_max,  30, -1, 1);   h_Loose_FJPtJPt ->Sumw2();

	h_Loose_DFZoomEta     = new TH1F("h_Loose_DFZoomEta"    , "Loose_DFZoomEta" , fDFn_binseta-1, &fDFbinseta[0]); // empty, just to use binning
	h_Loose_DFZoomPt      = new TH1F("h_Loose_DFZoomPt"     , "Loose_DFZoomPt"  , fDFn_binspt-1 , &fDFbinspt[0] ); // empty, just to use binning

	int n = 0;
	char nn[2];
	char name[150], title[150];
	for(int i=0; i<fDFn_binseta-1; ++i) {
		for(int j=0; j<fDFn_binspt-1; ++j) {
			if(n<10) sprintf(nn, "0%d", n);
			else sprintf(nn, "%d", n);
			sprintf(name, "h_Loose_DJPtZoomC_%s", nn);
			sprintf(title, "Loose_DJPtZoomC_%s", nn);
			h_Loose_DJPtZoomC[n] = new TH1F(name, title, 80, -30., 10.); 
			h_Loose_DJPtZoomC[n]->Sumw2();
			sprintf(name, "h_Loose_DJPtZoomR_%s", nn);
			sprintf(title, "Loose_DJPtZoomR_%s", nn);
			h_Loose_DJPtZoomR[n] = new TH1F(name, title, 80, -30., 10.); 
			h_Loose_DJPtZoomR[n]->Sumw2();
			sprintf(name, "h_Loose_FJPtZoomC_%s", nn);
			sprintf(title, "Loose_FJPtZoomC_%s", nn);
			h_Loose_FJPtZoomC[n] = new TH1F(name, title, 50, -1., 1.);
			h_Loose_FJPtZoomC[n]->Sumw2();
			sprintf(name, "h_Loose_FJPtZoomR_%s", nn);
			sprintf(title, "Loose_FJPtZoomR_%s", nn);
			h_Loose_FJPtZoomR[n] = new TH1F(name, title, 50, -1., 1.);
			h_Loose_FJPtZoomR[n]->Sumw2();
			++n;
		}
	}

	n = 0;
	for(int i=0; i<fFRMETn_binseta-1; ++i) {
		for(int j=0; j<fFRMETn_binspt-1; ++j) {
			if(n<10) sprintf(nn, "0%d", n);
			else sprintf(nn, "%d", n);
			sprintf(name, "h_Loose_METZoom_%s", nn);
			sprintf(title, "Loose_METZoom_%s", nn);
			h_Loose_METZoom[n] = new TH1F(name, title, 20, 0, 100);
			h_Loose_METZoom[n]->Sumw2();
			++n;
		}
	}

	h_FTight             = new TH2F("h_FTight"            , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight           ->Sumw2(); 
	h_FTight_CERN_small  = new TH2F("h_FTight_CERN_small" , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_CERN_small->Sumw2(); 
	h_FTight_CERN_large  = new TH2F("h_FTight_CERN_large" , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_CERN_large->Sumw2(); 

	h_FTight_0           = new TH2F("h_FTight_0"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_0  ->Sumw2(); 
	h_FTight_1           = new TH2F("h_FTight_1"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_1  ->Sumw2(); 
	h_FTight_2           = new TH2F("h_FTight_2"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_2  ->Sumw2(); 
	h_FTight_3           = new TH2F("h_FTight_3"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_3  ->Sumw2(); 
	h_FTight_4           = new TH2F("h_FTight_4"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_4  ->Sumw2(); 
	h_FTight_5           = new TH2F("h_FTight_5"          , "FTight", fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); h_FTight_5  ->Sumw2(); 
 	
	h_Tight_LepIso_0      = new TH1F("h_Tight_LepIso_0"     , "Tight_LepIso_0"    , 20, 0 , 1.0); h_Tight_LepIso_0     ->Sumw2();
	h_Tight_LepIso_1      = new TH1F("h_Tight_LepIso_1"     , "Tight_LepIso_1"    , 20, 0 , 1.0); h_Tight_LepIso_1     ->Sumw2();
	h_Tight_LepIso_2      = new TH1F("h_Tight_LepIso_2"     , "Tight_LepIso_2"    , 20, 0 , 1.0); h_Tight_LepIso_2     ->Sumw2();
	h_Tight_LepIso_3      = new TH1F("h_Tight_LepIso_3"     , "Tight_LepIso_3"    , 20, 0 , 1.0); h_Tight_LepIso_3     ->Sumw2();
	h_Tight_LepIso_4      = new TH1F("h_Tight_LepIso_4"     , "Tight_LepIso_4"    , 20, 0 , 1.0); h_Tight_LepIso_4     ->Sumw2();
	h_Tight_LepIso_5      = new TH1F("h_Tight_LepIso_5"     , "Tight_LepIso_5"    , 20, 0 , 1.0); h_Tight_LepIso_5     ->Sumw2();
	
	h_Tight_ClosJetPt_0   = new TH1F("h_Tight_ClosJetPt_0"  , "Tight_ClosJetPt_0" , 10, 20, 120); h_Tight_ClosJetPt_0  ->Sumw2(); 
	h_Tight_ClosJetPt_1   = new TH1F("h_Tight_ClosJetPt_1"  , "Tight_ClosJetPt_1" , 10, 20, 120); h_Tight_ClosJetPt_1  ->Sumw2(); 
	h_Tight_ClosJetPt_2   = new TH1F("h_Tight_ClosJetPt_2"  , "Tight_ClosJetPt_2" , 10, 20, 120); h_Tight_ClosJetPt_2  ->Sumw2(); 
	h_Tight_ClosJetPt_3   = new TH1F("h_Tight_ClosJetPt_3"  , "Tight_ClosJetPt_3" , 10, 20, 120); h_Tight_ClosJetPt_3  ->Sumw2(); 
	h_Tight_ClosJetPt_4   = new TH1F("h_Tight_ClosJetPt_4"  , "Tight_ClosJetPt_4" , 10, 20, 120); h_Tight_ClosJetPt_4  ->Sumw2(); 
	h_Tight_ClosJetPt_5   = new TH1F("h_Tight_ClosJetPt_5"  , "Tight_ClosJetPt_5" , 10, 20, 120); h_Tight_ClosJetPt_5  ->Sumw2(); 

	h_Tight_Provenance    = new TH1F("h_Tight_Provenance"   , "Tight_Provenance"   , 6 , 0 , 6  );
	h_Tight_ProvenanceAES = new TH1F("h_Tight_ProvenanceAES", "Tight_ProvenanceAES", 6 , 0 , 6  );

	h_Tight_FRZoomEta     = new TH1F("h_Tight_FRZoomEta"    , "Tight_FRZoomEta"   , fFRn_binseta-1   , &fFRbinseta[0]   ); // empty, just to use binning
	h_Tight_FRZoomPt      = new TH1F("h_Tight_FRZoomPt"     , "Tight_FRZoomPt"    , fFRn_binspt-1    , &fFRbinspt[0]    ); // empty, just to use binning
	h_Tight_FRMETZoomEta  = new TH1F("h_Tight_FRMETZoomEta" , "Tight_FRMETZoomEta", fFRMETn_binseta-1, &fFRMETbinseta[0]); // empty, just to use binning
	h_Tight_FRMETZoomPt   = new TH1F("h_Tight_FRMETZoomPt"  , "Tight_FRMETZoomPt" , fFRMETn_binspt-1 , &fFRMETbinspt[0] ); // empty, just to use binning
	
	h_Tight_LepPt         = new TH1F("h_Tight_LepPt"        , "Tight_LepPt"     , pt_bin  , pt_min  , pt_max ); h_Tight_LepPt     -> Sumw2();
	h_Tight_LepEta        = new TH1F("h_Tight_LepEta"       , "Tight_LepEta"    , eta_bin , eta_min , eta_max); h_Tight_LepEta    -> Sumw2();
	h_Tight_LepIso        = new TH1F("h_Tight_LepIso"       , "Tight_LepIso"    , 20      , 0.      , 1.0    ); h_Tight_LepIso    -> Sumw2();
 	h_Tight_D0            = new TH1F("h_Tight_D0"           , "Tight_D0"        , 20      , 0.      , 0.2    ); h_Tight_D0        -> Sumw2();
    
	h_Tight_LepEta_30     = new TH1F("h_Tight_LepEta_30"    , "Tight_LepEta_30" , eta_bin , eta_min , eta_max); h_Tight_LepEta_30 -> Sumw2();
	h_Tight_LepEta_40     = new TH1F("h_Tight_LepEta_40"    , "Tight_LepEta_40" , eta_bin , eta_min , eta_max); h_Tight_LepEta_40 -> Sumw2();
	h_Tight_LepEta_50     = new TH1F("h_Tight_LepEta_50"    , "Tight_LepEta_50" , eta_bin , eta_min , eta_max); h_Tight_LepEta_50 -> Sumw2();
	h_Tight_LepEta_60     = new TH1F("h_Tight_LepEta_60"    , "Tight_LepEta_60" , eta_bin , eta_min , eta_max); h_Tight_LepEta_60 -> Sumw2();
    
	h_Tight_LepPt_30      = new TH1F("h_Tight_LepPt_30"     , "Tight_LepPt_30"  , pt_bin  , pt_min  , pt_max );  h_Tight_LepPt_30  -> Sumw2();
	h_Tight_LepPt_40      = new TH1F("h_Tight_LepPt_40"     , "Tight_LepPt_40"  , pt_bin  , pt_min  , pt_max );  h_Tight_LepPt_40  -> Sumw2();
	h_Tight_LepPt_50      = new TH1F("h_Tight_LepPt_50"     , "Tight_LepPt_50"  , pt_bin  , pt_min  , pt_max );  h_Tight_LepPt_50  -> Sumw2();
	h_Tight_LepPt_60      = new TH1F("h_Tight_LepPt_60"     , "Tight_LepPt_60"  , pt_bin  , pt_min  , pt_max );  h_Tight_LepPt_60  -> Sumw2();
                                                                                         
	h_Tight_HT            = new TH1F("h_Tight_HT"           , "Tight_HT"        , 10      , 0       , 400    ); h_Tight_HT         -> Sumw2();
	h_Tight_MET           = new TH1F("h_Tight_MET"          , "Tight_MET"       , 10      , 0       , 100    ); h_Tight_MET        -> Sumw2();
	h_Tight_METnoMTCut    = new TH1F("h_Tight_METnoMTCut"   , "Tight_METnoMTCut", 10      , 0       , 100    ); h_Tight_METnoMTCut -> Sumw2();
	h_Tight_MT            = new TH1F("h_Tight_MT"           , "Tight_MT"        , 10      , 0       , 100    ); h_Tight_MT         -> Sumw2();
	h_Tight_MTMET20       = new TH1F("h_Tight_MTMET20"      , "Tight_MTMET20"   , 20      , 0       , 200    ); h_Tight_MTMET20    -> Sumw2();
	h_Tight_MTMET30       = new TH1F("h_Tight_MTMET30"      , "Tight_MTMET30"   , 20      , 0       , 200    ); h_Tight_MTMET30    -> Sumw2();
                                                                                                 
	h_Tight_MaxJPt        = new TH1F("h_Tight_MaxJPt"       , "Tight_MaxJPt"    , 10      , 20      , 120    ); h_Tight_MaxJPt     -> Sumw2();
	h_Tight_MaxJCPt       = new TH1F("h_Tight_MaxJCPt"      , "Tight_MaxJCPt"   , 10      , 20      , 120    ); h_Tight_MaxJCPt    -> Sumw2();
	h_Tight_MaxJRPt       = new TH1F("h_Tight_MaxJRPt"      , "Tight_MaxJRPt"   , 10      , 20      , 120    ); h_Tight_MaxJRPt    -> Sumw2();
	h_Tight_MaxJCSV       = new TH1F("h_Tight_MaxJCSV"      , "Tight_MaxJCSV"   , 20      ,  0      , 1.0    ); h_Tight_MaxJCSV   -> Sumw2();

	h_Tight_AllJCPt       = new TH1F("h_Tight_AllJCPt"      , "Tight_AllJCPt"   , 15      , 0       , 150    ); h_Tight_AllJCPt    -> Sumw2();
	h_Tight_AllJRPt       = new TH1F("h_Tight_AllJRPt"      , "Tight_AllJRPt"   , 15      , 0       , 150    ); h_Tight_AllJRPt    -> Sumw2();
	h_Tight_AllJEta       = new TH1F("h_Tight_AllJEta"      , "Tight_AllJEta"   , 12      , 0       , 2.4    ); h_Tight_AllJEta    -> Sumw2();
	h_Tight_AllJCSV       = new TH1F("h_Tight_AllJCSV"      , "Tight_AllJCSV"   , 20      , 0       , 1.0    ); h_Tight_AllJCSV    -> Sumw2();

	h_Tight_NBJets        = new TH1F("h_Tight_NBJets"       , "Tight_NBJets"    , 3       , 0       , 3      ); h_Tight_NBJets     -> Sumw2();
	h_Tight_NJets         = new TH1F("h_Tight_NJets"        , "Tight_NJets"     , 5       , 1       , 6      ); h_Tight_NJets      -> Sumw2();
	h_Tight_NVertices     = new TH1F("h_Tight_NVertices"    , "Tight_NVertices" , 40      , 0       , 40     ); h_Tight_NVertices  -> Sumw2();
	h_Tight_NVertices1    = new TH1F("h_Tight_NVertices1"   , "Tight_NVertices1", nvrtx_nbins-1, &nvrtx_bins[0]); h_Tight_NVertices1  -> Sumw2();
	h_Tight_NVerticesMET20= new TH1F("h_Tight_NVerticesMET20", "Tight_NVerticesMET20", 40 , 0       , 40     ); h_Tight_NVerticesMET20 -> Sumw2();
                                                                                                 
	h_Tight_AwayJetDR     = new TH1F("h_Tight_AwayJetDR"    , "Tight_AwayJetDR" , 15      ,  0      , 6      ); h_Tight_AwayJetDR  -> Sumw2();
	h_Tight_AwayJetPt     = new TH1F("h_Tight_AwayJetPt"    , "Tight_AwayJetPt" , 10      ,  20     , 120    ); h_Tight_AwayJetPt  -> Sumw2();
	h_Tight_ClosJetDR     = new TH1F("h_Tight_ClosJetDR"    , "Tight_ClosJetDR" , 15      ,  0      , 1      ); h_Tight_ClosJetDR  -> Sumw2();
	h_Tight_ClosJetPt     = new TH1F("h_Tight_ClosJetPt"    , "Tight_ClosJetPt" , 10      ,  20     , 120    ); h_Tight_ClosJetPt  -> Sumw2();

	h_Tight_JCPtJEta      = new TH2F("h_Tight_JCPtJEta"     , "Tight_JCPtJEta"  , eta_bin, eta_min, eta_max, 10, 20, 120); h_Tight_JCPtJEta->Sumw2();
	h_Tight_JRPtJEta      = new TH2F("h_Tight_JRPtJEta"     , "Tight_JRPtJEta"  , eta_bin, eta_min, eta_max, 10, 20, 120); h_Tight_JRPtJEta->Sumw2();
	h_Tight_JCPtJPt       = new TH2F("h_Tight_JCPtJPt"      , "Tight_JCPtJPt"   , pt_bin,  pt_min,  pt_max,  10, 20, 120); h_Tight_JCPtJPt ->Sumw2();
	h_Tight_JRPtJPt       = new TH2F("h_Tight_JRPtJPt"      , "Tight_JRPtJPt"   , pt_bin,  pt_min,  pt_max,  10, 20, 120); h_Tight_JRPtJPt ->Sumw2();

	h_Tight_DJPtJEta      = new TH2F("h_Tight_DJPtJEta"     , "Tight_DJPtJEta"  , eta_bin, eta_min, eta_max, 30, -30, 30); h_Tight_DJPtJEta->Sumw2();
	h_Tight_FJPtJEta      = new TH2F("h_Tight_FJPtJEta"     , "Tight_FJPtJEta"  , eta_bin, eta_min, eta_max, 30, -1, 1);   h_Tight_FJPtJEta->Sumw2();
	h_Tight_DJPtJPt       = new TH2F("h_Tight_DJPtJPt"      , "Tight_DJPtJPt"   , pt_bin,  pt_min,  pt_max,  30, -30, 30); h_Tight_DJPtJPt ->Sumw2();
	h_Tight_FJPtJPt       = new TH2F("h_Tight_FJPtJPt"      , "Tight_FJPtJPt"   , pt_bin,  pt_min,  pt_max,  30, -1, 1);   h_Tight_FJPtJPt ->Sumw2();

	h_Tight_DFZoomEta     = new TH1F("h_Tight_DFZoomEta"    , "Tight_DFZoomEta" , fDFn_binseta-1, &fDFbinseta[0]); // empty, just to use binning
	h_Tight_DFZoomPt      = new TH1F("h_Tight_DFZoomPt"     , "Tight_DFZoomPt"  , fDFn_binspt-1 , &fDFbinspt[0] ); // empty, just to use binning

	n = 0;
	for(int i=0; i<fDFn_binseta-1; ++i) {
		for(int j=0; j<fDFn_binspt-1; ++j) {
			if(n<10) sprintf(nn, "0%d", n);
			else sprintf(nn, "%d", n);
			sprintf(name, "h_Tight_DJPtZoomC_%s", nn);
			sprintf(title, "Tight_DJPtZoomC_%s", nn);
			h_Tight_DJPtZoomC[n] = new TH1F(name, title, 80, -30., 10.);
			h_Tight_DJPtZoomC[n]->Sumw2();
			sprintf(name, "h_Tight_DJPtZoomR_%s", nn);
			sprintf(title, "Tight_DJPtZoomR_%s", nn);
			h_Tight_DJPtZoomR[n] = new TH1F(name, title, 80, -30., 10.);
			h_Tight_DJPtZoomR[n]->Sumw2();
			sprintf(name, "h_Tight_FJPtZoomC_%s", nn);
			sprintf(title, "Tight_FJPtZoomC_%s", nn);
			h_Tight_FJPtZoomC[n] = new TH1F(name, title, 50, -1., 1.);
			h_Tight_FJPtZoomC[n]->Sumw2();
			sprintf(name, "h_Tight_FJPtZoomR_%s", nn);
			sprintf(title, "Tight_FJPtZoomR_%s", nn);
			h_Tight_FJPtZoomR[n] = new TH1F(name, title, 50, -1., 1.);
			h_Tight_FJPtZoomR[n]->Sumw2();
			++n;
		}
	}
	n = 0;
	for(int i=0; i<fFRMETn_binseta-1; ++i) {
		for(int j=0; j<fFRMETn_binspt-1; ++j) {
			if(n<10) sprintf(nn, "0%d", n);
			else sprintf(nn, "%d", n);
			sprintf(name, "h_Tight_METZoom_%s", nn);
			sprintf(title, "Tight_METZoom_%s", nn);
			h_Tight_METZoom[n] = new TH1F(name, title, 20, 0, 100);
			h_Tight_METZoom[n]->Sumw2();
			++n;
		}
	}

	
	/// TRIGGERS
	for (size_t tr=0; tr<iNTRIGS; tr++){
		TString title = "Loose "+TrigNames[tr];
		h_FLoose_trig[tr] = new TH2F("h_FLoose_"+TrigNames[tr], title ,fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); 
		h_FLoose_trig[tr]->Sumw2();  
		
		title = "Tight "+TrigNames[tr];
		h_FTight_trig[tr] = new TH2F("h_FTight_"+TrigNames[tr], title ,fFRn_binspt-1, &fFRbinspt[0], fFRn_binseta-1, &fFRbinseta[0]); 
		h_FTight_trig[tr]->Sumw2();  
		
		title = "Loose_Pt "+TrigNames[tr];
		h_Loose_LepPt_trig [tr] = new TH1F("h_Loose_LepPt_"+TrigNames[tr], title, 100  , pt_min  , pt_max);     h_Loose_LepPt_trig[tr]-> Sumw2();    
		title = "Loose_Eta "+TrigNames[tr];
		h_Loose_LepEta_trig[tr] = new TH1F("h_Loose_LepEta_"+TrigNames[tr], title, 100  , eta_min  , eta_max);  h_Loose_LepEta_trig[tr]-> Sumw2();    
		
		title = "Tight_Pt "+TrigNames[tr];
		h_Tight_LepPt_trig [tr] = new TH1F("h_Tight_LepPt_"+TrigNames[tr], title, 100  , pt_min  , pt_max);     h_Tight_LepPt_trig[tr]-> Sumw2();    	
		title = "Tight_Eta "+TrigNames[tr];
		h_Tight_LepEta_trig[tr] = new TH1F("h_Tight_LepEta_"+TrigNames[tr], title, 100  , eta_min  , eta_max);  h_Tight_LepEta_trig[tr]-> Sumw2();    
			  
		title = "Purity " + TrigNames[tr];
		h_Purity[tr] = new TH1F("h_Purity_"+TrigNames[tr], title, 27, -0.5, 26.5);
		h_Purity[tr]->Sumw2();
		
		title = "Purity LeptonPt " + TrigNames[tr];
		h_Purity_LepPt   [tr] = new TH1F("h_Purity_LepPt_"   +TrigNames[tr], title, 100, pt_min, pt_max);  h_Purity_LepPt   [tr]->Sumw2(); 
		title = "Purity JetPt " + TrigNames[tr];
		h_Purity_JetPt   [tr] = new TH1F("h_Purity_JetPt_"   +TrigNames[tr], title,  10,    20.,   120.);  h_Purity_JetPt   [tr]->Sumw2();
		title = "Purity JetRawPt " + TrigNames[tr];
		h_Purity_JetRawPt[tr] = new TH1F("h_Purity_JetRawPt_"+TrigNames[tr], title,  10,    20.,   120.);  h_Purity_JetRawPt[tr]->Sumw2();
		title = "Purity DRLepJet " + TrigNames[tr];
		h_Purity_DRLepJet[tr] = new TH1F("h_Purity_DRLepJet_"+TrigNames[tr], title,  15,     0.,     6.);  h_Purity_DRLepJet[tr]->Sumw2();
		title = "Purity MET " + TrigNames[tr];
		h_Purity_MET     [tr] = new TH1F("h_Purity_MET_"     +TrigNames[tr], title,  10,     0.,   100.);  h_Purity_MET     [tr]->Sumw2();
		title = "Purity MT " + TrigNames[tr];
		h_Purity_MT      [tr] = new TH1F("h_Purity_MT"       +TrigNames[tr], title,  10,     0.,   100.);  h_Purity_MT      [tr]->Sumw2();
	}
}


//____________________________________________________________________________
void Fakerates::writeHistos(TFile* pFile){
	/* 
	write histograms in output files
	parameters: pFile (output file)
	return: none
	*/

	pFile->cd(); 
	TDirectory* sdir = Util::FindOrCreate(fName, pFile);
	sdir->cd();

	h_FRatio               ->Write(fName + "_" + h_FRatio               ->GetName(), TObject::kWriteDelete);

	// loose histograms
	h_FLoose               ->Write(fName + "_" + h_FLoose               ->GetName(), TObject::kWriteDelete);
	h_FLoose_CERN_small    ->Write(fName + "_" + h_FLoose_CERN_small    ->GetName(), TObject::kWriteDelete);
	h_FLoose_CERN_large    ->Write(fName + "_" + h_FLoose_CERN_large    ->GetName(), TObject::kWriteDelete);

	h_FLoose_0             ->Write(fName + "_" + h_FLoose_0             ->GetName(), TObject::kWriteDelete);
	h_FLoose_1             ->Write(fName + "_" + h_FLoose_1             ->GetName(), TObject::kWriteDelete);
	h_FLoose_2             ->Write(fName + "_" + h_FLoose_2             ->GetName(), TObject::kWriteDelete);
	h_FLoose_3             ->Write(fName + "_" + h_FLoose_3             ->GetName(), TObject::kWriteDelete);
	h_FLoose_4             ->Write(fName + "_" + h_FLoose_4             ->GetName(), TObject::kWriteDelete);
	h_FLoose_5             ->Write(fName + "_" + h_FLoose_5             ->GetName(), TObject::kWriteDelete);

	h_Loose_LepIso_0       ->Write(fName + "_" + h_Loose_LepIso_0       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso_1       ->Write(fName + "_" + h_Loose_LepIso_1       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso_2       ->Write(fName + "_" + h_Loose_LepIso_2       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso_3       ->Write(fName + "_" + h_Loose_LepIso_3       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso_4       ->Write(fName + "_" + h_Loose_LepIso_4       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso_5       ->Write(fName + "_" + h_Loose_LepIso_5       ->GetName(), TObject::kWriteDelete);

	h_Loose_ClosJetPt_0    ->Write(fName + "_" + h_Loose_ClosJetPt_0    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt_1    ->Write(fName + "_" + h_Loose_ClosJetPt_1    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt_2    ->Write(fName + "_" + h_Loose_ClosJetPt_2    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt_3    ->Write(fName + "_" + h_Loose_ClosJetPt_3    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt_4    ->Write(fName + "_" + h_Loose_ClosJetPt_4    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt_5    ->Write(fName + "_" + h_Loose_ClosJetPt_5    ->GetName(), TObject::kWriteDelete);

	h_Loose_ClosJetPtLNT_0    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_0    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPtLNT_1    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_1    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPtLNT_2    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_2    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPtLNT_3    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_3    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPtLNT_4    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_4    ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPtLNT_5    ->Write(fName + "_" + h_Loose_ClosJetPtLNT_5    ->GetName(), TObject::kWriteDelete);

	h_Loose_Provenance     ->Write(fName + "_" + h_Loose_Provenance     ->GetName(), TObject::kWriteDelete);
	h_Loose_ProvenanceLNT  ->Write(fName + "_" + h_Loose_ProvenanceLNT  ->GetName(), TObject::kWriteDelete);
	h_Loose_ProvenanceAES  ->Write(fName + "_" + h_Loose_ProvenanceAES  ->GetName(), TObject::kWriteDelete);
 
	h_Loose_LepPt          ->Write(fName + "_" + h_Loose_LepPt          ->GetName(), TObject::kWriteDelete);
	h_Loose_LepEta         ->Write(fName + "_" + h_Loose_LepEta         ->GetName(), TObject::kWriteDelete);
	h_Loose_LepIso         ->Write(fName + "_" + h_Loose_LepIso         ->GetName(), TObject::kWriteDelete);
	h_Loose_D0             ->Write(fName + "_" + h_Loose_D0             ->GetName(), TObject::kWriteDelete);

	h_Loose_LepEta_30      ->Write(fName + "_" + h_Loose_LepEta_30      ->GetName(), TObject::kWriteDelete);
	h_Loose_LepEta_40      ->Write(fName + "_" + h_Loose_LepEta_40      ->GetName(), TObject::kWriteDelete);
	h_Loose_LepEta_50      ->Write(fName + "_" + h_Loose_LepEta_50      ->GetName(), TObject::kWriteDelete);
	h_Loose_LepEta_60      ->Write(fName + "_" + h_Loose_LepEta_60      ->GetName(), TObject::kWriteDelete);

	h_Loose_LepPt_30       ->Write(fName + "_" + h_Loose_LepPt_30       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepPt_40       ->Write(fName + "_" + h_Loose_LepPt_40       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepPt_50       ->Write(fName + "_" + h_Loose_LepPt_50       ->GetName(), TObject::kWriteDelete);
	h_Loose_LepPt_60       ->Write(fName + "_" + h_Loose_LepPt_60       ->GetName(), TObject::kWriteDelete);

	h_Loose_HT             ->Write(fName + "_" + h_Loose_HT             ->GetName(), TObject::kWriteDelete);
	h_Loose_MET            ->Write(fName + "_" + h_Loose_MET            ->GetName(), TObject::kWriteDelete);
	h_Loose_METnoMTCut     ->Write(fName + "_" + h_Loose_METnoMTCut     ->GetName(), TObject::kWriteDelete);
	h_Loose_MT             ->Write(fName + "_" + h_Loose_MT             ->GetName(), TObject::kWriteDelete);
	h_Loose_MTMET20        ->Write(fName + "_" + h_Loose_MTMET20        ->GetName(), TObject::kWriteDelete);
	h_Loose_MTMET30        ->Write(fName + "_" + h_Loose_MTMET30        ->GetName(), TObject::kWriteDelete);

	h_Loose_MaxJPt         ->Write(fName + "_" + h_Loose_MaxJPt         ->GetName(), TObject::kWriteDelete);
	h_Loose_MaxJCPt        ->Write(fName + "_" + h_Loose_MaxJCPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_MaxJRPt        ->Write(fName + "_" + h_Loose_MaxJRPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_MaxJCSV        ->Write(fName + "_" + h_Loose_MaxJCSV        ->GetName(), TObject::kWriteDelete);

	h_Loose_AllJCPt        ->Write(fName + "_" + h_Loose_AllJCPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_AllJRPt        ->Write(fName + "_" + h_Loose_AllJRPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_AllJEta        ->Write(fName + "_" + h_Loose_AllJEta        ->GetName(), TObject::kWriteDelete);
	h_Loose_AllJCSV        ->Write(fName + "_" + h_Loose_AllJCSV        ->GetName(), TObject::kWriteDelete);

	//h_Loose_AllJEtatest1  ->Write(fName + "_" + h_Loose_AllJEtatest1    ->GetName(), TObject::kWriteDelete);
	//h_Loose_AllJEtatest2  ->Write(fName + "_" + h_Loose_AllJEtatest2    ->GetName(), TObject::kWriteDelete);
	//h_Loose_AllJEtatest3  ->Write(fName + "_" + h_Loose_AllJEtatest3    ->GetName(), TObject::kWriteDelete);

	h_Loose_NBJets         ->Write(fName + "_" + h_Loose_NBJets         ->GetName(), TObject::kWriteDelete);
	h_Loose_NJets          ->Write(fName + "_" + h_Loose_NJets          ->GetName(), TObject::kWriteDelete);
	h_Loose_NVertices      ->Write(fName + "_" + h_Loose_NVertices      ->GetName(), TObject::kWriteDelete);
	h_Loose_NVertices1     ->Write(fName + "_" + h_Loose_NVertices1     ->GetName(), TObject::kWriteDelete);
	h_Loose_NVerticesMET20 ->Write(fName + "_" + h_Loose_NVerticesMET20 ->GetName(), TObject::kWriteDelete);

	h_Loose_AwayJetDR      ->Write(fName + "_" + h_Loose_AwayJetDR      ->GetName(), TObject::kWriteDelete);
	h_Loose_AwayJetPt      ->Write(fName + "_" + h_Loose_AwayJetPt      ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetDR      ->Write(fName + "_" + h_Loose_ClosJetDR      ->GetName(), TObject::kWriteDelete);
	h_Loose_ClosJetPt      ->Write(fName + "_" + h_Loose_ClosJetPt      ->GetName(), TObject::kWriteDelete);

	h_Loose_JCPtJEta       ->Write(fName + "_" + h_Loose_JCPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Loose_JRPtJEta       ->Write(fName + "_" + h_Loose_JRPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Loose_JCPtJPt        ->Write(fName + "_" + h_Loose_JCPtJPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_JRPtJPt        ->Write(fName + "_" + h_Loose_JRPtJPt        ->GetName(), TObject::kWriteDelete);

	h_Loose_DJPtJEta       ->Write(fName + "_" + h_Loose_DJPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Loose_FJPtJEta       ->Write(fName + "_" + h_Loose_FJPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Loose_DJPtJPt        ->Write(fName + "_" + h_Loose_DJPtJPt        ->GetName(), TObject::kWriteDelete);
	h_Loose_FJPtJPt        ->Write(fName + "_" + h_Loose_FJPtJPt        ->GetName(), TObject::kWriteDelete);

	for(int n = 0; n < (fDFn_binseta-1)*(fDFn_binspt-1); ++n) {
		h_Loose_DJPtZoomC[n] ->Write(fName + "_" + h_Loose_DJPtZoomC[n] ->GetName(), TObject::kWriteDelete);
		h_Loose_FJPtZoomC[n] ->Write(fName + "_" + h_Loose_FJPtZoomC[n] ->GetName(), TObject::kWriteDelete);
		h_Loose_DJPtZoomR[n] ->Write(fName + "_" + h_Loose_DJPtZoomR[n] ->GetName(), TObject::kWriteDelete);
		h_Loose_FJPtZoomR[n] ->Write(fName + "_" + h_Loose_FJPtZoomR[n] ->GetName(), TObject::kWriteDelete);
	}
	for(int n = 0; n < (fFRMETn_binseta-1)*(fFRMETn_binspt-1); ++n) {
		h_Loose_METZoom[n]   ->Write(fName + "_" + h_Loose_METZoom[n]   ->GetName(), TObject::kWriteDelete);
	}


	// tight histograms
	h_FTight               ->Write(fName + "_" + h_FTight               ->GetName(), TObject::kWriteDelete);
	h_FTight_CERN_small    ->Write(fName + "_" + h_FTight_CERN_small    ->GetName(), TObject::kWriteDelete);
	h_FTight_CERN_large    ->Write(fName + "_" + h_FTight_CERN_large    ->GetName(), TObject::kWriteDelete);

	h_FTight_0             ->Write(fName + "_" + h_FTight_0             ->GetName(), TObject::kWriteDelete);
	h_FTight_1             ->Write(fName + "_" + h_FTight_1             ->GetName(), TObject::kWriteDelete);
	h_FTight_2             ->Write(fName + "_" + h_FTight_2             ->GetName(), TObject::kWriteDelete);
	h_FTight_3             ->Write(fName + "_" + h_FTight_3             ->GetName(), TObject::kWriteDelete);
	h_FTight_4             ->Write(fName + "_" + h_FTight_4             ->GetName(), TObject::kWriteDelete);
	h_FTight_5             ->Write(fName + "_" + h_FTight_5             ->GetName(), TObject::kWriteDelete);

	h_Tight_LepIso_0       ->Write(fName + "_" + h_Tight_LepIso_0       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso_1       ->Write(fName + "_" + h_Tight_LepIso_1       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso_2       ->Write(fName + "_" + h_Tight_LepIso_2       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso_3       ->Write(fName + "_" + h_Tight_LepIso_3       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso_4       ->Write(fName + "_" + h_Tight_LepIso_4       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso_5       ->Write(fName + "_" + h_Tight_LepIso_5       ->GetName(), TObject::kWriteDelete);

	h_Tight_ClosJetPt_0    ->Write(fName + "_" + h_Tight_ClosJetPt_0    ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt_1    ->Write(fName + "_" + h_Tight_ClosJetPt_1    ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt_2    ->Write(fName + "_" + h_Tight_ClosJetPt_2    ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt_3    ->Write(fName + "_" + h_Tight_ClosJetPt_3    ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt_4    ->Write(fName + "_" + h_Tight_ClosJetPt_4    ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt_5    ->Write(fName + "_" + h_Tight_ClosJetPt_5    ->GetName(), TObject::kWriteDelete);

	h_Tight_Provenance     ->Write(fName + "_" + h_Tight_Provenance     ->GetName(), TObject::kWriteDelete);
	h_Tight_ProvenanceAES  ->Write(fName + "_" + h_Tight_ProvenanceAES  ->GetName(), TObject::kWriteDelete);
	
	h_Tight_LepPt          ->Write(fName + "_" + h_Tight_LepPt          ->GetName(), TObject::kWriteDelete);
	h_Tight_LepEta         ->Write(fName + "_" + h_Tight_LepEta         ->GetName(), TObject::kWriteDelete);
	h_Tight_LepIso         ->Write(fName + "_" + h_Tight_LepIso         ->GetName(), TObject::kWriteDelete);
	h_Tight_D0             ->Write(fName + "_" + h_Tight_D0             ->GetName(), TObject::kWriteDelete);

	h_Tight_LepEta_30      ->Write(fName + "_" + h_Tight_LepEta_30      ->GetName(), TObject::kWriteDelete);
	h_Tight_LepEta_40      ->Write(fName + "_" + h_Tight_LepEta_40      ->GetName(), TObject::kWriteDelete);
	h_Tight_LepEta_50      ->Write(fName + "_" + h_Tight_LepEta_50      ->GetName(), TObject::kWriteDelete);
	h_Tight_LepEta_60      ->Write(fName + "_" + h_Tight_LepEta_60      ->GetName(), TObject::kWriteDelete);

	h_Tight_LepPt_30       ->Write(fName + "_" + h_Tight_LepPt_30       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepPt_40       ->Write(fName + "_" + h_Tight_LepPt_40       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepPt_50       ->Write(fName + "_" + h_Tight_LepPt_50       ->GetName(), TObject::kWriteDelete);
	h_Tight_LepPt_60       ->Write(fName + "_" + h_Tight_LepPt_60       ->GetName(), TObject::kWriteDelete);

	h_Tight_HT             ->Write(fName + "_" + h_Tight_HT             ->GetName(), TObject::kWriteDelete);
	h_Tight_MET            ->Write(fName + "_" + h_Tight_MET            ->GetName(), TObject::kWriteDelete);
	h_Tight_METnoMTCut     ->Write(fName + "_" + h_Tight_METnoMTCut     ->GetName(), TObject::kWriteDelete);
	h_Tight_MT             ->Write(fName + "_" + h_Tight_MT             ->GetName(), TObject::kWriteDelete);
	h_Tight_MTMET20        ->Write(fName + "_" + h_Tight_MTMET20        ->GetName(), TObject::kWriteDelete);
	h_Tight_MTMET30        ->Write(fName + "_" + h_Tight_MTMET30        ->GetName(), TObject::kWriteDelete);

	h_Tight_MaxJPt         ->Write(fName + "_" + h_Tight_MaxJPt         ->GetName(), TObject::kWriteDelete);
	h_Tight_MaxJCPt        ->Write(fName + "_" + h_Tight_MaxJCPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_MaxJRPt        ->Write(fName + "_" + h_Tight_MaxJRPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_MaxJCSV        ->Write(fName + "_" + h_Tight_MaxJCSV        ->GetName(), TObject::kWriteDelete);

	h_Tight_AllJCPt        ->Write(fName + "_" + h_Tight_AllJCPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_AllJRPt        ->Write(fName + "_" + h_Tight_AllJRPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_AllJEta        ->Write(fName + "_" + h_Tight_AllJEta        ->GetName(), TObject::kWriteDelete);
	h_Tight_AllJCSV        ->Write(fName + "_" + h_Tight_AllJCSV        ->GetName(), TObject::kWriteDelete);

	h_Tight_NBJets         ->Write(fName + "_" + h_Tight_NBJets         ->GetName(), TObject::kWriteDelete);
	h_Tight_NJets          ->Write(fName + "_" + h_Tight_NJets          ->GetName(), TObject::kWriteDelete);
	h_Tight_NVertices      ->Write(fName + "_" + h_Tight_NVertices      ->GetName(), TObject::kWriteDelete);
	h_Tight_NVertices1     ->Write(fName + "_" + h_Tight_NVertices1     ->GetName(), TObject::kWriteDelete);
	h_Tight_NVerticesMET20 ->Write(fName + "_" + h_Tight_NVerticesMET20 ->GetName(), TObject::kWriteDelete);

	h_Tight_AwayJetDR      ->Write(fName + "_" + h_Tight_AwayJetDR      ->GetName(), TObject::kWriteDelete);
	h_Tight_AwayJetPt      ->Write(fName + "_" + h_Tight_AwayJetPt      ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetDR      ->Write(fName + "_" + h_Tight_ClosJetDR      ->GetName(), TObject::kWriteDelete);
	h_Tight_ClosJetPt      ->Write(fName + "_" + h_Tight_ClosJetPt      ->GetName(), TObject::kWriteDelete);

	h_Tight_JCPtJEta       ->Write(fName + "_" + h_Tight_JCPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Tight_JRPtJEta       ->Write(fName + "_" + h_Tight_JRPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Tight_JCPtJPt        ->Write(fName + "_" + h_Tight_JCPtJPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_JRPtJPt        ->Write(fName + "_" + h_Tight_JRPtJPt        ->GetName(), TObject::kWriteDelete);

	h_Tight_DJPtJEta       ->Write(fName + "_" + h_Tight_DJPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Tight_FJPtJEta       ->Write(fName + "_" + h_Tight_FJPtJEta       ->GetName(), TObject::kWriteDelete);
	h_Tight_DJPtJPt        ->Write(fName + "_" + h_Tight_DJPtJPt        ->GetName(), TObject::kWriteDelete);
	h_Tight_FJPtJPt        ->Write(fName + "_" + h_Tight_FJPtJPt        ->GetName(), TObject::kWriteDelete);

	for(int n = 0; n < (fDFn_binseta-1)*(fDFn_binspt-1); ++n) {
		h_Tight_DJPtZoomC[n] ->Write(fName + "_" + h_Tight_DJPtZoomC[n] ->GetName(), TObject::kWriteDelete);
		h_Tight_FJPtZoomC[n] ->Write(fName + "_" + h_Tight_FJPtZoomC[n] ->GetName(), TObject::kWriteDelete);
		h_Tight_DJPtZoomR[n] ->Write(fName + "_" + h_Tight_DJPtZoomR[n] ->GetName(), TObject::kWriteDelete);
		h_Tight_FJPtZoomR[n] ->Write(fName + "_" + h_Tight_FJPtZoomR[n] ->GetName(), TObject::kWriteDelete);
	}
	for(int n = 0; n < (fFRMETn_binseta-1)*(fFRMETn_binspt-1); ++n) {
		h_Tight_METZoom[n]   ->Write(fName + "_" + h_Tight_METZoom[n]   ->GetName(), TObject::kWriteDelete);
	}


	// TRIGGER...
	for (size_t tr=0; tr<iNTRIGS; tr++){

		h_FLoose_trig[tr]      ->Write(fName + "_" + h_FLoose_trig       [tr]->GetName(), TObject::kWriteDelete);
		h_FTight_trig[tr]      ->Write(fName + "_" + h_FTight_trig       [tr]->GetName(), TObject::kWriteDelete);
		h_Loose_LepPt_trig[tr] ->Write(fName + "_" + h_Loose_LepPt_trig  [tr]->GetName(), TObject::kWriteDelete);
		h_Tight_LepPt_trig[tr] ->Write(fName + "_" + h_Tight_LepPt_trig  [tr]->GetName(), TObject::kWriteDelete);
		h_Loose_LepEta_trig[tr]->Write(fName + "_" + h_Loose_LepEta_trig [tr]->GetName(), TObject::kWriteDelete);
		h_Tight_LepEta_trig[tr]->Write(fName + "_" + h_Tight_LepEta_trig [tr]->GetName(), TObject::kWriteDelete);
		
		h_Purity         [tr]  ->Write(fName + "_" + h_Purity            [tr]->GetName(), TObject::kWriteDelete);
		h_Purity_LepPt   [tr]  ->Write(fName + "_" + h_Purity_LepPt      [tr]->GetName(), TObject::kWriteDelete); 
		h_Purity_JetPt   [tr]  ->Write(fName + "_" + h_Purity_JetPt      [tr]->GetName(), TObject::kWriteDelete);
		h_Purity_JetRawPt[tr]  ->Write(fName + "_" + h_Purity_JetRawPt   [tr]->GetName(), TObject::kWriteDelete);
		h_Purity_DRLepJet[tr]  ->Write(fName + "_" + h_Purity_DRLepJet   [tr]->GetName(), TObject::kWriteDelete);
		h_Purity_MET     [tr]  ->Write(fName + "_" + h_Purity_MET        [tr]->GetName(), TObject::kWriteDelete);
		h_Purity_MT      [tr]  ->Write(fName + "_" + h_Purity_MT         [tr]->GetName(), TObject::kWriteDelete);
	}
}


//____________________________________________________________________________
bool Fakerates::PassesHLT(int hlt){

	if (hlt == iHLTMU5 ) return HLT_MU5;
	if (hlt == iHLTMU8 ) return HLT_MU8;
	if (hlt == iHLTMU12) return HLT_MU12;
	if (hlt == iHLTMU17) return HLT_MU17;
	if (hlt == iHLTMU24) return HLT_MU24;
	if (hlt == iHLTMU40) return HLT_MU40;
	
	return false;
}


//____________________________________________________________________________
void Fakerates::fillPurities(int trig, float bin, float fEventweight){
	/////////////////////////////////////////////////////////////////////////
	// For each trigger fill the corresponding histogram with the value bin
	
	// MEANING: 
	//  0 - # of events selected by the trigger
	//  1 - # of events with one lepton
	//  2 - # of events with one lepton with pT 
	//  3 - # of events with one lepton GlbMuon
	//  4 - # of events with one lepton IsPFMuon
	//  5 - # of events with one lepton passing Chi2
	//  6 - # of events with one lepton passing GlMuHits
	//  7 - # of events with one lepton passing MatchedStat
	//  8 - # of events with one lepton passing Dz
	//  9 - # of events with one lepton passing D0
	// 10 - # of events with one lepton passing NPxHits
	// 11 - # of events with one lepton passing NSiLayers
	// 12 - # of events with one loose lepton +ISO 
	// 13 - # of events with one and only one lepton
	// 14 - # of events with one jet
	// 15 - # of events with one good jet with pT > 20 GeV
	// 16 - # of events with one good away jet with pT > 20 GeV
	// 17 - # of events with MET < 20 GeV 
	// 18 - # of events with MT  < 20 GeV
	
	// 19 - # of events with one good jet with pT > 30 GeV
	// 20 - # of events with one good away jet with pT > 30 GeV
	// 21 - # of events with MET < 20 GeV 
	// 22 - # of events with MT  < 20 GeV
	
	// 23 - # of events with one good jet with pT > 40 GeV
	// 24 - # of events with one good away jet with pT > 40 GeV
	// 25 - # of events with MET < 20 GeV 
	// 26 - # of events with MT  < 20 GeV
	
	h_Purity[trig]->Fill(bin, fEventweight);

}


//____________________________________________________________________________
void Fakerates::fill2DWithoutOF(TH2F *&ihist, float x, float y, float w){
  
	float xmax = ihist->GetXaxis()->GetBinLowEdge(ihist->GetNbinsX());
	// float xmax = ihist->GetBinLowEdge(ihist->GetMaximumBin());
	float bw = ihist->GetXaxis()->GetBinWidth(ihist->GetMaximumBin());
	if(x > xmax) ihist->Fill(xmax + bw*0.5, y , w); // always increment last bin (i.e. never the overflow)
	else ihist->Fill(x, y, w);
}


//____________________________________________________________________________
void Fakerates::printProgress(Long64_t entry, Long64_t nentries, TString header){

	Long64_t step = nentries/20;
	if( step < 200 )   step = 200;
	if( step > 10000 ) step = 10000;
	
	if(entry%step != 0 && (entry+1 != nentries) ) return;
	
	float progress_f = (float)(entry+1)/(float)(nentries)*100.;
	char progress[10];
	sprintf(progress, "%5.1f", progress_f);
	cout << " Processing " << setw(50) << left << header << setw(6) << right << progress << " %      \n" << flush;
	if(entry+1 == nentries) cout << endl;
}




