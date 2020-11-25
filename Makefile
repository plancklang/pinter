# This file is NOT AUTOMATICALLY GENERATED.
# It may be at some point in the future, but not right now.

BIN = bin/

OBJECTS = bin/decode.o \
          bin/main.o \
          bin/parse_args.o

CC = clang -c -I.
LINKER = clang

bin/pinter : $(OBJECTS)
	@$(LINKER) $(OBJECTS) -o bin/pinter

bin/decode.o : src/decode.c src/decode.h src/bytecode/bytecodes.h
	$(CC) src/decode.c -o bin/decode.o

bin/main.o : src/main.c src/parse_args.h src/util.h
	$(CC) src/main.c -o bin/main.o

bin/parse_args.o : src/parse_args.c src/parse_args.h src/util.h
	$(CC) src/parse_args.c -o bin/parse_args.o
