#include <stdlib.h>
#include <stdio.h>

/* Struct Aresta */
typedef struct{
    int v;
    int w;
} Aresta;

/* Struct Grafo representado por matriz */
struct grafo{
    int n;
    int m;
    int **adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* TAD GRAFO */
Grafo GRAFOcria(int);
void GRAFOinsereA(Grafo, Aresta);
void GRAFOremoveA(Grafo, Aresta);
void GRAFOinsereApeso(Grafo, Aresta, int);
void GRAFOinsereDpeso(Grafo, Aresta, int);
void GRAFOimprime(Grafo);
void GRAFOdestroi(Grafo);
void GRAFOgrau(Grafo);

/* Construtores de grafos */
Grafo GRAFOconstroiCompleto(int);
Grafo GRAFOconstroiCiclo(int);
Grafo GRAFOconstroiGrade(int);
Grafo GRAFOconstroiPontes(int);

/* Algoritmos */
void BPrec(Grafo G);
void visitaBP(Grafo G, int v);
void BL(Grafo G);
void visitaBL(Grafo G, int v);
int Pontes(Grafo G, int vertice1, int vertice2);
void pontesRec(Grafo G, int v);
void Articulacao(Grafo G);
void artRec(Grafo G, int v);
void BellmanFord(Grafo G, int v);
void FloydWarshall(Grafo G);
int menorVertice(int* aberto, int* dist,Grafo G);
int min(int i, int j);
void dijkstra(Grafo G, int v);
void Prim_Matriz(Grafo G, int orig);
void Kruskal_Matriz (Grafo G);

// Leitura do arquivo
Grafo GRAFOleitura(const char *nomearq);
