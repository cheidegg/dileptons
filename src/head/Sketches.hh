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

#ifndef SKETCHES_HH
#define SKETCHES_HH

#include "src/head/AnalysisModules.hh"


class Sketches: public AnalysisModules {

public:


	// Member Functions

	Sketches(TString);
	virtual ~Sketches();
	virtual void Initialize();

	void CallSketchByID(int);
	void EndDileptons();
	void RunSketches();

	void Sketch101Frame();
	void Sketch101Kernel(float);



private:

	
};


#endif
