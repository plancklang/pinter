Pinter
======

Overview
--------
This file aims to describe completely (with links to other files) the complete
functioning of the Pinter interpreter.

General
-------
Pinter is an interpreter for Planck bytecodes, developed primarily by Adam
Hutchings and Jake Roggenbuck, starting in late 2020. It aims to be fast and
relatively compact in its source code.

Functioning
-----------
The program, when run, will open a given bytecode file and parse its contents
into an array of bytecodes. The program then creates a VM for the bytecodes to
execute on, and starts executing the bytecodes from their starting point. It
exits when there are no more bytecodes left in the array.

The VM
------
The Pinter VM is a large memory space allocated on the heap. The bytecodes
[referencing memory operations](https://github.com/plancklang/pinter/blob/main/doc/bytecodes.md)
will have their effects shown in this memory space. Memory cells start being
filled up from the very beginning of the block, in order.

Function calls / returns
------------------------
With a function call, the desired return location and the current end of the
stack are saved in a stack data structure, and all function arguments are pushed
onto the stack. The executing bytecode is then moved to the start of the called
function.  <br/>
When the function returns, the identified return value is given into the
cell value stored in the VM's call stack, and the stack pointer is moved back to
where it was before the function call.

The beginning and end of execution
----------------------------------
Once all bytecodes are loaded, and the VM has been started, Pinter immediately
commences execution. As arrays are not yet supported, command-line arguments are
not yet possible (although they will be in the future). The first bytecode is
a call to the main function, which resides at the end of the bytecode file.
Therefore, once the last instruction in main is reached, execution ends and
Pinter can exit.
