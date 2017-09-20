#ifndef EVENT_SELECTION_H
#define EVENT_SELECTION_H

#include "constants.h"
#include "hid.h"
#include "TVector3.h"
#include <TLorentzVector.h>
#include "physics.h"

//Determine if multiple ids assigned to a single particle
//These are the only particles I'm IDing so if it is something else it comes in as zero
bool clean_id ( bool proton, bool pi_plus)
{
	bool clean = false;
	if((int)proton +(int)pi_plus <= 1 )
	{
		clean = true;
	}
	return clean;
}

/*
//Determine if kinematically clean
//Only need to do when all particles are present 
//A momentum correction is all the more necessary after these
bool clean_kin 
*/

//Give proper particle ID number to the particle id varaible array you made
int give_id( bool electron, bool proton, bool pi_plus, bool pi_minus)
{
	//Check that the id is clean
	int id = 0;
	bool is_clean = clean_id(proton, pi_plus);
	if( is_clean == true)
	{
		if( electron)
		{
			id = ELECTRON;
		}
		if( proton)
		{
			id = PROTON;
		}
		if( pi_plus)
		{
			id = PION;
		}
		if( pi_minus )
		{
			id = -PION;
		}
	}
	return id;
}

//Determine if there were only clean id's in an event
//Not sure how this is useful, probably won't use. 
bool clean_event (Int_t gpart, int real_id[24])
{
	bool clean_event = false;
	int mult = 1;
	for( int a=0;a<gpart;a++)
	{
		mult = mult * real_id[a];
	}
	if( mult != 0)
	{
		clean_event = true;
	}
	return clean_event;
}



//Missing Mass



//The Cuts
bool MM_p(double p1, double p2, double p3, double cx1, double cx2, double cx3, double cy1, double cy2, double cy3, double cz1, double cz2, double cz3, double m1, double m2, double m3){
	bool pass = false;
	TLorentzVector k1_mu = Make_4Vector(p1,cx1,cy1,cy1,m1);//phyiscs.h
	TLorentzVector k2_mu = Make_4Vector(p2,cx2,cy2,cz2,m2);
	TLorentzVector k3_mu = Make_4Vector(p3,cx3,cy3,cz3,m3);
	//double MM = (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu).Mag2();
	double MM = MM_3(k1_mu,k2_mu,k3_mu);
	double upper = p_center + p_sig;
	double lower = p_center - p_sig;
	if(MM < upper && MM > lower){
		pass = true;
	}
	return pass;
}


bool MM_pi(double p1, double p2, double p3, double cx1, double cx2, double cx3, double cy1, double cy2, double cy3, double cz1, double cz2, double cz3, double m1, double m2, double m3){
	bool pass = false;
	TLorentzVector k1_mu = Make_4Vector(p1,cx1,cy1,cy1,m1);//physics.h
	TLorentzVector k2_mu = Make_4Vector(p2,cx2,cy2,cz2,m2);//physics.h
	TLorentzVector k3_mu = Make_4Vector(p3,cx3,cy3,cz3,m3);//physics.h

	//double MM = (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu).Mag2();
	double MM = MM_3(k1_mu,k2_mu,k3_mu);
	double upper = pip_center + pip_sig;
	double lower = pip_center - pip_sig;
	if(MM > lower && MM < upper){
		pass = true;
	}
	return pass;
}

bool MM_zero(double p1, double p2, double p3, double p4, double cx1, double cx2, double cx3, double cx4, double cy1, double cy2, double cy3, double cy4, double cz1, double cz2, double cz3, double cz4, double m1, double m2, double m3, double m4){
	bool pass = false;
	TLorentzVector k1_mu = Make_4Vector(p1,cx1,cy1,cy1,m1);//physics.h
	TLorentzVector k2_mu = Make_4Vector(p2,cx2,cy2,cz2,m2);//physics.h
	TLorentzVector k3_mu = Make_4Vector(p3,cx3,cy3,cz3,m3);//physics.h
	TLorentzVector k4_mu = Make_4Vector(p4,cx4,cy4,cz4,m4);//physics.h
	//double MM = (k_mu_e16 + p_mu - k1_mu - k2_mu - k3_mu).Mag2();
	double MM = MM_4(k1_mu,k2_mu,k3_mu,k4_mu);
	double upper = MM_zero_center + MM_zero_sigma;
	double lower = MM_zero_center - MM_zero_sigma;
	if(MM > lower && MM < upper){
		pass = true;
	}
	return pass;
}

