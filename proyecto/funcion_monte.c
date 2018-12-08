#include<stdio.h> //Se hace la declaración de las librerías usadas
#include<math.h>
#include<stdlib.h> 
#include "funciones.h" //Incluímos la librería creada por nosotros que contiene la declaración de las 3 funciones utilizadas

void calculo_monte(int N,  int x[], float y[], float o[]){ //Esta función tiene elementos de entrada pero no de salida

	float *m0, *b0, pend[4], ord[4], mn, bn, Pmn, mmin, mmax, bmin, bmax, num, sigmam, sigmab, pendi, orde;//Hacemos declaración de variables de tipo decimal
	int i, L, count=0, j; //L es las veces que quiere el usuario que se corra el programa para calcular m y b que mejor se ajustan a los datos experimentales
	double lnpl; //lnpl, es el logaritmo de likelihood
	FILE *fp2; //Se hace la declaración del archivo de escritura donde van a estar nuestros resultados
	FILE *fp3; //Se hace la declaración del archivo de lectura donde se encuentran los parámetros para que funcione este método

	fp3=fopen("parametros.txt","r"); //Se abre el archivo de lectura que contiene los parámetros
		for(j=0; j<4; j++){
			if(count==0){
				fscanf(fp3, "%f %f", &sigmam, &sigmab); //SE obtienen datos como "m" y "b" máximas, mínimas e iniciales, así cómo la cantidad de dispersión que se quiere que el archivo dé a los valores
	 			fscanf(fp3, "%f %f %f %f", &mmin, &mmax, &bmin, &bmax);
				fscanf(fp3, "%i", &L);
				fscanf(fp3, "%f %f", &pend[j], &ord[j]);
			}

			else{
				fscanf(fp3, "%f %f", &pend[j], &ord[j]);
			}

			count++;
			
			m0=(float*) malloc((L+10)*sizeof(int));//Se le ofrece un espacio reservado en la memoria a todos aquellos m0 y b0 que van a salir con el FOR, el cual corre "L" veces, pero más las pendientes y ordenadas iniciales puede a llegar a ser más.
			b0=(float*) malloc((L+10)*sizeof(int));//Se le ofrece un espacio reservado en la memoria a todos aquellos m0 y b0 que van a salir con el FOR, el cual corre "L" veces, pero más las pendientes y ordenadas iniciales puede a llegar a ser más

			pendi=pend[j];
			orde=ord[j];

			m0=&pendi; //Se le asigna un valor al apuntador de m0 y b0
			b0=&orde;

			char buffer [32]; //SE utiliza una variable de tipo char que tenga varios elementos (los diferentes nombres) de mis archivos a crear
			snprintf(buffer, sizeof(char)*32, "Res_cadena%i.txt",j+1); //Asigno un nombre a cada uno de los archivos que se van a crear, los cuales van a tener el nombre según las veces que se haya hecho la iteración.
	
			fp2=fopen(buffer,"w"); //Se abre el archivo de escritura con el nombre de "Resultados"	

			for(i=0; i<=L; i++){ //Se hace un FOR que corra "L" veces, el cual fue definido en el archivo de parámetros, de 1 en 1
				lnpl= likelihood(*m0, *b0, N, x, y, o); //Se llama a la función likelihood (que tiene 6 elementos de entrada y 1 de salida) para que regrese el valor del logaritmo de likelihood
		
				mn = num_gauss(*m0, sigmam);//Se llama a la función num_gauss(que tiene 2 elementos de entrada) para que regrese al programa 1 número aleatorio para la pendiente que no se pase de sigmam 
				bn = num_gauss(*b0, sigmab);//Se llama a la función num_gauss(que tiene 2 elementos de entrada) para que regrese al programa 1 número aleatorio para la ordenada al origen que no se pase de sigmab 
		
				if(mmin<mn<mmax && bmin<bn<bmax){ //Si la nueva pendiente y la nueva ordenada no se pasan de los parátreos establecidos en los datos de parámetros, entonces:
					Pmn=likelihood(mn, bn, N, x, y, o); //Se calcula la probabilidad de la nueva pendiente y se llama a esta función para que logre su objetivo
									
					if(Pmn > lnpl){ //Si el logaritmo de mn es mayor al log de likelihood (de la pendiente anterior), entonces:
						//Se iguala la pendiente y la ordenada anteriores a las nuevas
						*m0=mn; 					
						*b0=bn;					
					}

					else{ //Si lo anterior no se cumple:
					num=rand()*(1.0/RAND_MAX); //Se escoge un número al asar entre 0 y 1 
										
						if(num < exp(Pmn)){ //Si el número que se obtuvo es menor a la probablidad de la pendiente nueva
							//Se iguala la pendiente y la ordenada anteriores a las nuevas
							*m0=mn;							
							*b0=bn;
							
						}
					}
				}

		fprintf(fp2, "%f \t %f \t %f \n",lnpl, *m0, *b0); //Se imprimen los resultados del logaritmo de likelihood, la pendiente y la ordenada que sí cumplieron con todos los requisitos
	
		}
		fclose(fp2); //Se cierra el archivo de escritura
		}
		fclose(fp3); //Se cierra el archivo de lectura
	
} //Se cierra esta función


