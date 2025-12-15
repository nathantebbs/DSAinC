CC     := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -O2 -g

INCDIR := include
SRCDIR := src
OBJDIR := build
BIN    := main

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean graph

all: $(BIN)

graph: $(BIN)
	dot -Tpng graph.dot -o graph.png

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(BIN)
