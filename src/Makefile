objects = main.o menu.o struct.o functions.o 

all: main

main: $(objects)
	

main.o: main.cpp $(ohdr)/main.h 
	echo "<...> main.o"
	g++ -c main.cpp -I $(ohdr)

menu.o: menu.cpp $(ohdr)/menu.h
	echo "<...> menu.o"
	g++ -c menu.cpp -I $(ohdr)

functions.o: functions.cpp $(ohdr)/functions.h
	echo "<...> functions.o"
	g++ -c functions.cpp -I $(ohdr)

struct.o: struct.cpp $(ohdr)/struct.h $(ohdr)/functions.h
	echo "<...> struct.o"
	g++ -c struct.cpp -I $(ohdr)

