#include "utils.h"
#include <stddef.h>

void graph_print_adjlist(const Graph* g, FILE* out) {
    if (!g) return;
    if (!out) out = stdout;

    int n = graph_vertex_count(g);

    fprintf(out, "Graph(n=%d, %s)\n", n, graph_is_directed(g) ? "directed" : "undirected");

    for (int v = 0; v < n; v++) {
        size_t deg = graph_degree(g, v);
        const Edge* nbrs = graph_neighbors(g, v);

        fprintf(out, "%d:", v);
        for (size_t i = 0; i < deg; i++) {
            fprintf(out, " (%d,w=%d)", nbrs[i].to, (int)nbrs[i].w);
        }
        fputc('\n', out);
    }
}

void graph_print_dot(const Graph* g, FILE* out) {
    if (!g) return;
    if (!out) out = stdout;

    int directed = graph_is_directed(g);
    int n = graph_vertex_count(g);

    fprintf(out, "%s G {\n", directed ? "digraph" : "graph");
    fprintf(out, "  node [shape=circle];\n");

    // Emit all vertices (helps when isolated vertices exist)
    for (int v = 0; v < n; v++) {
        fprintf(out, "  %d;\n", v);
    }

    const char* op = directed ? "->" : "--";

    for (int v = 0; v < n; v++) {
        size_t deg = graph_degree(g, v);
        const Edge* nbrs = graph_neighbors(g, v);

        for (size_t i = 0; i < deg; i++) {
            int u = nbrs[i].to;
            int w = (int)nbrs[i].w;

            // For undirected graphs, avoid printing each edge twice
            if (!directed && u < v) continue;

            fprintf(out, "  %d %s %d [label=\"%d\"];\n", v, op, u, w);
        }
    }

    fprintf(out, "}\n");
}
