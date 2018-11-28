//Proyecto final de Programación Básica 2018
//Cadenas de Markov Chain Montecarlo (MCMC) con el método de Metropolis
//Participantes: Diana Hernández Bustos y Diana Rosales Rosales
//Este trabajo se comenzó el Miércoles 28 de Noviembre

#include<stdio.h>
#include<math.h>
int main(){

int i=0,N;
N=10;
float x[N],y[N],error[N];


FILE *fp; //Para abrir documento para leer archivos iniciales

fp=fopen("datos.txt","r");

for(i=0;i<N;i++){
	fscanf(fp,"%f %f %f",&x[i],&y[i],&error[i]);
	printf("%f %f %f \n",x[i],y[i],error[i]);
		}

return 0;
}
