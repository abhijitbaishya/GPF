CC=gcc			#The c compiler
CPP=g++			#The cpp compiler
LIB_DIR=lib		#The library directory
BIN_DIR=bin	$ 	#The binary directory

vpath %.cpp src		#search here for source files
vpath %.h   include	#search here for include files

app.exe : matrix_base.o simple_matrix.o main.o
	$(CPP) -o app.exe $^

matrix_base.o simple_matrix.o main.o: matrix_base.cpp simple_matrix.cpp main.cpp
	$(CPP) -c  $^
clean:
	@rm *.o
	@echo "Cleaned!"