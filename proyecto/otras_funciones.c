#include<stdio.h>
#include<math.h>
#include<stdlib.h> 
#include "funciones.h"

float likelihood(float m0, float b0, int N, int x[], float y[], float o[]){ 
	float ymod[N], aux, sumatoria=0, lnpl;
	int j;
 
		for(j=0;j<N;j++){ //SE calcula el logaritmo de likelihood
			ymod[j]=m0*x[j]+b0;
			aux=(pow((y[j]-ymod[j]),2))-(pow(o[j],2));
			sumatoria+=aux;		
		}	
		lnpl=(-0.5)*sumatoria;

	return lnpl;
}


double num_gauss(double x, double y) {
	int aux2 = 0;
	double spare;

	if(aux2) {
		aux2 = 0;
		return x + y * spare;

	}

	aux2 = 1;
	double u, v, s;
	do {
		u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		s = u * u + v * v;
	}

	while( (s >= 1.0) || (s == 0.0) );
		s = sqrt(-2.0 * log(s) / s);
		spare = v * s;
		return x + y * u * s;
	
}
