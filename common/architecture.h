#pragma once
// Architecture (GA-32)

// Registers ID
#define REG_A   0x01
#define REG_B   0x02
#define REG_C   0x03
#define REG_D   0x04
#define REG_E   0x05
#define REG_PC  0x06
#define REG_SP  0x07
#define REG_IMM 0x08 // Not an actual register

// Instructions opcode
#define OP_MOV   0x01
#define OP_LOAD  0x02
#define OP_STORE 0x03
#define OP_PUSH  0x04
#define OP_POP   0x05
#define OP_JMP   0x06
#define OP_ADD   0x07
#define OP_SUB   0x08
#define OP_CALL  0x09
#define OP_RET   0x0A
#define OP_HLT   0x0B
#define OP_NOP   0x0C
#define OP_MOVU  0x0D


