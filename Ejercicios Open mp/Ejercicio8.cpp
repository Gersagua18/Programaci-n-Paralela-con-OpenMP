#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;
double f(double x){//ecuacion de la funcion
	//double y=-1*(x*x)+(8*x)-12;
	double y=x*x;
	return y;
}
double metodo_trapecio_secuencial(double a,double b,int n){
	double h=(b-a)/n;
	double suma=0;
	double c=a;
	for(int i=1;i<=n;i++){
		double x=(h/2)*(f(c)+f(a+i*h));
		c=a+i*h;
		suma+=x;
	}
	return suma;
}
double metodo_trapecio_paralelo(double a,double b,int n){
	double h=(b-a)/n;
	double suma=0;
	#pragma omp parallel for reduction(+:suma)
	for(int i=1;i<=n;i++){
		double x=(h/2.0)*(f(a+(i-1)*h)+f(a+i*h));
		suma+=x;
	}
	return suma;
}
int main(){
	double a=3.0,b=5.0;
	int n=1000000;	
	double inicio_s=omp_get_wtime();
	double resultado_s=metodo_trapecio_secuencial(a,b,n);
	double fin_s=omp_get_wtime();
	
	double inicio_p=omp_get_wtime();
	double resultado_p=metodo_trapecio_paralelo(a,b,n);
	double fin_p=omp_get_wtime();
	
	if(resultado_s==resultado_p){
		cout<<"Los resultados son iguales: "<<resultado_s<<endl;
	}else{
		cout<<"Los resultados no son iguales"<<endl;
		cout<<"Paralelo: "<<resultado_p<<endl;
		cout<<"Secuencial: "<<resultado_s<<endl;
	}
	cout<<"Tiempo del Secuencial: "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"Tiempo del Paralelo: "<<(fin_p-inicio_p)<<" segundos"<<endl;
}