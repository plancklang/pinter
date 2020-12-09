/**
 * This file declares a singular function, which interprets one single bytecode
 * with a handle to a VM.
 *
 * Author: Adam Hutchings
 */

#ifndef PINTER_BEHAVIOR_H
#define PINTER_BEHAVIOR_H

#include <stdint.h> /* int32_t, int64_t */

#include <src/types/bytecodes.h> /* bytecode_t */
#include <src/vm.h> /* pi_vm_t, etc. */

#define PI_INVALID_CODE -1
#define PI_EXECUTION_DONE -2

/**
 * Executes a single bytecode. Returns the status of execution.
 */
int execute_bytecode(pi_vm_t* vm);

#endif /* PINTER_BEHAVIOR_H */
