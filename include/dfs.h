#ifndef DFS_H
#define DFS_H

#include <stddef.h>
#include "graph.h"
#include "stack.h"

size_t dfs_preorder(const Graph* g, int src, int* out);

#endif // DFS_H
