#include<stdio.h> //SE hace la declaración de todas las librerías que se van a usar en el programa
#include<math.h>
#include<stdlib.h> 
#include "funciones.h" //Se incluye la librería creada por nosotras mismas que contiene la declaración de todas las funciones utilizadas

float likelihood(float m0, float b0, int N, int x[], float y[], float o[]){ //Se abre la función likelihood, que tiene estos elementos de entrada y uno de salida, que viene siendo el logaritmo de likelihood (In de la probabilidad)
	float ymod[N], aux, sumatoria=0, lnpl; //SE hace la declaración de las variables utilizadas en esta función
	int j;
 
		for(j=0;j<N;j++){ //Se calcula el logaritmo de likelihood
			ymod[j]=m0*x[j]+b0; //Primero se obtiene un arreglo de una función (y) con la pendiente y la ordenada de entrada 
			aux=(pow((y[j]-ymod[j]),2))-(pow(o[j],2)); //Después se hace este cálculo que reemplaza a un ajuste de mínimos cuadrados
			sumatoria+=aux; //Se hace una sumatoria de los cálculos hechos		
		}	
		lnpl=(-0.5)*sumatoria; //Luego, se saca el logaritmo de likelihood

	return lnpl; //Se regresa el logaritmo natural obtenido
}//Se cierra esta función


double num_gauss(double x, double y) { //Se abre esta función para obtener 2 números al asar por medio de una distribución gaussiana, la cual, sólo tiene elementos de entrada la pendiente original y la sigma; o bien, la ordenada al origen y su repectiva sigma
	//Se hace la declaración de las variables
	double aux, u, v, s;
	do {
		u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0; //Se escogen 2 números al asar entre 0 y 1
		v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		s = u * u + v * v; //Se calcula s
	}

	while( (s >= 1.0) || (s == 0.0) ); //Siempre que s sea menor a 1 y mayor a 0
		s = sqrt(-2.0 * log(s) / s); //Se hace esta operación para obtener mNEW y bNEW
		aux = v * s;
		return x + y * u * s; //Se regresa el valor de mNEW y bNEW
	
} //Se cierra esta función
