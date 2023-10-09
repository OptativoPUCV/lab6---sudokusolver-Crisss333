/*
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

int is_valid(Node* n) {
    int marks[10];
    for (int i = 0; i < 9; i++) {
        memset(marks, 0, sizeof(marks));  // Limpiar marcas para cada fila
        for (int j = 0; j < 9; j++) {  // Validación de filas
            if (n->sudo[i][j] != 0 && marks[n->sudo[i][j]] == 1)
                return 0;
            marks[n->sudo[i][j]] = 1;
        }
        memset(marks, 0, sizeof(marks));  // Limpiar marcas para cada columna
        for (int j = 0; j < 9; j++) {  // Validación de columnas
            if (n->sudo[j][i] != 0 && marks[n->sudo[j][i]] == 1)
                return 0;
            marks[n->sudo[j][i]] = 1;
        }
    }
    for (int k = 0; k < 9; k++) {
        memset(marks, 0, sizeof(marks));  
        for(int p = 0; p < 9; p++) {
            int i = 3*(k/3) + (p/3);
            int j = 3*(k%3) + (p%3);
            if (n->sudo[i][j] != 0 && marks[n->sudo[i][j]] == 1)
                return 0;
            marks[n->sudo[i][j]] = 1;
        }
    }
    return 1;
}

*/


/*
int is_final(Node* n){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                return 0;  // Encuentra una casilla vacía, retorna 0
            }
        }
    }
    return 1;  // Todas las casillas están llenas, retorna 1
}


Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);

    while(!is_empty(S)){
        Node* current = top(S);
        pop(S);
        (*cont)++;

        if(is_final(current)){
            clean(S);  // Limpiar el stack
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while(adj_node != NULL){
            push(S, adj_node);
            adj_node = next(adj_nodes);
        }
        clean(adj_nodes);  // Limpiar la lista de nodos adyacentes
        free(current);  // Liberar el nodo actual
    }

    return NULL;
}
*/



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/


















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

int is_valid(Node* n) {
    int row_check[9][10] = {0}; // Arreglo para verificar las filas.
    int col_check[9][10] = {0}; // Arreglo para verificar las columnas.
    int submatrix_check[9][10] = {0}; // Arreglo para verificar las submatrices.

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            
            // Ignorar las casillas vacías (cero).
            if (num == 0) continue;

            // Verificar filas.
            if (row_check[i][num] == 1) {
                printf("Fila %d, número %d repetido.\n", i, num);
                return 0; // Número repetido en la fila.
            }
            row_check[i][num] = 1;

            // Verificar columnas.
            if (col_check[j][num] == 1) {
                printf("Columna %d, número %d repetido.\n", j, num);
                return 0; // Número repetido en la columna.
            }
            col_check[j][num] = 1;

            // Verificar submatrices de 3x3.
            int submatrix_index = 3 * (i / 3) + (j / 3);
            if (submatrix_check[submatrix_index][num] == 1) {
                printf("Submatriz %d, número %d repetido.\n", submatrix_index, num);
                return 0; // Número repetido en la submatriz.
            }
            submatrix_check[submatrix_index][num] = 1;
        }
    }

    return 1; // El estado/nodo es válido.
}

List* get_adj_nodes(Node* n){
    List* list = createList();
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                for(int num = 1; num <= 9; num++){
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = num;
                    if(is_valid(new_node)){
                        pushBack(list, new_node);
                    } else {
                        free(new_node);  // Libera la memoria si el nodo no es válido
                    }
                }
                return list;  // Retorna la lista después de encontrar y llenar la primera casilla vacía
            }
        }
    }
    return list;
}

/*
List* get_adj_nodes(Node* n){
    List* list = createList();

    int found = 0; // Bandera para verificar si se encontró al menos un nodo válido

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

                    // Verificar si el nodo resultante es válido.
                    if (is_valid(adj_node)) {
                        // Si es válido, agregar el nodo adyacente a la lista.
                        push(list, adj_node);
                        found = 1; // Se encontró al menos un nodo válido
                    } else {
                        // Si no es válido, liberar la memoria del nodo no válido.
                        free(adj_node);
                    }
                }
                // Se ha encontrado una casilla vacía, no es necesario buscar más.
                if (found) {
                    break;
                }
            }
        }
        // Se ha encontrado una casilla vacía, no es necesario buscar más.
        if (found) {
            break;
        }
    }            
    return list;
}
*/

int is_final(Node* n){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                // Si se encuentra una casilla vacía, el nodo no es final.
                return 0;
            }
        }
    }
    // Si no se encontraron casillas vacías, el nodo es final.
    return 1;
}


/*
Node* DFS(Node* initial, int* cont){
  return NULL;
}
*/

/*
Node* DFS(Node* initial, int* cont){
    Stack* stack = createStack();
    push(stack, initial);
  
    while (!is_empty(stack)) {
        Node* current_node = top(stack);
        pop(stack);
        (*cont)++;
      
        if (is_final(current_node)) {
            clean(stack);
            return current_node;
        }
      
        List* adj_nodes = get_adj_nodes(current_node);
        Node* aux_node = first(adj_nodes);
        while (aux_node != NULL) {
            push(stack, aux_node);
            aux_node = next(adj_nodes);
        }
      
        clean(adj_nodes);
    }
  
    clean(stack);
    return NULL;
}
*/

Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);

    while(!is_empty(S)){
        Node* current = top(S);
        pop(S);
        (*cont)++;

        if(is_final(current)){
            clean(S);  // Limpiar el stack
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while(adj_node != NULL){
            push(S, adj_node);
            adj_node = next(adj_nodes);
        }
        clean(adj_nodes);  // Limpiar la lista de nodos adyacentes
        free(current);  // Liberar el nodo actual
    }

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
}
*/



