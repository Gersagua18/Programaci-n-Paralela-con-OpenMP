#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;
int main(){
	const int size=1000000;
	long long suma_p=0;
	long long suma_pr=0;
	int* array=new int[size];
	srand(time(0));
	for(int i=0;i<size;i++){
		array[i]=rand()%100+1;
	}
	
	//paralelo sin clausula de reduccion
	double inicio_p=omp_get_wtime();
	#pragma omp parallel for
	for(int i=0;i<size;i++){
		suma_p+=array[i];
	}
	double fin_p=omp_get_wtime();
	
	//paralelismo con clausula de reduccion
	double inicio_pr=omp_get_wtime();
	#pragma omp parallel for reduction(+:suma_pr)
	for(int i=0;i<size;i++){
		suma_pr+=array[i];
	}
	double fin_pr=omp_get_wtime();
	
	cout<<"Tiempo de duracion sin clausula de reduccion: "<<(fin_p-inicio_p)<<" segundos"<<endl;
	cout<<"Tiempo de duracion con clausula de reduccion: "<<(fin_pr-inicio_pr)<<" segundos"<<endl;
}