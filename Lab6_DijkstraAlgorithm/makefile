all: Main

# Define the dependencies
Main: Main.o
	-o Main Main.o
	
Main.o: Main.cpp Vertex.h Edge.h
 	-std=c++0x -c Main.cpp 
###
clean:
	/bin/rm -f Main Main.o	