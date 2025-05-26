#include <iostream>
#include <ctime>
#include <omp.h>
#include <cstdlib>
using namespace std;
int main(){
	const int size=1000000;
	int max_s=0;
	int max_p=0;
	int* array=new int[size];
	srand(time(0));
	for(int i=0;i<size;i++){
		array[i]=rand()%100+1;
	}
	//secuencial
	double inicio_s=omp_get_wtime();
	for(int i=0;i<size;i++){
		if(array[i]>max_s){
			max_s=array[i];
		}
	}
	double fin_s=omp_get_wtime();
	
	//paralelo
	double inicio_p=omp_get_wtime();
	#pragma omp parallel for reduction(max:max_p)
	for(int i=0;i<size;i++){
		if(array[i]>max_p){
			max_p=array[i];
		}
	}
	double fin_p=omp_get_wtime();
	
	if(max_p==max_s){
		cout<<"El numero mayor es el mismo: "<<max_p<<endl;
	}else{
		cout<<"El numero mayor secuencial es: "<<max_s<<endl;
		cout<<"El numero mayor parelelo es: "<<max_p<<endl;
	}
	cout<<"El tiempo secuencial es de: "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"El tiempo paralelo es de: "<<(fin_p-inicio_p)<<" segundos"<<endl;
}