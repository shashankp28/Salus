CXX := g++
CFLAGS := -Wall -Iinc -fPIC -std=c++17 -O3 -lstdc++fs
LDFLAGS := -shared # Linker flags for creating a shared library

# Define the target directory for the object files and the library
OBJDIR := obj
LIBDIR := lib

# List of object files
OBJECTS := $(OBJDIR)/AccessRule.o $(OBJDIR)/HierarchyNode.o $(OBJDIR)/HierarchyStructure.o \
           $(OBJDIR)/PieceOfInformation.o $(OBJDIR)/RuleCollection.o $(OBJDIR)/SalusEngine.o \
           $(OBJDIR)/SalusInterface.o $(OBJDIR)/Logging.o

# The final shared library name
LIBRARY := $(LIBDIR)/libSalus.so

# Default target
all: $(LIBRARY)

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
	rm -f $(OBJDIR)/*.o $(LIBDIR)/*.so

.PHONY: all clean
