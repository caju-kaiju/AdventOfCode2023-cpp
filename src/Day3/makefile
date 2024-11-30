.RECIPEPREFIX = >

CC = g++
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++17

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
BINDIR = $(BUILDDIR)/bin

.PHONY: main
main: setup day3

.PHONY: setup
setup:
> mkdir -p $(OBJDIR)
> mkdir -p $(BINDIR)

.PHONY: clean
clean:
> rm $(OBJDIR)/*
> rm $(BINDIR)/*

DAY3_DEPS = $(OBJDIR)/day3.o
day3: $(DAY3_DEPS)
> $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/day3.o: day3.cpp
> $(CC) $(CFLAGS) -c day3.cpp -o $@

# DAY2PART2_DEPS = $(OBJDIR)/day2_part2.o
# day2_part2: $(DAY2PART2_DEPS)
# > $(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

# $(OBJDIR)/day2_part2.o: day2_part2.cpp
# > $(CC) $(CFLAGS) -c day2_part2.cpp -o $@
