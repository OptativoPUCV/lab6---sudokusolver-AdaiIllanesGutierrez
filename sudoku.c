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
   // Validar filas
    for (int i = 0; i < 9; i++) {
        int seen[10] = {0};
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1;
            }
        }
    }

    // Validar columnas
    for (int j = 0; j < 9; j++) {
        int seen[10] = {0};
        for (int i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1;
            }
        }
    }

    // Validar submatrices 3x3
    for (int k = 0; k < 9; k++) {
        int seen[10] = {0};
        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1;
            }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
   // Encontrar la primera casilla vacía
    int row = -1, col = -1;
    for (int i = 0; i < 9 && row == -1; i++) {
        for (int j = 0; j < 9 && col == -1; j++) {
            if (n->sudo[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }

    // Si no hay casillas vacías, no hay nodos adyacentes
    if (row == -1) return list;

    // Generar nodos adyacentes
    for (int num = 1; num <= 9; num++) {
        Node* adj = copy(n);
        adj->sudo[row][col] = num;
        if (is_valid(adj)) {
            pushBack(list, adj);
        } else {
            free(adj);
        }
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
             if (n->sudo[i][j] == 0) {
                 return 0;
             }
         }
     }
   return 1;
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