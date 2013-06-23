#The c compiler
CC=gcc
#The cpp compiler
CPP=g++
#The library directory
LIB_DIR=lib
#The binary directory
BIN_DIR=bin
#c++ compiler flags
CPP_FLAGS=-g -c -lm
SRC_LIST=directed_graph.cpp gpf_vector.cpp graph_base.cpp simple_matrix.cpp
#Frame work objects
FW_OBJ=directed_graph.o gpf_vector.o graph_base.o simple_matrix.o

#search here for source file
vpath %.cpp src
#search here for include files
vpath %.h   include

app : MAIN_OBJ FRAMEWORK_OBJ
	$(CPP) -o app main.o $(FW_OBJ)

MAIN_OBJ : main.cpp
	$(CPP) -c $^

#makes the vector class test application
vec : FRAMEWORK_OBJ test/gpf_vector_test.cpp
	$(CPP) -c test/gpf_vector_test.cpp
	$(CPP) -o vec gpf_vector_test.o $(FW_OBJ)

#makes the simple matrix test
simp : FRAMEWORK_OBJ test/simple_matrix_test.cpp
	$(CPP) -c test/simple_matrix_test.cpp
	$(CPP) -o simp $(FW_OBJ) simple_matrix_test.o

#makes the directed graph test
dir : FRAMEWORK_OBJ test/directed_graph_test.cpp
	$(CPP) -c test/directed_graph_test.cpp
	$(CPP) -o dir directed_graph_test.o $(FW_OBJ)
	
#make all the framework objects
FRAMEWORK_OBJ : $(SRC_LIST)
	$(CPP) $(CPP_FLAGS)  $^	

#makes all test and app
all : app vec simp dir

clean:
	@rm -f *.o *.exe 
	@echo
	@echo "All binary files cleaned!"
	@echo "-------------------------"
	