bool MM_p2(double MM){
	bool pass = false;
	double upper = p_center + p_sig;
	double lower = p_center - p_sig;
	if((MM < upper) && (MM > lower)){
		pass = true;
	}
	return pass;
}

bool MM_pi2(double MM){
	bool pass = false;
	double upper = pip_center + pip_sig;
	double lower = pip_center - pip_sig;
	if((MM < upper) && (MM > lower)){
		pass = true;
	}
	return pass;
}

bool MM_all2(double MM){
	bool pass = false;
	double upper = MM_zero_center + MM_zero_sigma;
	double lower = MM_zero_center - MM_zero_sigma;
	if((MM < upper) && (MM > lower)){
		pass = true;
	}
	return pass;
}

/*
1) Identify particles
2) Choose Topology
3) Pi-Missing mass
3.1
*/

//particle 1 should be the lead electron
//Determine if the other particles are all identified
bool other_pim_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	bool P_2 = false;
	bool P_3 = false;
	bool P_4 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4);
	P_1 = is_proton( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_2 = is_pip( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	P_3 = is_pip( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_4 = is_proton( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	if(P_0 && P_1 && P_2){
		/*if(idx_1 != idx_2){ //Makes sure we aren't looking at the same particle
			if(P_1 && !P_3){//Make sure proton doesn't also pass as a pi+
				if(P_2 && !P_4){ //Make sure pi+ doesn't also pass as a proton
					s++;
				}
			}
		}
	}
	if(s == 1){//To make sure the event is unique*/ //Check to see if this cross check is taking out too many guys
		pass = true;
	}
	return pass;
}

//The Cut on the missing mass 
bool pim_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	if(other_pim_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0, q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_pi(p0,p1,p2,cx0,cx1,cx2,cy0,cy1,cy2,cz0,cz1,cz2,me,mp,mpi)){
			pass = true;
		}
	}
	return pass;
}

bool pim_miss_2(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2, double mm){
	bool pass = false;
	if(other_pim_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_pi2(mm)){
			pass = true;
		}
	}
	return pass;
}


bool other_p_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	bool P_2 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4);
	P_1 = is_pip( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_2 = is_pim( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	if(P_0 && P_1 && P_2){
		if(idx_1 != idx_2){ //Makes sure we aren't looking at the same particle
					s++;
		}
	}
	if(s == 1){//To make sure the event is unique
		pass = true;
	}
	return pass;
}

bool p_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	if(other_p_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_p(p0,p1,p2,cx0,cx1,cx2,cy0,cy1,cy2,cz0,cz1,cz2,me,mpi,mpi)){
			pass = true;
		}
	}
	return pass;
}

bool p_miss_2(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2, double mm){
	bool pass = false;
	if(other_p_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_p2(mm)){
			pass = true;
		}
	}
	return pass;
}


bool other_pip_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	bool P_2 = false;
	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4); //eid.h
	P_1 = is_proton( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);	//hid.h
	P_2 = is_pim( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);	//hid.h
	if(P_0 && P_1 && P_2){
		pass = true;
	}
	return pass;
}

bool pip_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2){
	bool pass = false;
	if(other_pip_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_pi(p0,p1,p2,cx0,cx1,cx2,cy0,cy1,cy2,cz0,cz1,cz2,me,mp,mpi)){
			pass = true;
		}
	}
	return pass;
}

bool pip_miss_2(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int idx_1, int idx_2, double mm){
	bool pass = false;
	if(other_pip_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2)){
		if(MM_pi2(mm)){
			pass = true;
		}
	}
	return pass;
}

