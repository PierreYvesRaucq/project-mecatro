#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include "IO/ctrl_io.h"
typedef struct UserStruct{
	//speed controller
	double period;
	double Error_omega_l;
	double Error_omega_r;
	double windup;
	double Error_int_omega_l;
	double Error_int_omega_r;
    double wantedspeedl;
	double wantedspeedr;

	//cmd computation
	int cmdtype;
	double wanteddist; //objectif en distance
	double wantedangle; //objectif en angle

	//state informations
	int state;
	double posxyt[3];
	double stime;//time calculation for the position measurement (in number of clock)
} UserStruct;


typedef struct CtrlStruct{
	UserStruct *theUserStruct;  ///< user defined CtrlStruct
	CtrlIn *theCtrlIn;   ///< controller inputs
	CtrlOut *theCtrlOut; ///< controller outputs
} CtrlStruct;

int size_UserStruct();

CtrlStruct* init();

#endif // STRUCT_H_INCLUDED
