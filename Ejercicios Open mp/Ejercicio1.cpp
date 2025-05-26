#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){
	long long sum_p=0;
	long long sum_s=0;
	const int size=1000000;
	int* array=new int[size];
	srand(time(0));
	
	for(int i=0;i<size;i++){
		array[i]=rand()%100+1;
	}

	omp_set_num_threads(4);
	
	//Secuencial
	double inicio_s=omp_get_wtime();
	for(int i=0;i<size;i++){
		sum_s+=array[i];
	}
	double fin_s=omp_get_wtime();
	
	//Paralela
	double inicio_p=omp_get_wtime();
	#pragma omp parallel for reduction(+:sum_p)
	for(int i=0;i<size;i++){
		sum_p+=array[i];
	}
	
	
	double fin_p=omp_get_wtime();
	delete[]array;
	cout<<"Suma secuencial: "<<sum_s<<" Con un tiempo de: "<<(fin_s-inicio_s)<<endl;
	cout<<"Suma paralela: "<<sum_p<<" Con un tiempo de: "<<(fin_p-inicio_p)<<endl;	
	return 0;
}