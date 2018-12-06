//Proyecto final de Programación Básica 2018
//Cadenas de Markov Chain Montecarlo (MCMC) con el método de Metropolis
//Participantes: Diana Hernández Bustos y Diana Rosales Rosales
//Este trabajo se comenzó el Miércoles 28 de Noviembre

#include<stdio.h> //Incluímos todas las librerías que se van a usar en el programa
#include<math.h>
#include<stdlib.h> 
#include "funciones.h" //Esta es una librería hecha por nosotras que contiene las 3 funciones utilizadas en este programa

int main(){

	//SE hace la declaración de nuestras variables. Los datos de nuestro experimento son de tipo arreglo con igual núm. de elementos
	int i, N=11,x[N];
	float y[N],o[N]; //La desviación estándar o margen de error de nuestro experimento es o
	FILE *fp; //Para abrir documento para leer archivos iniciales

	fp=fopen("datos.txt","r"); //SE abre el archivo de lectura para poder asignar un valor a cada uno de las variables arreglo
	for(i=0;i<N;i++){ //ESte FOR corre "N" veces, donde N es la cantidad de elementos de nuestro experimento
		fscanf(fp,"%i %f %f",&x[i],&y[i],&o[i]); //Se obtiene el valor de cada elemento de nuestro arreglo
	}
	fclose(fp); //Se cierra el documento de lectura
	
	calculo_monte(N, x, y, o);//Se llama a la función (que no tiene elementos de salida) que va a hacer las operaciones de la Cadena de Márkov

return 0; //SE cierra el programa
}





