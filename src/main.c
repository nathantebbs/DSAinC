#include "../include/graph.h"
#include "../include/stack.h"
#include "../include/dfs.h"
#include "../include/utils.h"
#include <stdio.h>

static void print_order(const int* out, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%d%s", out[i], (i + 1 == n) ? "\n" : " ");
    }
}

int main(void) {
    Graph* g = graph_create(6, 0);
    if (!g) {
        fprintf(stderr, "graph_create failed\n");
        return 1;
    }

    // edges (feel free to change)
    // component: 0-1-3, 0-2-4-5
    if (graph_add_edge(g, 0, 1, 1) ||
        graph_add_edge(g, 0, 2, 1) ||
        graph_add_edge(g, 1, 3, 1) ||
        graph_add_edge(g, 2, 4, 1) ||
        graph_add_edge(g, 4, 5, 1)) {
        fprintf(stderr, "graph_add_edge failed\n");
        graph_free(g);
        return 1;
    }

    int  n   = graph_vertex_count(g);
    int* out = malloc((size_t)n * sizeof(int));
    if (!out) {
        fprintf(stderr, "malloc failed\n");
        graph_free(g);
        return 1;
    }

    size_t visited = dfs_preorder(g, 0, out);
    printf("DFS preorder from 0 (%zu visited): ", visited);
    print_order(out, visited);

    graph_print_adjlist(g, stdout);
    FILE* fp = fopen("graph.dot", "w");
    if (fp) {
        graph_print_dot(g, fp);
        fclose(fp);
    }

    free(out);
    graph_free(g);
    return 0;
}
