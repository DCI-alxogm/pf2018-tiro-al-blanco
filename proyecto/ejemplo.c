//Proyecto final de Programación Básica 2018
//Cadenas de Markov Chain Montecarlo (MCMC) con el método de Metropolis
//Participantes: Diana Hernández Bustos y Diana Rosales Rosales
//Este trabajo se comenzó el Miércoles 28 de Noviembre

#include<stdio.h>
#include<math.h>
#include<stdlib.h> 

float likelihood(float m0, float b0, int N, int x[], float y[], float o[]);
void calculo_monte(float* m0,float* b0,int N,  int x[], float y[], float o[], float sigmam, float sigmab);
double num_gauss(double mean, double stdDev);

int main(){

	int i,N=11,x[N];
	float y[N],o[N]; //DESVIAVCION ESTADAR ES o
	float m0=2.5, b0=0.3;
	
	float mn, L=1.0,bn, s, xg, yg, Pmn, Pbn, sigmam=0.6, sigmab=0.2; 
	FILE *fp; //Para abrir documento para leer archivos iniciales

	fp=fopen("datos.txt","r");

	//INTRODUCE LA M MAX Y M MIN
	for(i=0;i<N;i++){
		fscanf(fp,"%i %f %f",&x[i],&y[i],&o[i]);
	}
	fclose(fp);

//Generar dtaos random:

	
	//printf("%le \n", lnpl);
	//printf("%le \n", pl);
//Llamar la funcion de calculo

	calculo_monte(&m0,&b0, N, x, y, o, sigmam, sigmab);

//Dar valores de sigma

return 0;
}

void calculo_monte(float* m0,float* b0,int N,  int x[], float y[], float o[], float sigmam, float sigmab){

	float mn, bn, Pmn, mmin=0, mmax=5.0, bmin=0, bmax=5.0,num;
	int i;
	double lnpl, pl;
	FILE *fp2;
	
	fp2=fopen("Resultados.txt","w");	

	for(i=0; i<=100000; i++){
		lnpl= likelihood(*m0, *b0, N, x, y, o);
		//printf("prob de likelidhood: %f \n", lnpl);
		pl=exp(lnpl);
		mn = num_gauss(*m0, sigmam);
		bn = num_gauss(*b0, sigmab);
		
			if(mmin<mn<mmax && bmin<bn<bmax ){ 
				Pmn=likelihood(mn, bn, N, x, y, o); 
				//printf("prob de nueva m y b0= %f \n", Pmn);
					
					if(Pmn > lnpl){
					*m0=mn;
					//printf("m0=%f \n", m0);
					*b0=bn;
					//printf("b0=%f \n \n", b0);
					}

					else{
					num=rand()*(1.0/RAND_MAX);
					//printf("num=%f \n", num);
					
						if(num < exp(Pmn)){
							*m0=mn;
							//printf("m0=%f \n", m0);
							*b0=bn;
							//printf("bn=%f \n \n", b0);
						}
					}
			}

	fprintf(fp2, "%f \t %f \t %f \n",lnpl, *m0, *b0);
	
	}
	fclose(fp2);
	
}



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

double num_gauss(double mean, double stdDev) {
	int hasSpare = 0;
	double spare;

	if(hasSpare) {
		hasSpare = 0;
		return mean + stdDev * spare;

	}


	hasSpare = 1;
	double u, v, s;
	do {
		u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;

		v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;

		s = u * u + v * v;

	}

	while( (s >= 1.0) || (s == 0.0) );


	s = sqrt(-2.0 * log(s) / s);

	spare = v * s;

	return mean + stdDev * u * s;

}




