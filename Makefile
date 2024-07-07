# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable name
EXEC = blackhole_simulator

# Source files
SRCS = main.cpp BehaviorTree.cpp AStar.cpp UCS.cpp GeneticAlgorithm.cpp Graphics.cpp Map.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)
