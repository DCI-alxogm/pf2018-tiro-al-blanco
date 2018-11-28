//Proyecto final de Programación Básica 2018
//Cadenas de Markov Chain Montecarlo (MCMC) con el método de Metropolis
//Participantes: Diana Hernández Bustos y Diana Rosales Rosales
//Este trabajo se comenzó el Miércoles 28 de Noviembre

#include<stdio.h>
#include<math.h>
int main(){

int i=0,N=10,x[N];

float y[N],error[N];


FILE *fp; //Para abrir documento para leer archivos iniciales

fp=fopen("datos.txt","r");

for(i=0;i<N;i++){
	fscanf(fp,"%i %f %f",&x[i],&y[i],&error[i]);
	printf("%i %f %f \n",x[i],y[i],error[i]);
		}
fclose(fp);

return 0;
}
