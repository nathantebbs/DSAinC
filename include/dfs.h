#pragma once
#include <stddef.h>
#include "graph.h"
#include "stack.h"

size_t dfs_preorder(const Graph* g, int src, int* out);
