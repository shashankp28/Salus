CXX := g++
CFLAGS := -Wall -Iinc -fPIC -std=c++17 -O3
LDFLAGS := -shared # Linker flags for creating a shared library

# Define the target directory for the object files and the library
OBJDIR := obj
LIBDIR := lib
BINDIR := bin

# List of object files
OBJECTS := $(OBJDIR)/AccessRule.o $(OBJDIR)/HierarchyNode.o $(OBJDIR)/HierarchyStructure.o \
           $(OBJDIR)/PieceOfInformation.o $(OBJDIR)/RuleCollection.o $(OBJDIR)/SalusEngine.o \
           $(OBJDIR)/Logging.o

# The final shared library name
LIBRARY := $(LIBDIR)/libSalus.so

# Run sanity check binary
BINARY := $(BINDIR)/sanity


# Default target
lib: $(BINARY) run_sanity $(LIBRARY)
run_sanity:
	@echo "Running sanity check..."
	@$(BINARY)
	@echo "Sanity check passed."


# Rule to create the sanity check binary
$(BINARY): $(OBJECTS) src/sanity.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ src/sanity.cpp

# Rule to create the shared library
$(LIBRARY): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rules for compiling source files into object files. Includes a check for the obj directory.
$(OBJDIR)/%.o: src/%.cpp inc/%.h
	@mkdir -p $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJDIR)/*.o $(LIBDIR)/*.so $(BINDIR)/*

.PHONY: all clean
