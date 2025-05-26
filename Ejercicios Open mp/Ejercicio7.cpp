#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
#include <random>
using namespace std;

double calcular_pi_montecarlo_secuencial(long long total_puntos){
	long long puntos_dentro=0;
	srand(time(0));
	for(long long i=0;i<total_puntos;i++){
		double x=rand()/(double)RAND_MAX;
		double y=rand()/(double)RAND_MAX;
		
		if(x*x+y*y<=1.0){
			puntos_dentro++;
		}
	}
	return 4.0*puntos_dentro/total_puntos;
}
double calcular_pi_montecarlo_paralelo(long long total_puntos,int num_hilos){
	long long puntos_dentro=0;
	omp_set_num_threads(num_hilos);
	#pragma omp parallel reduction(+:puntos_dentro)
	{
		/*unsigned int seed=time(0)^omp_get_thread_num();
		mt19937 rng(seed);
		uniform_real_distribution<double> dist(0.0,1.0);*/
		long long local_dentro=0;
		#pragma omp for
		for(long long i=0;i<total_puntos;i++){
			double x=rand()%2;
			double y=rand()%2;
			
			if(x*x+y*y<=1.0){
				puntos_dentro++;
			}
		}	
	}
	
	return 4.0*puntos_dentro/total_puntos;
}


int main(){
	long long total_puntos=1000000000;
	int num_threads=4;
	//secuencial
	double inicio_s=omp_get_wtime();
	double pi_s=calcular_pi_montecarlo_secuencial(total_puntos);
	double fin_s=omp_get_wtime();
	//paralelo
	double inicio_p=omp_get_wtime();
	double pi_p=calcular_pi_montecarlo_paralelo(total_puntos,num_threads);
	double fin_p=omp_get_wtime();
	
	cout<<"Aproximacion de pi secuencial: "<<pi_s<<endl;
	cout<<"Tiempo de ejecucion: "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"Aproximacion de pi paralelo: "<<pi_p<<endl;
	cout<<"Tiempo de ejecucion: "<<(fin_p-inicio_p)<<" segundos"<<endl;
}