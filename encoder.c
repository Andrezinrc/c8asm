#include <stdio.h>
#include <stdint.h>

// 00E0
// 00EE
// 1NNN
// 2NNN
// 3XKK
// 4XKK
// 5XY0
// 6XKK
// 7XKK
// 8XY0
// 8XY1
// 8XY2
// 8XY3
// 8XY4
// 8XY5
// 8XY6
// 8XY7
// 8XYE
// 9XY0
// ANNN
// BNNN
// CXKK
// DXYN
// EX9E
// EXA1
// FX07
// FX0A
// FX15
// FX18
// FX1E
// FX29
// FX33
// FX55
// FX65

uint16_t encode_00e0(void)
{
	return 0x00E0;
}
uint16_t encode_00ee(void)
{
	return 0x00EE;
}
uint16_t encode_0nnn(uint16_t nnn)
{
	return 0x0000 | (nnn & 0x0FFF);
}
uint16_t encode_1nnn(uint16_t nnn)
{
	return 0x1000 | (nnn & 0x0FFF);
}
uint16_t encode_2nnn(uint16_t nnn)
{
	return 0x2000 | (nnn & 0x0FFF);
}
uint16_t encode_3xkk(uint8_t x, uint8_t kk)
{
	return 0x3000 | ((uint16_t)x << 8) | kk;
}
uint16_t encode_4xkk(uint8_t x, uint8_t kk)
{
	return 0x4000 | ((uint16_t)x << 8) | kk;
}
uint16_t encode_5xy0(uint8_t x, uint8_t y)
{
	return 0x5000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x0; 
}
uint16_t encode_6xkk(uint8_t x, uint8_t kk)
{
	return 0x6000 | ((uint16_t)x << 8) | kk;
}
uint16_t encode_7xkk(uint8_t x, uint8_t kk)
{
	return 0x7000 | ((uint16_t)x << 8) | kk;
}
uint16_t encode_8xy0(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4);
}
uint16_t encode_8xy1(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x1;
}
uint16_t encode_8xy2(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x2;
}
uint16_t encode_8xy3(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x3;
}
uint16_t encode_8xy4(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x4;
}
uint16_t encode_8xy5(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x5;
}
uint16_t encode_8xy6(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x6;
}
uint16_t encode_8xy7(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0x7;
}
uint16_t encode_8xye(uint8_t x, uint8_t y)
{
	return 0x8000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | 0xE;
}
uint16_t encode_9xy0(uint8_t x, uint8_t y)
{
	return 0x9000 | ((uint16_t)x << 8) | ((uint16_t)y << 4);
}
uint16_t encode_annn(uint16_t nnn)
{
	return 0xA000 | (nnn & 0x0FFF);
}
uint16_t encode_bnnn(uint16_t nnn)
{
	return 0xB000 | (nnn & 0x0FFF);
}
uint16_t encode_cxkk(uint8_t x, uint8_t kk)
{
	return 0xC000 | ((uint16_t)x << 8) | kk;
}
uint16_t encode_dxyn(uint8_t x, uint8_t y, uint8_t n)
{
	return 0xD000 | ((uint16_t)x << 8) | ((uint16_t)y << 4) | n;
}
uint16_t encode_ex9e(uint8_t x)
{
	return 0xE09E | ((uint16_t)x << 8);
}
uint16_t encode_exa1(uint8_t x)
{
	return 0xE0A1 | ((uint16_t)x << 8); 
}
uint16_t encode_fx07(uint8_t x)
{
	return 0xF007 | ((uint16_t)x << 8);
}
uint16_t encode_fx0a(uint8_t x)
{
	return 0xF00A | ((uint16_t)x << 8);
}
uint16_t encode_fx15(uint8_t x)
{
	return 0xF015 | ((uint16_t)x << 8);
}
uint16_t encode_fx18(uint8_t x)
{
	return 0xF018 | ((uint16_t)x << 8);
}
uint16_t encode_fx1e(uint8_t x)
{
	return 0xF01E | ((uint16_t)x << 8);
}
uint16_t encode_fx29(uint8_t x)
{
	return 0xF029 | ((uint16_t)x << 8);
}
uint16_t encode_fx33(uint8_t x)
{
	return 0xF033 | ((uint16_t)x << 8);
}
uint16_t encode_fx55(uint8_t x)
{
	return 0xF055 | ((uint16_t)x << 8);
}
uint16_t encode_fx65(uint8_t x)
{
	return 0xF065 | ((uint16_t)x << 8);
}
