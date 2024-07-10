CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lncurses

# List of object files
OBJS = main.o BehaviorTree.o AStar.o UCS.o GeneticAlgorithm.o Graphics.o Map.o NcursesUtils.o

# Output executable
TARGET = blackhole_simulator

# Build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)
