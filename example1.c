#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct Stack {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int value, STK *s) {
    if (s->t < s->scap - 1) {
        s->arr[++(s->t)] = value;
    }
}

int contains(STK *s, int val) {
    for (int i = 0; i <= s->t; i++) {
        if (s->arr[i] == val)
            return 1;
    }
    return 0;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("Adauga %d muchii (noduri de la 0 la %d):\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

int can_be_reached(GPH *g, int a, int b) {
    STK *s = create_s(2 * g->v);
    DFS(g, s, a);
    int found = contains(s, b);
    free(s->arr);
    free(s);
    return found;
}

int main() {
    int nrv, edg_nr;
    int v1, v2;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr, nrv);

    printf("Verificam daca doua restaurante pot fi atinse unul de la celalalt.\n");
    printf("Introdu doua noduri (ex: 0 4): ");
    scanf("%d %d", &v1, &v2);

    if (can_be_reached(g, v1, v2) && can_be_reached(g, v2, v1)) {
        printf("DA! Se poate ajunge din %d in %d si invers.\n", v1, v2);
    } else {
        printf("NU! Nu exista drum dus-intors intre %d si %d.\n", v1, v2);
    }

    return 0;
}
