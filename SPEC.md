# GA-32 architecture specification
## Overview
* 32-bit CPU
* Uses MMIO to communicate with hardwares.
* Big-endian byte order.

## Registers
The CPU features five general-purpose registers, two 32-bit pointers, and a 4-bit flag status register.

| Register | Size   | Description       |
| -------- | ------ | ----------------- |
| A        | 32-bit | General purpose   |
| B        | 32-bit | General purpose   |
| C        | 32-bit | General purpose   |
| D        | 32-bit | General purpose   |
| E        | 32-bit | General purpose   |
| PC       | 32-bit | Program counter   |
| SP       | 32-bit | Stack pointer     |
| Z        | 4-bit  | CPU status        |

Z register (MSB to LSB):
- ZERO
- CARRY
- NEGATIVE
- OVERFLOW

**NOTE:** The Z register isn't directly accessible by the software or program by using regular instructions like `MOVE`. <br>
Instead, they're accessed indirectly (See section **Instructions** for more details).

## Instructions
**Instruction format (2 argument):** `[OP] [destination], [source]` <br>
**Instruction format (1 argument):** `[OP] [source]` <br>
`imm` stands for immediate value (16 bit). <br>
`reg` stands for register (32 bit). <br>
Any instructions that doesn't have **Flags affected** section meaning that it doesn't affect any flags.

Instruction layout: <br>
XXXXXXXXYYYYZZZZIIIIIIIIIIIIIIII <br>
- X: Instruction opcode (8 bits) <br>
- Y: Source register ID (4 bits) <br>
- Z: Destination register ID (4 bits) <br>
- I: Address/imm (16 bits) <br>

### MOV
**Format:** MOV [reg], [imm/reg] <br>
**Opcode:** 0x01 <br>
**Description:** Set [reg] to [imm/reg].
### LOAD
**Format:** LOAD [reg], [imm/reg] <br>
**Opcode:** 0x02 <br>
**Description:** Load value directly from [imm] or the memory address in [reg].
### STORE
**Format:** STORE [reg/imm], [reg] <br>
**Opcode:** 0x03 <br>
**Description:** Store a value from [reg] into the memory address from [reg/imm].
### PUSH
**Format**: PUSH [imm/reg] <br>
**Opcode:** 0x04 <br>
**Description:** Push a value from [imm/reg] into the stack.
### POP
**Format:** POP [reg] <br>
**Opcode:** 0x05 <br>
**Description:** Pop a value from the stack into [reg].
### JMP
**Format:** JMP [imm] <br>
**Opcode:** 0x06 <br>
**Description:** Jump to an address from [imm] unconditionally.
### ADD
**Format:** ADD [reg], [imm/reg] <br>
**Opcode:** 0x07 <br>
**Description:** Add [imm/reg] to [reg] ([reg] + [imm/reg]).
**Flags affected:**
- ZERO: Set if the 32-bit result is exactly 0; otherwise cleared.
- CARRY: Set if the operation exceed unsigned 32-bit limit; otherwise cleared.
- NEGATIVE: Set if bit 31 of the result is set (negative); otherwise cleared.
- OVERFLOW: Set if the operation exceed signed 32-bit limit; otherwise cleared.
### SUB
**Format:** SUB [reg], [imm/reg] <br>
**Opcode:** 0x08 <br>
**Description:** Subtract [imm/reg] from [reg] ([reg] - [imm/reg]).
**Flags affected:**
- ZERO: Set if the 32-bit result is exactly 0; otherwise cleared.
- CARRY: Set if the operation underflow unsigned 32-bit limit; otherwise cleared.
- NEGATIVE: Set if bit 31 of the result is set (negative); otherwise cleared.
- OVERFLOW: Set if the operation underflow signed 32-bit limit; otherwise cleared.
### CALL
**Format:** CALL [imm/reg] <br>
**Opcode:** 0x09 <br>
**Description:** Jump to the address in [imm/reg] and save the current address in the stack.
### RET
**Format:** RET <br>
**Opcode:** 0x0A <br>
**Description:** Return from a **CALL** to the address saved in the stack earlier.
### HLT
**Format:** HLT <br>
**Opcode:** 0x0B <br>
**Description:** Halt current CPU execution.
### NOP
**Format:** NOP <br>
**Opcode:** 0x0C <br>
**Description:** Performs no operation (1 CPU cycle).

## Behaviors
### Reset vector
On reset vector, the CPU read a 32-bit big-endian address from (MSB to LSB):
- 0xFFFFFFF0 (MSB) to 0xFFFFFFF3 (LSB)
Then, the PC will be initialize to the 32-bit value.
Then the stack will be reset to address 0x00FFFFFF.
### Invalid instruction
If the CPU encounter an invalid instruction during execution, it stops execution completely.

## Memory layout
- 0x00000000 - 0x00DFFFFF: General purpose RAM
- 0x00E00000 - 0x00FFFFFF: Stack memory
- 0x10000000 - 0x1000FFFF: MM/IO
- 0xFFFFFFF0 - 0xFFFFFFF3: Reset vector

## Devices MM/IO
- 0x10000000 - 0x100000FF: UART controller
- 0x10000100 - 0x100001FF: Keyboard controller

