#include "emitter.h"
#include "assembler.h"
#include "parser.h"
#include "encoder.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void emit_instruction(uint16_t op)
{
    // An instruction occupies two bytes in the chip8 rom
    if ((state.pc - ROM_START_ADDRESS) + 1 >= MAX_ROM_SIZE) {
        fprintf(stderr, "[ERROR] ROM limit exceeded.\n");
        exit(1);
    }

	// The emulator later joins these two bytes back into one 16-bit opcode
    state.rom[state.pc - ROM_START_ADDRESS] = (op >> 8) & 0xFF;
    state.rom[state.pc - ROM_START_ADDRESS + 1] = op & 0xFF;
    state.pc += 2;
}

void emit_byte(uint8_t byte)
{
    if (state.pc - ROM_START_ADDRESS >= MAX_ROM_SIZE) {
        fprintf(stderr, "[ERROR] ROM limit exceeded.\n");
        exit(1);
    }
    state.rom[state.pc - ROM_START_ADDRESS] = byte;
    state.pc += 1;
}


// Instruction Handles
// Each handler turns parsed operands into the 16-bit layout expected
// by the chip8 CPU, then leaves byte emission to emit_instruction()

void handle_cls(FILE *src, const char *mnemonic)
{
    (void)src; (void)mnemonic;
    emit_instruction(encode_00e0());
}

void handle_ret(FILE *src, const char *mnemonic)
{
    (void)src; (void)mnemonic;
    emit_instruction(encode_00ee());
}

void handle_sys(FILE *src, const char *mnemonic)
{
    (void)mnemonic;
    char op[32];
    get_operand(src, op, sizeof(op));
    emit_instruction(encode_0nnn(resolve_address(op)));
}

void handle_jp(FILE *src, const char *mnemonic)
{
    (void)mnemonic;
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));

    if (strcmp(op1, "v0") == 0) {
        get_operand(src, op2, sizeof(op2));
        emit_instruction(encode_bnnn(resolve_address(op2)));
    } else {
        emit_instruction(encode_1nnn(resolve_address(op1)));
    }
}

void handle_call(FILE *src, const char *mnemonic)
{
    (void)mnemonic;
    char op[32];
    get_operand(src, op, sizeof(op));
    emit_instruction(encode_2nnn(resolve_address(op)));
}

void handle_se_sne(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));
    
    if (!IS_REG(op1))
        error_invalid_reg(mnemonic);
    int regX = PARSE_REG(op1);

    if (IS_REG(op2)) {
        int regY = PARSE_REG(op2);

		// Register form: 5XY0 / 9XY0
        if (strcmp(mnemonic, "se") == 0)
			emit_instruction(encode_5xy0(regX, regY));
		else
			emit_instruction(encode_9xy0(regX, regY));
    } else {
		// Immediate form: 3XKK / 4XKK
        uint8_t val = (uint8_t)strtol(op2, NULL, 0);
        if (strcmp(mnemonic, "se") == 0)
			emit_instruction(encode_3xkk(regX, val));
		else
			emit_instruction(encode_4xkk(regX, val));
    }
}

void handle_skp_sknp(FILE *src, const char *mnemonic)
{
    char op[32];
    get_operand(src, op, sizeof(op));
    if (!IS_REG(op))
        error_invalid_reg(mnemonic);
    
    int regX = PARSE_REG(op);

	// EX9E skips on key press; EXA1 skips when the key is not pressed
    if (strcmp(mnemonic, "skp") == 0)
		emit_instruction(encode_ex9e(regX));
	else
		emit_instruction(encode_exa1(regX));
}

