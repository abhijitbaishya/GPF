CC=gcc			#The c compiler
CPP=g++			#The cpp compiler
LIB_DIR=lib		#The library directory
BIN_DIR=bin	$ 	#The binary directory

vpath %.cpp src		#search here for source files
vpath %.h   include	#search here for include files

matrix_base : matrix_base.cpp
	g++ -c -o $@ $^	#automatic variables are used because sources are not in current directory
					#and without automatic variables make cannot substitute the searched file name
