# This file is NOT AUTOMATICALLY GENERATED.
# It may be at some point in the future, but not right now.

BIN = bin/

OBJECTS = bin/behavior.o \
          bin/decode.o \
          bin/main.o \
          bin/parse_args.o \
          bin/types/stack.o \
          bin/vm.o

CC = clang -c -I.
LINKER = clang

bin/pinter : $(OBJECTS)
	@$(LINKER) $(OBJECTS) -o bin/pinter

bin/behavior.o : src/behavior.c src/behavior.h src/types/bytecodes.h src/vm.h
	$(CC) src/behavior.c -o bin/behavior.o

bin/decode.o : src/decode.c src/decode.h src/types/bytecodes.h
	$(CC) src/decode.c -o bin/decode.o

bin/main.o : src/main.c src/parse_args.h src/util.h
	$(CC) src/main.c -o bin/main.o

bin/parse_args.o : src/parse_args.c src/parse_args.h src/util.h
	$(CC) src/parse_args.c -o bin/parse_args.o

bin/types/stack.o : src/types/stack.c src/types/stack.h
	$(CC) src/types/stack.c -o bin/types/stack.o

bin/vm.o : src/vm.c src/vm.h
	$(CC) src/vm.c -o bin/vm.o
