//biblioteca de graphos para n graphos com vértices de 1 à n 
#include <stdio.h>
#include <stdlib.h>

int no_vertices;

struct node{
    int vertex;
    struct node *prox;
};

struct Graph{
    int numVertices;
    struct node **adjLists;
};

struct node *createNode(int v){
    struct node *newNode = malloc(sizeof(struct node));
    newNode-> vertex = v;
    newNode-> prox = NULL;
    return newNode;
}

struct Graph *createAGraph(int vertices){
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph-> numVertices = vertices;
    graph-> adjLists = malloc(vertices * sizeof(struct node*));
    for(int i=0; i<vertices; i++)
        graph-> adjLists[i] = NULL;
    return graph;
}

void addVerticesList(struct Graph *graph, int s, int d){
    struct node *newNode = createNode(d);
    newNode-> prox = graph-> adjLists[s];
    graph-> adjLists[s] = newNode;
    newNode = createNode(s);
    newNode-> prox = graph-> adjLists[d];
    graph-> adjLists[d] = newNode;
}

void printGraphList(struct Graph *graph){
    for(int v=0; v<graph->numVertices; v++){
        struct node *temp = graph-> adjLists[v];
        printf("\nVértice %d: ",v+1);
        while(temp){
            printf("-> %d ", temp-> vertex+1);
            temp = temp-> prox;
        }
    }
}

void init(int adj[no_vertices][no_vertices]){
    for(int i=0; i<no_vertices; i++)
        for(int j=0; j<no_vertices; j++)
            adj[i][j]=0;
}

void addVertices(int adj[no_vertices][no_vertices], FILE *file){
    int s, d;
    while(fscanf(file, "%d %d", &s, &d) != EOF){
        adj[s-1][d-1] = 1;
        adj[d-1][s-1] = 1;
    }
}

/*void newFile(){
    FILE *file = fopen("grafo.txt", "w");
    if(file == NULL){
        printf("erro ao criar arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "5\n");
    fprintf(file, "1 2\n");
    fprintf(file, "2 5\n");
    fprintf(file, "3 5\n");
    fprintf(file, "4 5\n");
    fprintf(file, "5 1\n");
    fclose(file);
}*/

void printGraph(int adj[no_vertices][no_vertices]){
    for(int i = 0; i < no_vertices; i++){
        for(int j = 0; j < no_vertices; j++)
            printf(" %d ", adj[i][j]);
        printf("\n");
    }
}

void bfs(struct Graph *graph, int ini){
    int visited[graph-> numVertices+1], queue[graph-> numVertices+1], front=-1, rear=-1;
    for(int count=0; count<graph-> numVertices; count++)
        visited[count]=0;
    visited[ini] = 1;
    queue[++rear] = ini;
    front ++;
    while(front<=rear){
        int currentVertex = queue[front++];
        printf("%d\t", currentVertex+1);
        struct node *temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->prox;
        }
    }
}

void dfs(struct Graph* graph, int vertex, int *visited) {
    visited[vertex] = 1;
    printf("%d ", vertex+1); 
    struct node *adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            dfs(graph, adjVertex, visited);
        }
        adjList = adjList->prox;
    }
}

int countingArestas(int adj[no_vertices][no_vertices]) {
    int arestas = 0;
    for (int i = 0; i < no_vertices; i++) {
        for (int j = 0; j < no_vertices; j++) {
            if (adj[i][j] == 1) {
                arestas++;
            }
        }
    }

    return arestas/2;
}

void countingGrau(int adj[no_vertices][no_vertices]){
    int graus=0, first;
    FILE *file = fopen("grafo.txt", "r");
    if (file == NULL) {
        printf("erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &no_vertices);
    for (int i = 0; i < no_vertices; i++) {
        for (int j = 0; j < no_vertices; j++) {
            if (adj[i][j] == 1) {
                graus++;
            }
        }
        fscanf(file, "%d %*d", &first);
        printf("\n%d %d", first, graus);  
        graus = 0;
    }
}

void dfsConexos(struct Graph *graph, int v, int *visited, int *component, int *size, int *idx) {
    visited[v] = 1; 
    component[*idx] = v + 1;  
    (*size)++;  
    (*idx)++;  
    struct node* adj = graph->adjLists[v];
    while (adj != NULL) {
        if (!visited[adj->vertex]) {
            dfsConexos(graph, adj->vertex, visited, component, size, idx);
        }
        adj = adj->prox;
    }
}

void components_conexos(struct Graph *graph) {
    int visited[no_vertices];  
    for (int i = 0; i < no_vertices; i++) {
        visited[i] = 0;
    }
    int component[no_vertices];  
    int size;  
    int idx;  
    int num_components = 0;  

    for (int v = 0; v < graph->numVertices; v++) {
        if (!visited[v]) {
            size = 0;
            idx = 0;
            printf("\ncomponente %d: ", ++num_components);
            dfsConexos(graph, v, visited, component, &size, &idx);
            printf("\ntamanho: %d, \nvértices: ", size);
            for (int i = 0; i < size; i++) {
                printf("\n%d ", component[i]);
            }
            printf("\n");
        }
    }
    printf("número total de componentes conexos: %d\n", num_components);
}

int main(){
    //newFile();
    FILE *file = fopen("grafo.txt", "r");
    if (file == NULL) {
        printf("erro ao abrir o arquivo!\n");
        return 1;
    }
    fscanf(file, "%d", &no_vertices);
    int s, d, adj[no_vertices][no_vertices];
    init(adj);
    addVertices(adj, file);
    int m = 0;
    m = countingArestas(adj);
    printf("\n# n = %d", no_vertices);
    printf("\n# m = %d", m);
    countingGrau(adj);
    fclose(file);
    //printGraph(adj);
    
    fopen("grafo.txt", "r");
    if (file == NULL) {
        printf("erro ao abrir o arquivo!\n");
        return 1;
    }
    fscanf(file, "%d", &no_vertices);
    int a, b;
    struct Graph *graph = createAGraph(no_vertices);
    while(fscanf(file, "%d %d", &a, &b) != EOF){
        addVerticesList(graph, a-1, b-1);
    }
    fclose(file);
    //printGraphList(graph);
    
    int ch, inicio;
    
    int* visited = malloc(no_vertices * sizeof(int));
    
    for (int i = 0; i < no_vertices; i++) {
        visited[i] = 0;
    }
    
    //components_conexos(graph);
     
    /*do{
        printf("\nDigite 1 para realizar a busca por largura: ");
        printf("\ndigite 2 para realizar a busca por profundidade: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Digite o vértice pelo qual deseja iniciar: ");
                scanf("%d", &inicio);
                bfs(graph, inicio);
            break;
            case 2:
                printf("Digite o vértice pelo qual deseja iniciar: ");
                scanf("%d", &inicio);
                dfs(graph, inicio, visited);
                free(visited);
                    }
    }while(ch != 3);*/
    
    return 0;
}





