mkpath := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkpath)))
hdr := $(current_dir)/Include
src := $(current_dir)/src
objects = $(src)/main.o $(src)/menu.o $(src)/functions.o $(src)/struct.o $(src)/sqlite3.o
enc = -finput-charset=UTF-8 -fexec-charset=cp1251

all: exec

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: execdb

exec: 
	@echo "Building..."
	@cd $(current_dir)/src && $(MAKE) all ohdr=$(hdr)
	@echo "Finishing..."
	@g++ -g $(objects) $(enc) -I $(hdr) -o main

execdb: 
	@make -f Makefile clean
	@echo "[Debug] Building..."
	@cd $(current_dir)/src && $(MAKE) debug ohdr=$(hdr)
	@echo "Finishing..."
	@g++ $(CXXFLAGS) $(objects) $(enc) -I $(hdr) -o main
	@make -f Makefile clean

clean:
	rm -rf $(src)/*.o
