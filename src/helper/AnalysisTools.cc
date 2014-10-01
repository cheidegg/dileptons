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


#include "src/helper/AnalysisTools.hh"




//____________________________________________________________________________
float AnalysisTools::Absolute(float value){
	/*
  	computes the absolute value of a variable
  	yeah, okay, it does NOT compute a thing and it seems pretty useless, but 
  	due to the fact that it IS a function, we can access it via the config file
  	parameters: value
  	return: absolute value
  	*/

	return TMath::Abs(value);

}


//____________________________________________________________________________
float AnalysisTools::AngleAddition(float angle1, float angle2){
	/*
	computes the addition between two angles taking the pi correction into account
	parameters: angle1, angle2
	return: the sum of the two
	*/

	float result = angle1 + angle2;
	while(result >   TMath::Pi()) result -= TMath::TwoPi();
	while(result <= -TMath::Pi()) result += TMath::TwoPi();

	return result;

}


//____________________________________________________________________________
float AnalysisTools::AngleSubtraction(float angle1, float angle2){
	/*
	computes the subtraction between two angles taking the pi correction into account
	parameters: angle1, angle2
	return: the difference between the two
	*/

	float result = angle1 - angle2;
	while(result >   TMath::Pi()) result -= TMath::TwoPi();
	while(result <= -TMath::Pi()) result += TMath::TwoPi();
	return result;

}


//____________________________________________________________________________
float AnalysisTools::DeltaPhi(float phi1, float phi2){
	/*
	computes delta Phi between two given azimuthal angles
	parameters: phi1, phi2
	return: delta Phi
	*/

	return TMath::Abs(AnalysisTools::AngleSubtraction(phi1, phi2));

}


//__________________________________________________________________________
float AnalysisTools::DeltaR(float eta1, float eta2, float phi1, float phi2){
	/* 
	computes delta R between two particles, whose pseudorapidity and azimuthal
	angles are given
	parameters: eta1, eta2, phi1, phi2
	return: delta R
	*/

	float deta = eta1 - eta2;
	float dphi = AnalysisTools::DeltaPhi(phi1, phi2);
	return sqrt( deta*deta + dphi*dphi );

}


//__________________________________________________________________________
float AnalysisTools::Maximum(std::vector<float> vector){
	/*
  	returns the maximum element of a vector of floats, if size larger than 0,
  	otherwise it returns 0.0
 	parameters: vector
 	return: maximum element
 	*/

	if(vector.size() == 0) return 0.;

	return *std::max_element(vector.begin(), vector.end());

}


//__________________________________________________________________________
float AnalysisTools::Minimum(std::vector<float> vector){
	/*
  	returns the minimum element of a vector of floats, if size larger than 0,
  	otherwise it returns 0.0
  	parameters: vector
  	return: minimum element
  	*/

	if(vector.size() == 0) return 0.;

	return *std::min_element(vector.begin(), vector.end());

}


//__________________________________________________________________________
float AnalysisTools::Sum(std::vector<float> summands){
	/*
	computes the sum over the elements in a vector
	parameters: summands
	return: sum
	*/

	float sum = 0.;
	for(int i = 0; i < summands.size(); ++i)
		sum += summands[i];

	return sum;

}


