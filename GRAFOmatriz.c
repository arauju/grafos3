#include "GRAFOmatriz.h"
#include "FILA.h"

/********** TAD GRAFO **********/

/* Cria matriz [ l ] [ c ] vazia */
int **MATRIZint(int l, int c){
    int i, j;
    int ** m = malloc(l * sizeof(int *));
    for (i = 0; i < l; i++)
        m[i] = malloc(c * sizeof(int));
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            m[i][j] = 0;
    return m;
}

/* Cria um grafo vazio de n vertices */
Grafo GRAFOcria(int n){
    Grafo G = malloc(sizeof(Grafo));
    G->n = n;
    G->m = 0;
    G->adj = MATRIZint(n,n);
    return G;
}

/* Funcao para inserir uma aresta em um grafo */
void GRAFOinsereA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = 1;
        G->adj[w][v] = 1;
    }
}

/* Funcao para inserir uma aresta em um grafo com peso */
void GRAFOinsereApeso(Grafo G, Aresta e, int peso){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = peso;
        G->adj[w][v] = peso;
    }
}

/* Funcao para inserir uma aresta em um grafo com peso */
void GRAFOinsereDpeso(Grafo G, Aresta e, int peso){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = peso;
    }
}

/* Funcao para remover uma aresta de um grafo */
void GRAFOremoveA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 1) {
        G->m--;
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;
    }
}

/* Funcao para imprimir um grafo */
void GRAFOimprime(Grafo G) {
    int v, w;
    printf(" \nGRAFO:" );
    //printf("%d vertices, %d arestas\n", G->n, G->m);
    for (v = 0; v < G->n; v++) {
        printf( "%2d:", v);
        for (w = 0; w < G->n; w++)
            if (G->adj[v][w] != 0)
                printf( " %2d", w);
        printf( "\n");
    }
}

/* Funcao para destruir um grafo */
void GRAFOdestroi(Grafo G){
    int i;
    for (i = 0; i < G->n; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}

/* Funcao para exibir os graus dos vertices de um grafo */
void GRAFOgrau(Grafo G){
    int v, w, grau;

    for (v = 0; v < G->n; v++) {
	grau = 0;
        for (w = 0; w < G->n; w++){
            if (G->adj[v][w] == 1) {
                grau++;
            }
        }
	  printf("grau[%d] = %d\n", v, grau);
    }
}

/********** IO **********/

// Leitura do arquivo
Grafo GRAFOleitura(const char *nomearq)
{
    int n, m, t, peso;
    Aresta e;
    FILE *arquivo;
    arquivo = fopen(nomearq,"r");

    if (!arquivo) {
        printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
        getchar();
        exit(1);
    }

    // n
    fscanf(arquivo, "%d %d %d", &n, &m, &t);
    Grafo G = GRAFOcria(n);

    // nao direcionado
    if (t == 0){
        while (!feof(arquivo)){
            fscanf(arquivo, "%d %d %d", &e.v, &e.w, &peso);
            GRAFOinsereApeso(G, e, peso);
        }
    }
    // direcionado
    else{
        while (!feof(arquivo)){
            fscanf(arquivo, "%d %d %d", &e.v, &e.w, &peso);
            GRAFOinsereDpeso(G, e, peso);
        }
    }

    fclose(arquivo);

    return G;
}

/********** CONSTRUTORES **********/

Grafo GRAFOconstroiCompleto(int n){
    int i, j;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
        for (j = i+1; j < n; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }
    return G;
}

Grafo GRAFOconstroiCiclo(int n){
    int i;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
	Aresta e;
	e.v = i;
        e.w = i+1;

	if (i == n-1) e.w = 0;

	GRAFOinsereA(G, e);
    }
    return G;
}

