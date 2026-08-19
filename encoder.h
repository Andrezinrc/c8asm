#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

uint16_t encode_00e0(void);
uint16_t encode_00ee(void);
uint16_t encode_0nnn(uint16_t nnn);
uint16_t encode_1nnn(uint16_t nnn);
uint16_t encode_2nnn(uint16_t nnn);
uint16_t encode_3xkk(uint8_t x, uint8_t kk);
uint16_t encode_4xkk(uint8_t x, uint8_t kk);
uint16_t encode_5xy0(uint8_t x, uint8_t y);
uint16_t encode_6xkk(uint8_t x, uint8_t kk);
uint16_t encode_7xkk(uint8_t x, uint8_t kk);
uint16_t encode_8xy0(uint8_t x, uint8_t y);
uint16_t encode_8xy1(uint8_t x, uint8_t y);
uint16_t encode_8xy2(uint8_t x, uint8_t y);
uint16_t encode_8xy3(uint8_t x, uint8_t y);
uint16_t encode_8xy4(uint8_t x, uint8_t y);
uint16_t encode_8xy5(uint8_t x, uint8_t y);
uint16_t encode_8xy6(uint8_t x, uint8_t y);
uint16_t encode_8xy7(uint8_t x, uint8_t y);
uint16_t encode_8xye(uint8_t x, uint8_t y);
uint16_t encode_9xy0(uint8_t x, uint8_t y);
uint16_t encode_annn(uint16_t nnn);
uint16_t encode_bnnn(uint16_t nnn);
uint16_t encode_cxkk(uint8_t x, uint8_t kk);
uint16_t encode_dxyn(uint8_t x, uint8_t y, uint8_t n);
uint16_t encode_ex9e(uint8_t x);
uint16_t encode_exa1(uint8_t x);
uint16_t encode_fx07(uint8_t x);
uint16_t encode_fx0a(uint8_t x);
uint16_t encode_fx15(uint8_t x);
uint16_t encode_fx18(uint8_t x);
uint16_t encode_fx1e(uint8_t x);
uint16_t encode_fx29(uint8_t x);
uint16_t encode_fx33(uint8_t x);
uint16_t encode_fx55(uint8_t x);
uint16_t encode_fx65(uint8_t x);

#endif
