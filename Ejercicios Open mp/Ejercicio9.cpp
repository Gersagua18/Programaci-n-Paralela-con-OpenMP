#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;
const int size=500;
const int generaciones=100;
int contar_vecinos(int** mundo,int x, int y){
	int vivos=0;
    for(int dx=-1;dx<=1;dx++){
        for(int dy=-1;dy<=1;dy++){
            if(dx==0 && dy==0)continue;
            int nx=x+dx;
            int ny=y+dy;
            if (nx>=0 && nx<size && ny>=0 && ny<size) {
                vivos+=mundo[nx][ny];
            }
        }
    }
    return vivos;
}
void imprimir_mundo(int** mundo){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<(mundo[i][j]? "o ":". ");
		}
		cout<<endl;
	}
	cout<<endl;
}
int** crear_matriz(){
	int** matriz=new int*[size];
	for(int i=0;i<size;i++) matriz[i]=new int[size];
	return matriz;
}
void eliminar_matriz(int** matriz){
	for(int i=0;i<size;i++) 
		delete[] matriz[i];	
	delete[] matriz;	
}
void copiar_matriz(int** origen, int** destino){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			destino[i][j]=origen[i][j];
		}
	}
}

int main(){
	srand(time(0));
	int** mundo_s=crear_matriz();
	int** nuevo_s=crear_matriz();
	int** mundo_p=crear_matriz();
	int** nuevo_p=crear_matriz();
	
	for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            int val=rand()%2;
            mundo_s[i][j]=val;
            mundo_p[i][j]=val;
        }
    }
    //secuencial
    double inicio_s=omp_get_wtime();
	for(int gen=0;gen<generaciones;gen++){
        for(int i=0;i<size;i++) {
            for(int j=0;j<size;j++){
                int vecinos=contar_vecinos(mundo_s,i,j);
                nuevo_s[i][j]=(mundo_s[i][j]==1)? (vecinos==2 || vecinos==3):(vecinos==3);
            }
        }
        copiar_matriz(nuevo_s, mundo_s);
    }
	double fin_s=omp_get_wtime();
	//paralelo
	double inicio_p=omp_get_wtime();
	for(int gen=0;gen<generaciones;gen++){
        #pragma omp parallel for collapse(2)
        for(int i=0;i<size;i++) {
            for(int j=0;j<size;j++){
                int vecinos=contar_vecinos(mundo_p,i,j);
                nuevo_p[i][j]=(mundo_p[i][j]==1)? (vecinos==2 || vecinos==3):(vecinos==3);
            }
        }
        copiar_matriz(nuevo_p, mundo_p);
    }
	double fin_p=omp_get_wtime();
	
	cout<<"Tiempo secuencial: "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"Tiempo paralelizado "<<(fin_p-inicio_p)<<" segundos"<<endl;
	
	
    eliminar_matriz(mundo_s);
    eliminar_matriz(nuevo_s);
    eliminar_matriz(mundo_p);
    eliminar_matriz(nuevo_p);

    return 0;
}