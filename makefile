CC=gcc				#The c compiler
CPP=g++				#The cpp compiler
LIB_DIR=lib			#The library directory
BIN_DIR=bin	$ 		#The binary directory
CPP_FLAGS=-DDEBUG

vpath %.cpp src		#search here for source files
vpath %.h   include	#search here for include files

app.exe : matrix_base.o simple_matrix.o main.o
	$(CPP) $(CPP_FLAGS) -o app.exe $^

matrix_base.o simple_matrix.o main.o: matrix_base.cpp simple_matrix.cpp main.cpp
	$(CPP) $(CPP_FLAGS) -c  $^
clean:
	@rm *.o *.exe
	@echo "Cleaned!"