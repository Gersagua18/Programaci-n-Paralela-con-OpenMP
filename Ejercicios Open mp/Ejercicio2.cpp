#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(){
	const int size=100;
	int** matrizA=new int*[size];
	int** matrizB=new int*[size];
	int** suma_p=new int*[size];
	int** suma_s=new int*[size];
	for(int i=0;i<size;i++){
		matrizA[i]=new int[size];
		matrizB[i]=new int[size];
		suma_s[i]=new int[size];
		suma_p[i]=new int[size];
	}
	srand(time(0));
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			matrizA[i][j]=rand()%10+1;
			matrizB[i][j]=rand()%10+1;
			suma_p[i][j]=0;
			suma_s[i][j]=0;
		}		
	}
	//secuencial
	double inicio_s=omp_get_wtime();
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			for(int k=0;k<size;k++){
				suma_s[i][j]+=matrizA[i][k]*matrizB[k][j];
			}
			
		}
	}
	double fin_s=omp_get_wtime();
	
	//paralelo
	double inicio_p=omp_get_wtime();
	#pragma omp parallel for collapse(2)
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			int temp=0;
			for(int k=0;k<size;k++){
				temp+=matrizA[i][k]*matrizB[k][j];
			}
			suma_p[i][j]=temp;
		}
	}
	double fin_p=omp_get_wtime();
	cout<<"Tiempo de duracion secuencial: "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"Tiempo de duracion paralelo: "<<(fin_p-inicio_p)<<" segundos"<<endl;
	//liberar memoria
	for(int i=0;i<size;i++){
	    delete[] matrizA[i];
	    delete[] matrizB[i];
    	delete[] suma_p[i];
    	delete[] suma_s[i];
	}
	delete[] matrizA;
	delete[] matrizB;
	delete[] suma_p;
	delete[] suma_s;
	return 0;
}