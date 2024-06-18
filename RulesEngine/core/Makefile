# Compiler and linker
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directory containing the source files
SRCDIR = src

# Directory containing the header files
INCDIR = include

# Output directory
BUILDDIR = build

# Output shared library
TARGET = libName.so

# Find all .cpp files in the src directory
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Generate object files for each source file
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link object files to create the shared library
$(TARGET): $(OBJECTS)
	$(CXX) -shared -o $@ $^

# Compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

# Create build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean up build files
clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
