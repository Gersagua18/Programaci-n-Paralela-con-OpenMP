#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

void merge(int array[], int left[], int leftSize, int right[], int rightSize);
void merge_sort_secuencial(int array[], int size){
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

    merge_sort_secuencial(left,mid);
    merge_sort_secuencial(right,size-mid);

    merge(array,left,mid,right,size-mid);
    delete[] left;
    delete[] right;
}
void merge_sort_paralelo(int array[], int size, int hilos){
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
	if(hilos<=0){
		merge_sort_secuencial(left,mid);
    	merge_sort_secuencial(right,size-mid);
	}else{
		#pragma omp parallel sections
		{
				#pragma omp section
				merge_sort_paralelo(left,mid,hilos-1);
				#pragma omp section
				merge_sort_paralelo(right,size-mid,hilos-1);
		}
	}
    

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

int main(){
	const int size=1000000;
	int* array1=new int[size];
	int* array2=new int[size];
	srand(time(0));
	for(int i=0;i<size;i++){
		int val=rand()%100+1;
		array1[i]=val;
		array2[i]=val;
	}
	//secuencial
	double inicio_s=omp_get_wtime();
	merge_sort_secuencial(array1,size);
	double fin_s=omp_get_wtime();
	
	//paralelo
	double inicio_p=omp_get_wtime();
	merge_sort_paralelo(array2,size,4);
	double fin_p=omp_get_wtime();
	
	cout<<"Tiempo secuencial "<<(fin_s-inicio_s)<<" segundos"<<endl;
	cout<<"Tiempo paralelo "<<(fin_p-inicio_p)<<" segundos"<<endl;
}