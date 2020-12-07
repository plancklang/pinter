Bytecodes
=========

Overview
--------
This file aims to describe the functionality of all bytecodes recognized by the
Pinter interpreter, or the behavior executed by the interpreter when executing
a bytecode with a particular opcode. The bytecodes are referred to by a
four-character string as a mnemonic for their functionality, as well as the hex
code representing each one. This document will then give a description of what
happens upon execution, referring to the left operand as $1 and the right one as
$1.

Bytecode Listing
----------------

NXLL (0x00) <br/>
	- Does nothing.

SETV (0x01) <br/>
	- Sets the value in cell $0 to the value $1.

SETC (0x02) <br/>
	- Sets the value in cell $0 to the value in cell $1.

CADD (0x03) <br/>
	- Adds the value in cell $1 to the value in cell $0, treating both as
	`signed char` type in C.

CSUB (0x04) <br/>
	- Subtracts the value in cell $1 from the value in cell $0, treating both as
	`signed char` type in C.

CMUL (0x05) <br/>
	- Multiplies the value in cell $1 into the value in cell $0, treating both
	as `signed char` type in C.

CDIV (0x06) <br/>
	- Divides the value in cell $0 by the value in cell $1, treating both as
	`signed char` type in C.

Bytecodes 0x07 - 0x0a : IADD, ISUB, IMUL, IDIV <br/>
	- The same as CADD, CSUB, CMUL, CDIV, but the interpreter considers the
	given cells as four-byte `signed int` numbers.

Bytecodes 0x0b - 0x0e : DADD, DSUB, DMUL, DDIV <br/>
	- The same as CADD, CSUB, CMUL, CDIV, but the interpreter considers the
	given cells as eight-byte `signed double` numbers.

CALL (0x10) <br/>
	- Calls the function starting at bytecode $1, and puts the return value into
	cell $0 (and cells following if the return value is larger than one cell)

RTRN (0x11) <br/>
	- Returns from the current function with value $0 ($1 is ignored). If the
	current function is `main`, behaves identically to EXIT.

EXIT (0x12) <br/>
	- Ends the program. Once the VM finishes executing this instruction, no
	other instruction will be executed after.

DREF (0x13) <br/>
	- Puts into $1, and the three following cells, the value in the address
	specified by $0 and the three following cells.
