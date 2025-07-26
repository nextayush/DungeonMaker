# ===================================================================================
# Makefile for the Procedural Dungeon Generator Project
#
# This file automates the build process.
#
# Common Commands:
#   make          - Compiles the project and creates the executable.
#   make run      - Compiles if necessary, then runs the program.
#   make clean    - Removes all compiled files (object files and the executable).
# ===================================================================================

# 1. Compiler and Flags
# -----------------------------------------------------------------------------------
# CXX: The C++ compiler to use (g++ is standard on Linux/macOS).
# CXXFLAGS: Flags passed to the compiler.
#   -std=c++11: Use the C++11 standard.
#   -Wall: Enable all compiler warnings (good practice).
#   -Iinclude: Tell the compiler to look for header files in the 'include' directory.
# LDFLAGS: Flags passed to the linker (none needed for this simple project).

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS =

# 2. Directories and Files
# -----------------------------------------------------------------------------------
# Define the directories for source, include, and output files.
IDIR = include
SRCDIR = src
BINDIR = bin

# Automatically find all .cpp source files in the 'src' directory.
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Create a list of object file names (.o) that correspond to each source file.
# These will be placed in the 'bin' directory.
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

# Define the name of the final executable file.
EXECUTABLE = $(BINDIR)/dungeon

# 3. Build Rules (Targets)
# -----------------------------------------------------------------------------------

# The 'all' target is the default. Typing 'make' will execute this rule.
# It depends on the final executable, so it will trigger the linking process.
# The .PHONY directive tells make that 'all' is not a real file.
.PHONY: all
all: $(EXECUTABLE)

# Rule to link all the object files (.o) into the final executable.
# $@ is an automatic variable representing the target name (the executable).
# $^ is an automatic variable representing all the dependencies (the object files).
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR) # Create the bin directory if it doesn't exist
	$(CXX) $(LDFLAGS) -o $@ $^
	@echo "Linking complete. Executable created at $(EXECUTABLE)"

# Pattern rule to compile each .cpp source file into a .o object file.
# $< is an automatic variable representing the first dependency (the .cpp file).
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR) # Create the bin directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo "Compiled $< into $@"

# The 'run' target compiles the project and then runs it.
# It depends on 'all' to ensure the project is built first.
.PHONY: run
run: all
	./$(EXECUTABLE)

# The 'clean' target removes all compiled files.
# This is useful for starting a fresh build.
.PHONY: clean
clean:
	@rm -rf $(BINDIR)
	@echo "Cleaned project directory. All compiled files removed."

