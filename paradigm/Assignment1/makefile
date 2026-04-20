CXX = g++
CXXFLAGS = -Wall

all: program

array_mod.o: array_mod.cpp array_mod.h
	$(CXX) $(CXXFLAGS) -c array_mod.cpp

string_mod.o: string_mod.cpp string_mod.h
	$(CXX) $(CXXFLAGS) -c string_mod.cpp

lib_array_mod.a: array_mod.o
	ar rcs lib_array_mod.a array_mod.o

lib_string_mod.a: string_mod.o
	ar rcs lib_string_mod.a string_mod.o

program: client_code_Split_modules.cpp lib_array_mod.a lib_string_mod.a
	$(CXX) client_code_Split_modules.cpp -L. lib_array_mod.a lib_string_mod.a -o clientExecutable

clean:
	rm -f *.o *.a clientExecutable
