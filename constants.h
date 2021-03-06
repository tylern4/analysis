#ifndef DELTA_T_CUTS_H
#define DELTA_T_CUTS_H

#include "TMath.h"

const double c_special = 29.9792458; //speed of light in cm/ns

//Beam energies in GeV
const double energy_e16 = 5.754;
//Check 4.794 GeV for e16
const double energy_e1f = 5.499;

//Masses of relevant particles
const	double me = 0.0005109989; //mass of electron in GeV
const	double mp = 0.93828;	//Mass of proton in GeV
const	double mpi = 0.1395;	//Mass of pion in GeV

//Particle ID Numbers
//anti particles are negative
const 	int PROTON = 2212;
const	int ELECTRON = 11;
const	int PION = 211;
const	int PION_0 = 111;

// Beam spot from Arjun's Fortran vertex_e1f.f
const double x_beam = 0.090;
const double y_beam = -0.345;

//These vertext cut constants are from Arjun's cuts.h in elast_lite
const Float_t VX_ZMAX = -22.25; //Empirically-determined target upstream edge z-position in cm, for E1F
const Float_t VX_ZMIN = -27.75; //Empirically-determined target downstream edge z-position in cm, for E1F
const Float_t VX_DZ = 1.6; //Vertex resolution in cm, for E1F

//Fiducial cut Parameters. electron's have an e and hadrons have an h
//These were gotten from Arjun's cut_fid_e1f.f
const double c1e = 12.0;
const double c2e = 18.5;
const double c3e = 0.25;
const double c4e = 15.0;
const double factor_e = 0.416667;
const double p_shift_e = 0.14;
const double a0xh[6] = {24.0,24.0,23.0,23.5,24.5,24.5};
const double a0mh[6] = {25.0,26.0,26.0,25.5,27.0,26.0};
const double a1xh[6] = {0.22,0.23,0.20,0.20,0.22,0.22};
const double a1mh[6] = {0.22,0.22,0.22,0.22,0.16,0.16};
const double a2xh[6] = {8.0,8.0,8.0,8.0,8.0,8.0};
const double a2mh[6] = {8.0,8.0,8.0,8.0,8.0,8.0};
const double a3xh[6] = {1.0,1.0,1.0,1.0,1.0,1.0};
const double a3mh[6] = {1.0,1.0,1.0,1.0,1.0,1.0};

//Missing Mass cut parameters
/*
//None determined yet (just place holders for now)
const double pim_center = 0.1395;
const double pim_sig = 0.02; 
const double pip_center = 0.1395;
const double pip_sig = 0.02;
const double p_center = 0.93828;
const double p_sig = 0.02;
*/
//Arjun's ranges for each Missing mass cut
//proton min: 0.652  max: 0.912
//pion min: 0.050  max: 0.270
//Convert to the formalism I'll use, but will adjust later
const double pim_center = 0.160;
const double pim_sig = 0.0366;
const double pip_center = 0.160;
const double pip_sig = 0.0366;
const double p_center = 0.782;
const double p_sig = 0.0433;

//Delta T cut parameters
/*
//Currently cannot find Arjun's so they are just guesses of flat numbers. Will adjust when I can 8/4/16
const double DT_PROTON_L = -0.6;
const double DT_PROTON_H = 0.6;
const double DT_PI_L = -0.6;
const double DT_PI_H = 0.6;
*/
//Arjun's cut parameters: 3rd order polynomial
const double DTL[4] = {-0.778903, 0.027350, 0.047947, -0.009641};
const double DTH[4] = {0.758057, -0.147383, 0.034343, -0.002367};


//Kinematic Cuts
// Margin of error allowed for kinematic fitting 
const double px_dev = 0.02;
const double py_dev = 0.02;
const double pz_dev = 0.02;

//Electron EC cut parameters
//currently from Arjun and not verified
//High and Low functions are third order polynomials separtated by sector
const Float_t p_min_e16 = 0.70; //in GeV
const Float_t ec_min_e16 = 0.06; //in GeV 
const double sf_high_e16[6][4] = {
		{0.380401, -0.019463, 0.004609, -0.000359},
		{0.428533, -0.047554, 0.016350, -0.001938},
		{0.420563, -0.064622, 0.025420, -0.003105},
		{0.411866, -0.062074, 0.022444, -0.002734},
		{0.383041, -0.020678, 0.007576, -0.000897},
		{0.394516, -0.023219, 0.010402, -0.001431}
		};
const double sf_low_e16[6][4] = {
		{0.141603, 0.063643, -0.012677, 0.000918},
		{0.149598, 0.053507, -0.007504, 0.000323},
		{0.172657, 0.038093, -0.002066, -0.000355},
		{0.149623, 0.060981, -0.012957, 0.001054},
		{0.099589, 0.102036, -0.028452, 0.002751},
		{0.117104, 0.097765, -0.023769, 0.002149}
		};
const Float_t p_min_e1f = 0.64;
const Float_t ec_min_e1f_exp[6] = {0.058,0.064,0.060,0.056,0.058,0.056}; 
const Float_t ec_min_e1f_sim[6] = {0.063,0.063,0.063,0.063,0.063,0.063}; 


#endif /* CONSTANTS_H */