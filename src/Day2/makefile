.RECIPEPREFIX = >

CC = g++
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++17

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
BINDIR = $(BUILDDIR)/bin

.PHONY: main
main: setup day2 day2_part2

.PHONY: setup
setup:
> mkdir -p $(OBJDIR)
> mkdir -p $(BINDIR)

.PHONY: clean
clean:
> rm $(OBJDIR)/*
> rm $(BINDIR)/*

DAY2_DEPS = $(OBJDIR)/day2.o
day2: $(DAY2_DEPS)
> $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/day2.o: day2.cpp
> $(CC) $(CFLAGS) -c day2.cpp -o $@

DAY2PART2_DEPS = $(OBJDIR)/day2_part2.o
day2_part2: $(DAY2PART2_DEPS)
> $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/day2_part2.o: day2_part2.cpp
> $(CC) $(CFLAGS) -c day2_part2.cpp -o $@

