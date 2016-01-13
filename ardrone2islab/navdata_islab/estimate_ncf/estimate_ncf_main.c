#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <math.h>

#include "estimate_ncf.h"

int main(void){
	double omega[3] ={0.0619E-3,  -0.0078E-3,    0.6374E-3};
	double acc[3]= {-0.2303,    0.3004,    9.4569};
	double b_est[3]={-0.0101,   -0.0079,    0.0000};
	double q_est[4]={0.9996,    0.0167,    0.0134,    0.0197};
	double dt=0.05;
	double kp=0.1;
	
	estimate_ncf(q_est,b_est,omega,acc,kp,dt);

	printf("q_est:\t%f\t%f\t%f\t%f\n",q_est[0],q_est[1],q_est[2],q_est[3]);
	printf("q_ref:\t%f\t%f\t%f\t%f\n",0.9996,    0.0165,    0.0132,    0.0197);
	printf("\nb_est:\t%f\t%f\t%f\n",b_est[0],b_est[1],b_est[2]);
	printf("b_ref:\t%f\t%f\t%f\n",-0.0078,   -0.0065,    0.0000);
	return 0;
}