Grafo GRAFOconstroiPontes(int n){
    int i, j;
    Grafo G = GRAFOcria(n);
    // Clique 0 a 3
    for (i = 0; i < 4; i++){
        for (j = i+1; j < 4; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }

    // Aresta 3-4
    Aresta e;
    e.v = 3;
    e.w = 4;
    GRAFOinsereA(G, e);

    // Aresta 3-5
    e.v = 3;
    e.w = 5;
    GRAFOinsereA(G, e);

    // Clique 5 a 7
    for (i = 5; i < 8; i++){
        for (j = i+1; j < 8; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }

    // Aresta 7-8
    e.v = 7;
    e.w = 8;
    GRAFOinsereA(G, e);

    // Clique 8 a 10
    for (i = 8; i < 11; i++){
        for (j = i+1; j < 11; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }

    return G;
}

/********** ALGORITMOS **********/
int cont;
int *ordem, *pai, *menor;

// Profundidade
void BPrec(Grafo G){
    int i;
    ordem = malloc(G->n * sizeof(int));
    cont = 0;

    printf("Ordem BP: ");

    for (i = 0; i < G->n; i++)
        ordem[i] = -1;

    for (i = 0; i < G->n; i++){
	if (ordem[i] == -1){
	    visitaBP(G,i);
	}
    }

    printf("\n");
    free(ordem);
}

void visitaBP(Grafo G, int v){
    int j;
    ordem[v] = cont++;
    printf("%d ", v);

    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            visitaBP(G,j);
        }
    }
}

// Largura
void BL(Grafo G){
    int i;
    ordem = malloc(G->n * sizeof(int));
    cont = 0;

    printf("Ordem BL: ");

    for (i = 0; i < G->n; i++)
        ordem[i] = -1;

    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            visitaBL(G,i);
        }
    }

    printf("\n");
    free(ordem);
}

void visitaBL(Grafo G, int i){
    int v, j;
    FILAcria(G->n);
    FILAinsere(i);

    while(!FILAvazia()) {
        v = FILAremove(); // remove primeiro da fila
        if (ordem[v] == -1){
            ordem[v] = cont++;
            printf("%d ", v);

            for (j = 0; j < G->n; j++){
                if (G->adj[v][j] != 0 && ordem[j] == -1){
                    FILAinsere(j);
                }
            }
        }
    }

    FILAdestroi();
}

// Pontes
int Pontes(Grafo G, int vertice1, int vertice2){
    int i;

    ordem = malloc(G->n * sizeof(int));
    pai = malloc(G->n * sizeof(int));
    menor = malloc(G->n * sizeof(int));
    cont = 0;

    //printf("Pontes:\n");

    for (i = 0; i < G->n; i++)
        ordem[i] = pai[i] = menor[i] = -1;

    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            pai[i] = i;
            pontesRec(G,i);
        }
    }

    for (i = 0; i < G->n; i++) {
        if (menor[i] == ordem[i] && pai[i] != i){
            //printf("%d -- %d\n", pai[i], i);
            if (i == vertice1 && pai[i] == vertice2){
              return -1;
            }
            if (pai[i] == vertice1 && i == vertice2){
              return -1;
            }
        }
    }
    free(ordem);
    free(pai);
    free(menor);
    return 0;
}

void pontesRec(Grafo G, int v){
    int j;
    int min;
    ordem[v] = cont++;
    min = ordem[v];

    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            pai[j] = v;
            pontesRec(G,j);
            // descendente tem aresta de retorno
            if (menor[j] < min){
                min = menor[j];
            }
        }
        else if (G->adj[v][j] != 0){
            // aresta de retorno a partir de v
            if (ordem[j] < min && j != pai[v]){
                min = ordem[j];
            }
        }
    }
    menor[v] = min;


}

// Articulacao
void Articulacao(Grafo G){
    int i;

    ordem = malloc(G->n * sizeof(int));
    pai = malloc(G->n * sizeof(int));
    menor = malloc(G->n * sizeof(int));
    cont = 0;

    printf("Articulacoes:\n");

    for (i = 0; i < G->n; i++)
        ordem[i] = pai[i] = menor[i] = -1;

    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            pai[i] = i;
            artRec(G,i);
        }
    }

    int v, w;
    int *grau = malloc(G->n * sizeof(int));

    for (v = 0; v < G->n; v++) {
	grau[v] = 0;
        for (w = 0; w < G->n; w++){
            if (G->adj[v][w] == 1) {
                grau[v]++;
            }
        }
    }

    for (i = 0; i < G->n; i++) {
        if (menor[i] == ordem[i] && pai[i] != i){
            //printf("%d -- %d\n", pai[i], i);
	    // Testar se pai[i] eh articulacao
	    if (grau[pai[i]] > 1) printf("%d, ", pai[i]);

	    // Testar se i eh articulacao
	    if (grau[i] > 1) printf("%d, ", i);
        }
    }

    printf("\n");
    free(ordem);
    free(pai);
    free(menor);
}

