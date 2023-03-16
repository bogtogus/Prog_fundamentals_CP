objects = main.o menu.o struct.o functions.o sqlite3.o
enc = -finput-charset=UTF-8 -fexec-charset=cp1251

all: main

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: main

main: $(objects)
	

main.o: main.cpp $(ohdr)/main.h $(ohdr)/menu.h $(ohdr)/struct.h $(ohdr)/functions.h
	@echo "<...> main.o"
	@g++ $(CXXFLAGS) -c main.cpp $(enc) -I $(ohdr)

menu.o: menu.cpp $(ohdr)/menu.h $(ohdr)/main.h $(ohdr)/struct.h $(ohdr)/functions.h
	@echo "<...> menu.o"
	@g++ $(CXXFLAGS) -c menu.cpp $(enc) -I $(ohdr)

functions.o: functions.cpp $(ohdr)/functions.h $(ohdr)/main.h $(ohdr)/struct.h
	@echo "<...> functions.o"
	@g++ $(CXXFLAGS) -c functions.cpp $(enc) -I $(ohdr)

struct.o: struct.cpp $(ohdr)/struct.h $(ohdr)/main.h $(ohdr)/functions.h
	@echo "<...> struct.o"
	@g++ $(CXXFLAGS) -c struct.cpp $(enc) -I $(ohdr)

sqlite3.o: sqlite3.c $(ohdr)/sqlite3.h
	@echo "<...> sqlite"
	@gcc $(CXXFLAGS) -c sqlite3.c $(enc) -I $(ohdr)
