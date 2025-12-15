#pragma once
#include <stdio.h>
#include "graph.h"

// Prints adjacency lists like:
// 0: (1,w=2) (3,w=5)
void graph_print_adjlist(const Graph* g, FILE* out);

// Prints Graphviz DOT so you can render with:
// dot -Tpng graph.dot -o graph.png
void graph_print_dot(const Graph* g, FILE* out);
