OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers


program.exe: program.o Productos.o Ciudad.o Cuenca.o Barco.o
	g++ -o program.exe program.o Productos.o Ciudad.o Cuenca.o Barco.o $(OPCIONS)

Productos.o: Productos.cc Productos.hh
	g++ -c Productos.cc $(OPCIONS)

Ciudad.o: Ciudad.cc Ciudad.hh Productos.hh
	g++ -c Ciudad.cc $(OPCIONS)

Cuenca.o: Cuenca.cc Cuenca.hh Ciudad.hh Barco.hh Productos.hh
	g++ -c Cuenca.cc $(OPCIONS)

Barco.o: Barco.cc Barco.hh
	g++ -c Barco.cc $(OPCIONS)

program.o: program.cc Productos.hh Cuenca.hh 
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe