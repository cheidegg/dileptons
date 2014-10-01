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

#ifndef CUSTOMTYPES_HH
#define CUSTOMTYPES_HH


#include <TString.h>


/*****************************************************************************
******************************************************************************
** TYPE REDEFINITION DEFINTIONS                                             **
******************************************************************************
*****************************************************************************/


typedef TString AKROSD;
typedef TString Label;


/*****************************************************************************
******************************************************************************
** ENUMERATES                                                              **
******************************************************************************
*****************************************************************************/

enum DileptonsRunOn {
	analysis,
	modules,
	sketches
};

enum DileptonsMode {
	normal,
	test
};

enum DileptonsVerbose {
	low = 0,
	medium = 1,
	high = 2
};

enum HistogramMode {
	unpublished,
	published
};

enum OutputType {
	histogram,
	list,
	text,
	tree
};

enum SampleType {
	data,
	mc
};



/*****************************************************************************
******************************************************************************
** STRUCTURES AND UNIONS                                                    **
******************************************************************************
*****************************************************************************/

typedef struct {
	float ch    ;
	float chiso ;
    float d0    ;
    float eta   ;
	float gmid  ;
	float id    ;
	float isl   ;
	float ist   ;
	float isv   ;
	float mid   ;
	float neiso ;
    float pfiso ;
    float phi   ;
	float phiso ;
    float pt    ;
} Electron;

typedef struct {
    float betastar     ;
	float btag         ;
    float e            ;
    float eta          ;
	float partonflavor ;
    float phi          ;
    float pt           ;
} Jet;

typedef struct {
	float ch    ;
	float chiso ;
    float d0    ;
    float eta   ;
	float gmid  ;
	float id    ;
	float isl   ;
	float ist   ;
	float isv   ;
	float mid   ;
	float neiso ;
    float pfiso ;
    float phi   ;
	float phiso ;
    float pt    ;
} Muon;

typedef struct {
	float pt    ;
} Photon;

typedef struct {
	float ch    ;
	float chiso ;
    float d0    ;
    float eta   ;
	float gmid  ;
	float id    ;
	float mid   ;
	float neiso ;
    float pfiso ;
    float phi   ;
	float phiso ;
    float pt    ;
} Tau;




#endif
