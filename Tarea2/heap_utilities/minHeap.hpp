// Agregado de librearias a utilizar para el algoritmo de monticulos
#include <climits>
#include <math.h>
//#include "../geometry/node.hpp"
// Codigo basado en ejemplo aplicado dentro de la materia de Analisis de Algoritmos
// Para presentar el ejemplo de HeapSort.
// Pero en este caso aplicando el algorithm de MinHeap.

// funcion destinada para asignar el valor de un nodo a otro
void swap(Node** A, int i, int j){
    Node *temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
// funciones designadas para tomar el valor de los nodos hijos
// el valor del nodo de izquierda
// el valor dle nodo de derecha
int left(int i){
    return 2*i + 1;
}

int right(int i){
    return 2*i + 2;
}

// La funcion de min_heapify se modifica para que reciba un arreglo de nodos
// Aqui se verifica ambos lados de un nodo para ver si es menor que el nodo indice.
void min_heapify(Node** A, int i, int heap_size){
    int smallest = i;
    int l = left(i);
    int r = right(i);
    if( l < heap_size && A[ l ]->get_ID() < A[ smallest ]->get_ID() )
        smallest = l;    
    if( r < heap_size && A[ r ]->get_ID() < A[ smallest ]->get_ID() )
        smallest = r;
    if( smallest != i ){
        swap(A, i, smallest);
        min_heapify(A, smallest, heap_size);
    }
}

// La funcion de build_max_heap se modifica para que reciba un arreglo de nodos
// y dentro de esta funcion lo que realiza es construir un min heap
void build_max_heap(Node** A, int heap_size){
    //int heap_size = n;
    for(int i = floor(heap_size/2)-1; i >= 0; i--)
        min_heapify(A, i, heap_size);
}

// La funcion de heapsort se modifica para que reciba un arreglo de nodos
void heapsort(Node** A, int n){
    int heap_size = n;
    build_max_heap(A, heap_size);
    for(int i = n-1; i > 0; i--){
        swap(A, 0, i);
        heap_size--;
        min_heapify(A, 0, heap_size);
    }
}