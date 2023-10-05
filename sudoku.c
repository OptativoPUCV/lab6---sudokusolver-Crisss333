#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int row_check[9][10] = {0}; // Arreglo para verificar las filas.
    int col_check[9][10] = {0}; // Arreglo para verificar las columnas.
    int submatrix_check[9][10] = {0}; // Arreglo para verificar las submatrices.

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];

            // Verificar filas.
            if (row_check[i][num] == 1) {
                return 0; // Número repetido en la fila.
            }
            row_check[i][num] = 1;

            // Verificar columnas.
            if (col_check[j][num] == 1) {
                return 0; // Número repetido en la columna.
            }
            col_check[j][num] = 1;
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    // Iterar a través del tablero para encontrar una casilla vacía.
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (n->sudo[row][col] == 0) {
                // Encontrar una casilla vacía e intentar colocar números del 1 al 9.
                for (int num = 1; num <= 9; num++) {
                    // Crear una copia del nodo original para modificarla.
                    Node* adj_node = copy(n);
                    // Intentar colocar el número en la casilla vacía.
                    adj_node->sudo[row][col] = num;
                    // Agregar el nodo adyacente a la lista.
                    push(list, adj_node);
                }
                // Se ha encontrado una casilla vacía, no es necesario buscar más.
                break;
            }
        }
    }            
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/