mkpath := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkpath)))
hdr := $(current_dir)/Include
src := $(current_dir)/src
objects = $(src)/main.o $(src)/menu.o $(src)/functions.o $(src)/struct.o
enc = -finput-charset=UTF-8 -fexec-charset=cp1251

all: 
	@echo "Building..."
	@cd $(current_dir)/src && $(MAKE) all ohdr=$(hdr)
	@echo "Finishing..."
	@g++ -g $(objects) $(enc) -I $(hdr) -o main
