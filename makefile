#The c compiler
CC=gcc
#The cpp compiler
CPP=g++
#The library directory
LIB_DIR=lib
#The binary directory
BIN_DIR=bin
#c++ compiler flags
CPP_FLAGS=-g
#source file list
SRC_LIST=directed_graph.cpp gpf_vector.cpp graph_base.cpp simple_matrix.cpp main.cpp

#search here for source file
vpath %.cpp src
#search here for include files
vpath %.h   include

app.exe : directed_graph.o graph_base.o gpf_vector.o simple_matrix.o main.o
	$(CPP) $(CPP_FLAGS) -o app.exe $^

matrix_base.o simple_matrix.o main.o: $(SRC_LIST)
	$(CPP) $(CPP_FLAGS) -c  $^
clean:
	@rm *.o *.exe 
	@echo "Cleaned!"