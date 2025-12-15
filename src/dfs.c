#include "../include/dfs.h"
#include <stdlib.h>
#include <string.h>

size_t dfs_preorder(const Graph* g, int src, int* out) {
    if (!g || !out)
        return 0;

    int n = graph_vertex_count(g);
    if (src < 0 || src >= n)
        return 0;

    unsigned char* visited = (unsigned char*)calloc((size_t)n, 1);
    if (!visited)
        return 0;

    Stack st;
    if (stack_init(&st, 0) != 0) {
        stack_free(&st);
        free(visited);
        return 0;
    }

    if (stack_push(&st, src) != 0) {
        stack_free(&st);
        free(visited);
        return 0;
    }

    size_t k = 0;

    while (!stack_empty(&st)) {
        int v;
        if (stack_pop(&st, &v) != 0)
            break;

        if (visited[v])
            continue;

        visited[v] = 1;
        out[k++]   = v;

        size_t      deg  = graph_degree(g, v);
        const Edge* nbrs = graph_neighbors(g, v);

        for (size_t i = deg; i-- > 0; ) {
            int u                       = nbrs[i].to;
            if (!visited[u]) {
                // If alloc fails, stop early but return what we have
                if (stack_push(&st, u) != 0) {
                    stack_free(&st);
                    free(visited);
                    return k;
                }
            }
        }
    }

    stack_free(&st);
    free(visited);
    return k;
}