void artRec(Grafo G, int v){
    int j;
    int min;
    ordem[v] = cont++;
    min = ordem[v];

    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            pai[j] = v;
            artRec(G,j);
            // descendente tem aresta de retorno
            if (menor[j] < min){
                min = menor[j];
            }
        }
        else if (G->adj[v][j] != 0){
            // aresta de retorno a partir de v
            if (ordem[j] < min && j != pai[v]){
                min = ordem[j];
            }
        }
    }
    menor[v] = min;
}

int menorVertice(int* aberto, int* dist,Grafo G){
  int menor = 9999;
  int indiceDoMenor;

  for(int i = 0 ; i < G->n ; i++){
    if(dist[i] < menor && aberto[i] == 1){
      menor = dist[i];
      indiceDoMenor = i;
      }
  }

  if (menor == 9999){
    return -1;
  }else{
    return indiceDoMenor;
  }
}

int min(int i, int j ){
  if(i < j ){
    return i;
  }else{
    return j;
  }
}

void dijkstra(Grafo G, int v){
  int r ;
  int p;
  int* dist = (int*) malloc(G->n * sizeof(int));
  int* pred = (int*) malloc(G->n * sizeof(int));
  int* aberto = (int*) malloc(G->n * sizeof(int));
  int acabou = 0;

  dist[v]= 0;
  pred[v] = -1;
  aberto[v] = 1;

  for( int i = 0 ; i < G->n ; i++){
    if(i != v){
      dist[i] = 2000;
      pred[i] = -1;
      aberto[i] = 1;
    }
  }

  while(!acabou){
    r = menorVertice(aberto,dist,G);
    aberto[r] = 0;
    if(r < 0){
      acabou = 1;

    }else{
      for(int i = 0 ; i < G->n ; i++){
        if(G->adj[r][i] >= 0 && aberto[i]){
          p = min(dist[i],dist[r]) + G->adj[r][i];
          if (p < dist[i]){
            dist[i] = p;
            pred[i] = r;
          }
        }
      }
    }
  }

  printf("Distancia do vertice %d para:\n", v);
  for(int i = 0 ; i < G->n ; i++){
    printf("%d: %d\n", i, dist[i]);
  }
}


void BellmanFord(Grafo G, int v){
  int *dist = malloc(G->n * sizeof(int));
  int *pred = malloc(G->n * sizeof(int));
  int altera = 0, i, j, k;
  dist[v] = 0;
  pred[v] = -1;
  printf("\ntotal: %d\n", G->n);
  for (i = 0; i < G->n; i++){
    if (i != v){
      if (G->adj[i][v] != 0){
        dist[i] = G->adj[i][v];
        pred[i] = v;
      }else{
        dist[i] = 9999;
        pred[i] = -1;
      }
    }
  }

  for (k = 0; k < G->n; k++){
    altera = 0;
    for (i = 0; i < G->n; i++){
      if (i != v){
        if (dist[i] > dist[j] + G->adj[j][i]){
          dist[i] = dist[j] + G->adj[j][i];
          pred[i] = j;
          altera = 1;
        }
      }
    }
    if (altera == 0)
      k = G->n;
  }

  printf("Distancia de %d entre os vértices: \n", v);
  for (i = 0; i < G->n; i++){
    printf("%d: %d\n", i, dist[i]);
  }
}


void FloydWarshall(Grafo G){
  int **L;
  int i, j, k;
  L = MATRIZint(G->n, G->n);

  for(i = 0; i < G->n; i++){
    for (j = 0; j < G->n; j++){
        L[i][j] = 9999;
    }
  }

  for (i = 0; i < G->n; i++){
    for (j = 0; j < G->n; j++){
      if (G->adj[i][j] != 0)
        L[i][j] = G->adj[i][j];
    }
  }

  for(k = 0; k < G->n; k++){
    for(i = 0; i < G->n; i++){
      for (j = 0; j < G->n; j++){
        if (L[i][j] > (L[i][k] + L[k][j])){
          L[i][j] = L[i][k] + L[k][j];
        }
      }
    }
  }

  /* Resultado */
  for(i = 0; i < G->n; i++){
    for (j = 0; j < G->n; j++){
      printf("%d  ", L[i][j]);
    }
    printf("\n");
  }
}


