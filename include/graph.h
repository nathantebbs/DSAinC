#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <stdint.h>

typedef struct Graph Graph;

typedef struct {
    int to;
    int32_t w;
} Edge;

Graph*      graph_create(int n_vertices, int directed);
void        graph_free(Graph* g);
int         graph_vertex_count(const Graph* g);
int         graph_is_directed(const Graph* g);
int         graph_add_edge(Graph* g, int from, int to, int32_t w);
size_t      graph_degree(const Graph* g, int v);
const Edge* graph_neighbors(const Graph* g, int v);

#endif // GRAPH_H
