# Makefile

CPP = g++
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = 
EXEC = run
SOURCES = $(wildcard *.cpp)
OBJ = $(SOURCES:.cpp=.o)

# Compile the program.
kmeans : $(OBJ)
	$(CPP) $(CPPFLAGS) -o kmeans $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

# command to be executed.
clean:
	rm -f $(EXEC) $(OBJ)