/* ARVORES */
void Prim_Matriz(Grafo G, int orig){
    int *pai = malloc(G->n * sizeof(int));
    int i, j, dest, primeiro, NV = G->n, pesoTotal = 0;
    double menorPeso;
    for (i = 0; i < NV; i++)
        pai[i] = -1; // sem pai
    pai[orig] = orig;
    while (1){
        primeiro = 1;
        //percorre todos os vertices
        for (i = 0; i < NV; i++){
            //achou vertices já visitados
            if (pai[i] != -1){
              //percorre os vizinhos do vertice visitados
              for (j = 0; j < NV; j++){
                  //procurar menor peso
                  if (pai[j] == -1 && G->adj[i][j] != 0){
                      if (primeiro){ //procura aresta de menor peso
                          menorPeso = G->adj[i][j];
                          orig = i;
                          dest = j;
                          primeiro = 0;
                          } else {
                          if (menorPeso > G->adj[i][j]){
                              menorPeso = G->adj[i][j];
                              orig = i;
                              dest = j;
                            }
                        }
                    }
                }
            }
        }
        if (primeiro == 1)
            break;
        pai[dest] = orig;
    }
    printf("Resposta Prim:\n");
    for (i = 0; i < NV; i++){
      printf("%d-%d\n", i, pai[i]);
      pesoTotal += G->adj[i][pai[i]];
    }
    printf("Peso total: %d\n", pesoTotal);
}

void Kruskal_Matriz (Grafo G){
  int min, k = -1, l = -1, x = -1, y = -1, NV = G->n, pesoTotal = 0;
  int *comp = malloc(G->n * sizeof(int));

  for (int i = 0; i < NV; i++)
    comp[i] = i;

  printf("Resposta Kruskal:\n");
  while (1){
    min = 9999;
    for (int i = 0; i < NV; i++){
      for (int v = 0; v < NV; v++){
        if (G->adj[i][v] > 0){
          if (comp[i] != comp[v] && min > G->adj[i][v]){
            min = G->adj[i][v];
            k = i;
            l = v;
          }
        }
      }
    }
    if (min == 9999)
      break;

    printf("%d - %d\n", k, l);
    pesoTotal += G->adj[k][l];
    x = comp[k]; y = comp[l];
    for (int v = 0; v < NV; v++){
      if(comp[v] == y)
        comp[v] = x;
    }
  }
  printf("Peso total: %d\n", pesoTotal);
}

