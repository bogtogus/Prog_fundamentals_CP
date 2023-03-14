objects = main.o menu.o struct.o functions.o 
enc = -finput-charset=UTF-8 -fexec-charset=cp1251

all: main

main: $(objects)
	

main.o: main.cpp $(ohdr)/main.h 
	echo "<...> main.o"
	g++ -c main.cpp $(enc) -I $(ohdr)

menu.o: menu.cpp $(ohdr)/menu.h
	echo "<...> menu.o"
	g++ -c menu.cpp $(enc) -I $(ohdr)

functions.o: functions.cpp $(ohdr)/functions.h
	echo "<...> functions.o"
	g++ -c functions.cpp $(enc) -I $(ohdr)

struct.o: struct.cpp $(ohdr)/struct.h $(ohdr)/functions.h
	echo "<...> struct.o"
	g++ -c struct.cpp $(enc) -I $(ohdr)

