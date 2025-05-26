#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;
void merge(int array[], int left[], int leftSize, int right[], int rightSize);
void merge_sort(int array[], int size){
    if (size< 2) {
        return;
    }
    int mid=size/2;
    int* left=new int[mid];
    int* right=new int[size-mid];

    for (int i=0;i<mid;i++) {
        left[i]=array[i];
    }

    for (int i=mid;i<size;i++) {
        right[i-mid]=array[i];
    }

    merge_sort(left,mid);
    merge_sort(right,size-mid);

    merge(array,left,mid,right,size-mid);
    delete[] left;
    delete[] right;
}
void merge(int array[], int left[], int leftSize, int right[], int rightSize) {
    int i=0,j=0,k=0;

    while(i<leftSize && j<rightSize){
        if(left[i]<=right[j]) {
            array[k++]=left[i++];
        }else{
            array[k++]=right[j++];
        }
    }
    while (i<leftSize) {
        array[k++]=left[i++];
    }

    while (j<rightSize) {
        array[k++]=right[j++];
    }
}
int busqueda_binaria(int array[],int size,int bsc){
	int inicio=0;
	int fin=size-1;
	while(inicio<=fin){
		int medio=inicio+(fin-inicio)/2;
		if(array[medio]==bsc){
			return medio;
		}else if(array[medio]<bsc){
			inicio=medio+1;
		}else{
			fin=medio-1;
		}
	}
	return -1;
}
int main(){
	srand(time(0));
	const int size=100;
	const int size_bsc=5;
	int* array=new int[size];
	int* bsc=new int[size_bsc];
	for(int i=0;i<size_bsc;i++){
		bsc[i]=rand()%100+1;
	}
	for(int i=0;i<size;i++){
		array[i]=rand()%100+1;
	}
	merge_sort(array,size);
	//paralelizacion
	omp_set_num_threads(4);
	#pragma omp parallel for
	for(int i=0;i<size_bsc;i++){
		int resul=busqueda_binaria(array,size,bsc[i]);
		#pragma omp critical
		{
			if(resul!=-1){
				cout<<"Numero "<<bsc[i]<<" encontrado en indice "<<resul<<" por hilo "<<omp_get_thread_num()<<endl;
				
			}else{
				cout<<"Numero "<<bsc[i]<<" no encontrado en indice "<<" por hilo "<<omp_get_thread_num()<<endl;
			}
		}
	}
}