.RECIPEPREFIX = >

CC = g++
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++17

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
BINDIR = $(BUILDDIR)/bin

.PHONY: main
main: setup day1 day1_part2

.PHONY: setup
setup:
> mkdir -p $(OBJDIR)
> mkdir -p $(BINDIR)

.PHONY: clean
clean:
> rm $(OBJDIR)/*
> rm $(BINDIR)/*

DAY1_DEPS = $(OBJDIR)/day1.o
day1: $(DAY1_DEPS)
> $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/day1.o: day1.cpp
> $(CC) $(CFLAGS) -c day1.cpp -o $@

DAY1PART2_DEPS = $(OBJDIR)/day1_part2.o
day1_part2: $(DAY1PART2_DEPS)
> $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/day1_part2.o: day1_part2.cpp
> $(CC) $(CFLAGS) -c day1_part2.cpp -o $@

