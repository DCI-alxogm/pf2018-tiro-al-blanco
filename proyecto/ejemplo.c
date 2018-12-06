//Proyecto final de Programación Básica 2018
//Cadenas de Markov Chain Montecarlo (MCMC) con el método de Metropolis
//Participantes: Diana Hernández Bustos y Diana Rosales Rosales
//Este trabajo se comenzó el Miércoles 28 de Noviembre

#include<stdio.h> //Incluyo las librerías que se van a utilizar en este programa
#include<math.h>
#include<stdlib.h> 

float likelihood(float m0, float b0, int N, int x[], float y[], float o[]);
void calculo_monte(float* m0,float* b0, int N,  int x[], float y[], float o[]);
double num_gauss(double x, double y);

int main(){

	int i,N=12,x[N],count=0;
	float y[N],o[N], m0, b0; 
	FILE *fp; //Para abrir documento para leer archivos iniciales
	
	fp=fopen("datos.txt","r");

	for(i=0;i<N;i++){
		if(count<N-2){	
			fscanf(fp,"%i %f %f",&x[i],&y[i],&o[i]);
		}		

		else{
			fscanf(fp,"%f %f",&m0,&b0);
		}
	count++;
	}
	fclose(fp);

	calculo_monte(&m0, &b0, N-1, x, y, o);

return 0;
}

void calculo_monte(float* m0,float* b0, int N,  int x[], float y[], float o[]){

	float mn, bn, Pmn, mmin, mmax, bmin, bmax,num, sigmam, sigmab;
	int i,L;
	double lnpl;
	FILE *fp2;
	FILE *fp3;
	
	fp3=fopen("parametros.txt","r");

	fscanf(fp3, "%f %f", &sigmam, &sigmab);
 	fscanf(fp3, "%f %f %f %f", &mmin, &mmax, &bmin, &bmax);
	fscanf(fp3, "%i", &L);

	fclose(fp3);

	fp2=fopen("Resultados.txt","w");

	for(i=0; i<=L; i++){
		lnpl= likelihood(*m0, *b0, N, x, y, o);
		mn = num_gauss(*m0, sigmam);
		bn = num_gauss(*b0, sigmab);
		
			if(mmin<mn<mmax && bmin<bn<bmax){ 
				Pmn=likelihood(mn, bn, N, x, y, o); 
									
					if(Pmn > lnpl){
					*m0=mn;
					*b0=bn;
					}

					else{
					num=rand()*(1.0/RAND_MAX);
										
						if(num < exp(Pmn)){
							*m0=mn;
							*b0=bn;
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




