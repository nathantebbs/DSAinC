#include "../include/graph.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    Edge*  data;
    size_t len;
    size_t cap;
} EdgeVec;

struct Graph {
    int      n;
    int      directed;
    EdgeVec* adj;               // length n
};

static int vec_reserve(EdgeVec* v, size_t need_cap) {
    if (v->cap >= need_cap)
        return 0;

    size_t new_cap = (v->cap == 0) ? 4 : v->cap;

    while (new_cap < need_cap) {

        // growing ~2x to guard overflow

        size_t next = new_cap * 2;

        if (next < new_cap)
            return -2;

        new_cap = next;
    }

    Edge* p = (Edge*)realloc(v->data, new_cap * sizeof(Edge));

    if (!p)
        return -2;

    v->data = p;
    v->cap  = new_cap;

    return 0;
}                               // vec_reserve()


static int vec_push(EdgeVec* v, Edge e) {
    if (v->len == v->cap) {
        int rc = vec_reserve(v, v->cap ? (v->cap * 2) : 4);
        if (rc)
            return rc;
    }

    v->data[v->len++] = e;

    return 0;
}                               // vec_push()


static int in_bounds(const Graph* g, int v) {
    return g && v >= 0 && v < g->n;
}                               // in_bounds()


Graph* graph_create(int n_vertices, int directed) {
    if (n_vertices <= 0)
        return NULL;

    Graph* g = (Graph*)calloc(1, sizeof(Graph));
    if (!g)
        return NULL;

    g->n        = n_vertices;
    g->directed = directed ? 1 : 0;

    g->adj = (EdgeVec*)calloc((size_t)g->n, sizeof(EdgeVec));
    if (!g->adj) {
        free(g);
        return NULL;
    }

    return g;
}                               // graph_create()


void graph_free(Graph* g) {
    if (!g)
        return;

    for (int i = 0; i < g->n; ++i) {
        free(g->adj[i].data);
    }
    free(g->adj);
    free(g);
}                               // graph_free()


int graph_vertex_count(const Graph* g) {
    return g ? g->n : 0;
}                               // graph_vertex_count()


int graph_is_directed(const Graph* g) {
    return g ? g->directed : 0;
}                               // graph_is_directed()


int graph_add_edge(Graph* g, int from, int to, int32_t w) {
    if (!in_bounds(g, from) || !in_bounds(g, to))
        return -1;

    int rc = vec_push(&g->adj[from], (Edge){ .to = to, .w = w });
    if (rc)
        return rc;

    if (!g->directed && from != to) {
        rc = vec_push(&g->adj[to], (Edge){ .to = to, .w = w });
        if (rc)
            return rc;
    }

    return 0;
}                               // graph_add_edge()


size_t graph_degree(const Graph* g, int v) {
    if (!in_bounds(g, v))
        return 0;

    return g->adj[v].len;
}                               // graph_degree()


const Edge* graph_neighbors(const Graph* g, int v) {
    if (!in_bounds(g, v))
        return NULL;

    return g->adj[v].data;
}                               // graph_neighbors()