bool other_zero_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2,  int q3, double p3, double cx3, double cy3, double cz3, int dc3, int sc3, int stat3, int dc_stat3, double sc_t3, double sc_r3, int idx_1, int idx_2, int idx_3){
	bool pass = false;
	int s = 0;
	bool P_0 = false;
	bool P_1 = false;
	bool P_2 = false;
	bool P_3 = false;
 	P_0 = eid(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, 4);
	P_1 = is_proton( q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1, p0, sc_r0, sc_t0);
	P_2 = is_pip( q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, p0, sc_r0, sc_t0);
	P_3 = is_pim( q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, p0, sc_r0, sc_t0);
	if(P_0 && P_1 && P_2){
		if(idx_1 != idx_2 && idx_1 != idx_3 && idx_3 != idx_2){ //Makes sure we aren't looking at the same particle
					s++;
		}
	}
	if(s == 1){//To make sure the event is unique
		pass = true;
	}
	return pass;
}

bool zero_miss(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2, int q3, double p3, double cx3, double cy3, double cz3, int dc3, int sc3, int stat3, int dc_stat3, double sc_t3, double sc_r3 ,int idx_1, int idx_2, int idx_3){
	bool pass = false;
	if(other_zero_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2,  q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, idx_1, idx_2, idx_3)){
		if(MM_zero(p0,p1,p2,p3,cx0,cx1,cx2,cx3,cy0,cy1,cy2,cy3,cz0,cz1,cz2,cz3,me,mp,mpi,mpi)){
			pass = true;
		}
	}
	return pass;
}

//To see if an event satisfies any of the four topologies
bool top_cross ( bool all_present, bool pi_mi_miss, bool pi_p_miss, bool proton_miss)
{
	bool cross = false;
	if( ((int)all_present + (int)pi_mi_miss +(int)pi_p_miss +(int)proton_miss)>=1)
	{
		cross = true;
	}
	return cross;
}

//Remember
/*
Particle 0 ->Electron
Particle 1 -> Proton
Particle 2 -> Pip
Particle 3 -> Pim
The indexes on the subsequent missing mass ids need to match that
*/
bool total_event(double p0, int q0, double cx0, double cy0, double cz0, double vx0, double vy0, double vz0, int dc0, int cc0, int ec0, int sc0, int dc_stat0, double etot0, int stat0, double sc_r0, double sc_t0,  int q1, double p1, double cx1, double cy1, double cz1, int dc1, int sc1, int stat1, int dc_stat1, double sc_t1, double sc_r1,  int q2, double p2, double cx2, double cy2, double cz2, int dc2, int sc2, int stat2, int dc_stat2, double sc_t2, double sc_r2,  int q3, double p3, double cx3, double cy3, double cz3, int dc3, int sc3, int stat3, int dc_stat3, double sc_t3, double sc_r3, int idx_1, int idx_2, int idx_3){
	bool zero = false;
	bool proton = false;
	bool pip =false;
	bool pim = false;
	zero = zero_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2,  q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, idx_1, idx_2, idx_3);
					
					//p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0, q1, p1, cx1, cy1, cz1, dc1,  sc1,  stat1,  dc_stat1,  sc_t1,  sc_r1,  q2,  p2,  cx2,  cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2,sc_r2, idx_1, idx_2
	proton = p_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2,  q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, idx_2, idx_3);
	pip = pip_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q3, p3, cx3, cy3, cz3, dc3, sc3, stat3, dc_stat3, sc_t3, sc_r3, idx_1, idx_3);
	pim = pim_miss(p0, q0, cx0, cy0, cz0, vx0, vy0, vz0, dc0, cc0, ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0,  q1, p1, cx1, cy1, cz1, dc1, sc1, stat1, dc_stat1, sc_t1, sc_r1,  q2, p2, cx2, cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2, sc_r2, idx_1, idx_2);
	return top_cross( zero, pip, pim, proton);
}

//Actual event selection
//Will cross reference through diffrent topologies to make sure that events are not double, or triple counted
/*
Says whether or not the event fits within
- Taret Particles
- Kinematic Agreement
- no momentum corrections yet
*/

//p0, q0, cx0, cy0,  cz0,  vx0, vy0,  vz0,  dc0,  cc0,  ec0, sc0, dc_stat0, etot0, stat0, sc_r0, sc_t0, q1, p1, cx1, cy1, cz1, dc1,  sc1,  stat1,  dc_stat1,  sc_t1,  sc_r1,  q2,  p2,  cx2,  cy2, cz2, dc2, sc2, stat2, dc_stat2, sc_t2,sc_r2, idx_1, idx_2


//bool event_selection()

#endif /* EVENT_SELECTION_H */