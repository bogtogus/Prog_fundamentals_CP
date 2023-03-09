mkpath := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkpath)))
hdr := $(current_dir)/Include
src := $(current_dir)/src
objects = main.o menu.o functions.o struct.o

all: 
	@echo "Building..."
	@cd $(current_dir)/src && $(MAKE) all ohdr=$(hdr)
	@echo "Finishing..."
	@g++ -g $(objects) -I $(hdr) -o main