void Hierholzer (Grafo G){
  int i, j, NV = G->n, impar = 0, verticeImpar, vertice, corrente, inicio, u, tamanhoTour = 0, v, posicaoVazia, fim = 0;
  int grau[NV], tour[G->m], subtour[G->m], tamanhoSubtour = 0;

  for (i = 0; i < G->m; i++){
    subtour[i] = -1;
    tour[i] = -1;
  }
  for(i = 0; i < NV; i++){
    grau[i] = 0;
  }
  //encontra o numero de vertices de grau impar
  for (i = 0; i < NV; i++){
    for (j = 0; j < NV;j++){
      if (G->adj[i][j] != 0 && i != j){
        grau[i]++;
      }
    }
  }
  for (i = 0; i < NV; i++){
    if (grau[i] % 2 != 0){
      impar ++;
      verticeImpar = i;
    }
  }

  //Verifica se é euleriano ou semi
  if (impar > 2){
    printf(" ERRO: grafo não possui caminho ou ciclo euleriano\n");
  } else {
    if (impar == 2){
      v = verticeImpar;
    } else {
      v = 1;
    }
  }

  tour[0] = v;
  do {
    //encontra v
    int sair = 0;
    for (i = 0; i < G->m; i++){
      vertice = tour[i];
      if(sair == 1){
        break;
      }
      for (j = 0; j < NV; j++){
        if (G->adj[vertice][j] != 0){
          v = vertice;
          sair = 1;
          break;
        }
      }
    }
    for (i = 0; i < G->m; i++){
      subtour[i] = -1;
    }
    subtour[0] = v;
    corrente = v;

    do{
      //encontra u, sendo o proximo adj de v
      for (i = 0; i < NV; i++){
        if (G->adj[corrente][i] != 0){
          u = i;
        }
      }
      //marca a aresta
      G->adj[corrente][u] = 0;
      grau[corrente]--;
      grau[u]--;
      subtour[tamanhoSubtour] = u;
      tamanhoSubtour++;
      corrente = u;
    //  printf("%d\n", subtour[posicaoVazia]);
    } while (v != corrente);
    //integrar subtour
    for (i = 0; i < G->m; i++){
      if(tour[i] == subtour[0]){
        inicio = i;
        break;
      }
    }
    tamanhoTour = 0;
    //encontra o numero de posicoes a partir do inicio
    for (i = inicio + 1; i < G->m; i++){
      if(tour[i] != -1){
        tamanhoTour ++;
      }
    }
    //desloca o elementos de tour
    for(i = inicio + tamanhoTour; i != inicio; i--){
      tour[i + tamanhoSubtour] = tour[i];
    }

    //acrescenta o subtour
    for(i = 0; i < tamanhoSubtour; i++){
      tour[inicio + i + 1] = subtour[i];
    }

    //zera o subtour
    for (i = 0; i < G->m; i++){
      subtour[i] = -1;
    }
    tamanhoSubtour = 0;

    //verifica se todas as arestas foram marcadas
    fim = 1;
    for (i = 0; i < NV; i++){
      for (j = 0; j < NV; j++){
        if (G->adj[i][j] != 0){
          fim = 0;
          break;
        }
      }
    }
  } while (fim == 0);

  //imprime Resultado
  printf("Resultado:\n");
  for(i = 0; i < G->m; i++){
    if(tour[i] != 0)
      printf(" %d - ", tour[i]);
  }
}

void Fleury(Grafo G){
  int i, j, NV = G->n;
  int tour[NV], grau[NV], impar = 0, verticeImpar, v, posicaoTour = 1, u, fim = 0, adj, ponte, candidatoU;

  for (i = 0; i < NV; i++){
    grau[i] = 0;
    tour[i] = 0;
  }

  //encontra o numero de vertices de grau impar
  for (i = 0; i < NV; i++){
    for (j = 0; j < NV;j++){
      if (G->adj[i][j] != 0 && i != j){
        grau[i]++;
      }
    }
  }
  for (i = 0; i < NV; i++){
    if (grau[i] % 2 != 0){
      impar ++;
      verticeImpar = i;
    }
  }

  //Verifica se é euleriano ou semi
  if (impar > 2){
    printf(" ERRO: grafo não possui caminho ou ciclo euleriano\n");
  } else {
    if (impar == 2){
      v = verticeImpar;
    } else {
      v = 1;
    }
  }

  tour[0] = v;
  printf("Caminho euleriano:\n");
  printf("%d - ", tour[0]);
  while(fim == 0){
    //encontra u, sendo o proximo adj de v
    adj = 0; ponte = 0;
    for (i = 0; i < NV; i++){
      if (G->adj[v][i] != 0 && v != i){
        adj++;
        candidatoU = i;
        //verifica se v - u é ponte
        ponte = Pontes(G, candidatoU, v);
        if(ponte != -1){
          u = candidatoU;
          break;
        }
      }
    }
    if (adj == 1){
      u = candidatoU;
    }

    tour[posicaoTour] = u;
    printf(" %d - ", tour[posicaoTour]);
    posicaoTour ++;
    G->adj[u][v] = 0;
    G->adj[v][u] = 0;
    fim = 1;
    for (i = 0; i < NV; i++){
      for (j = 0; j < NV; j++){
        if (G->adj[i][j] != 0){
          fim = 0;
          break;
        }
      }
    }
    v = u;
  }
  if (impar != 2){
    printf("%d\n", tour[0]);
  }
  printf("\n");
}