void handle_ld(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));

    if (strcmp(op1, "i") == 0) {
        emit_instruction(encode_annn(resolve_address(op2)));
        return;
    }
    if (strcmp(op1, "dt") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
		int regX = PARSE_REG(op2);
        emit_instruction(encode_fx15(regX));
        return;
    }
    if (strcmp(op1, "st") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
        int regX = PARSE_REG(op2);
		emit_instruction(encode_fx18(regX));
        return;
    }
    if (strcmp(op1, "f") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
		int regX = PARSE_REG(op2);
        emit_instruction(encode_fx29(regX));
        return;
    }
    if (strcmp(op1, "b") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
		int regX = PARSE_REG(op2);
        emit_instruction(encode_fx33(regX));
        return;
    }
    if (strcmp(op1, "[i]") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
		int regX = PARSE_REG(op2);
        emit_instruction(encode_fx55(regX));
        return;
    }

    if (!IS_REG(op1))
        error_invalid_reg(mnemonic);
    int regX = PARSE_REG(op1);
	uint8_t val = (uint8_t)strtol(op2, NULL, 0);

    if      (strcmp(op2, "dt")  == 0)
        emit_instruction(encode_fx07(regX));
    else if (strcmp(op2, "k")   == 0)
        emit_instruction(encode_fx0a(regX));
    else if (strcmp(op2, "[i]") == 0)
        emit_instruction(encode_fx65(regX));
    else if (IS_REG(op2))
        emit_instruction(encode_8xy0(regX, PARSE_REG(op2)));
    else
        emit_instruction(encode_6xkk(regX, val));
}

void handle_add(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));

    if (strcmp(op1, "i") == 0) {
        if (!IS_REG(op2))
            error_invalid_reg(mnemonic);
        emit_instruction(encode_fx1e(PARSE_REG(op2)));
        return;
    }

    if (!IS_REG(op1))
        error_invalid_reg(mnemonic);
    int regX = PARSE_REG(op1);
	uint8_t val = (uint8_t)strtol(op2, NULL, 0);

    if (IS_REG(op2))
        emit_instruction(encode_8xy4(regX, PARSE_REG(op2))); 
    else
        emit_instruction(encode_7xkk(regX, val));
}

void handle_alu(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));

    if (!IS_REG(op1) || (!IS_REG(op2) && op2[0] != '\0'))
        error_invalid_reg(mnemonic);
    
    int regX = PARSE_REG(op1);
	// Shifts may omit the 2nd operand; use regX as the source
    int regY = (op2[0] != '\0') ? PARSE_REG(op2) : regX;

	//uint16_t suffix = 0;
    if      (strcmp(mnemonic, "or")   == 0)
        emit_instruction(encode_8xy1(regX, regY));
    else if (strcmp(mnemonic, "and")  == 0)
        emit_instruction(encode_8xy2(regX, regY));
    else if (strcmp(mnemonic, "xor")  == 0)
        emit_instruction(encode_8xy3(regX, regY));
    else if (strcmp(mnemonic, "sub")  == 0)
        emit_instruction(encode_8xy5(regX, regY));
    else if (strcmp(mnemonic, "shr")  == 0)
        emit_instruction(encode_8xy6(regX, regY));
    else if (strcmp(mnemonic, "subn") == 0)
        emit_instruction(encode_8xy7(regX, regY));
    else if (strcmp(mnemonic, "shl")  == 0)
        emit_instruction(encode_8xye(regX, regY));

    //emit_instruction(0x8000 | (regX << 8) | (regY << 4) | suffix);
}

void handle_rnd(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));
    
    if (!IS_REG(op1))
        error_invalid_reg(mnemonic);
    int regX = PARSE_REG(op1);
    
    uint8_t val = (uint8_t)strtol(op2, NULL, 0);
    emit_instruction(encode_cxkk(regX, val));
}

void handle_drw(FILE *src, const char *mnemonic)
{
    char op1[32], op2[32], op3[32];
    get_operand(src, op1, sizeof(op1));
    get_operand(src, op2, sizeof(op2));
    get_operand(src, op3, sizeof(op3));

    if (!IS_REG(op1) || !IS_REG(op2))
        error_invalid_reg(mnemonic);
    
    int regX = PARSE_REG(op1);
    int regY = PARSE_REG(op2);

    uint8_t nibble = (uint8_t)strtol(op3, NULL, 0) & 0x0F;
    emit_instruction(encode_dxyn(regX, regY, nibble));
}
