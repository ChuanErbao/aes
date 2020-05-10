//
// Created by 船宝儿 on 2020/5/9.
//

#include "aes.h"

// key_length:128, 192, 256
// block_length: 128
// irreducible polynomial: m(x) = x^8 + x^4 + x^3 + x + 1

/*
 * use in MixColumns;
 * in GF(2^8):
 * addition is the bitwise XOR operation;
 * multiplication of a value by {02} can be implemented as a 1-bit left shift  followed
 * by a conditional bitwise XOR with (0001 1011) if the leftmost bit is 1
 */
uint8_t mul(uint8_t scalar, uint8_t s){
    uint8_t p = 0, i = 0, hbs = 0;
    for (i = 0; i < 8; i++) {
        if (scalar & 1) {
            p ^= s;
        }
        hbs = s & 0x80;
        s <<= 1;
        if (hbs) s ^= 0x1b; // 0000 0001 0001 1011
        scalar >>= 1;
    }
    return (uint8_t)p;
}
//
//static void AddRoundKey(uint8_t *state, uint8_t *round_key){
//
//}

/*
 * the leftmost 4 bits of the byte are used as a row value
 * the rightmost 4 bits are used as a column value
 */
static void substitute(uint8_t *state, int inv){
    int i;
    for(i = 0;i < 16;i++){
        //row
        unsigned row = state[i] >> 4;
        //col
        unsigned col = state[i] & 0x0f;
        if(!inv)state[i] = s_box[row*16+col];
        else state[i] = inv_s_box[row*16+col];
    }
}

/*
 * the shift row transformation is more substantial than it may first appear;
 * this is because the State is treated as an array of four 4-byte columns;
 * Furthermore, the round key is applied to State column by column;
 * so, shift row make a difference;
 * 使原来单列中的4byte分布到了4列中
 */
static void ShiftRows(uint8_t *state){
    // 这里没想到好的方法
    uint8_t temp[16];
    uint8_t i;
    temp[0] = state[0];
    temp[1] = state[5];
    temp[2] = state[10];
    temp[3] = state[15];
    temp[4] = state[4];
    temp[5] = state[9];
    temp[6] = state[14];
    temp[7] = state[3];
    temp[8] = state[8];
    temp[9] = state[13];
    temp[10] = state[2];
    temp[11] = state[7];
    temp[12] = state[12];
    temp[13] = state[1];
    temp[14] = state[6];
    temp[15] = state[11];
    for(i = 0;i < 16;i++)state[i] = temp[i];
}

static void inv_ShiftRows(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = state[0];
    temp[1] = state[13];
    temp[2] = state[10];
    temp[3] = state[7];
    temp[4] = state[4];
    temp[5] = state[1];
    temp[6] = state[14];
    temp[7] = state[11];
    temp[8] = state[8];
    temp[9] = state[5];
    temp[10] = state[2];
    temp[11] = state[15];
    temp[12] = state[12];
    temp[13] = state[9];
    temp[14] = state[6];
    temp[15] = state[3];
    for(i = 0;i < 16;i++)state[i] = temp[i];
}


void MixColumns(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = mul(2, state[0]) ^ mul(3, state[1]) ^ state[2] ^ state[3];
    temp[1] = state[0] ^ mul(2, state[1]) ^ mul(3, state[2]) ^ state[3];
    temp[2] = state[0] ^ state[1] ^ mul(2, state[2]) ^ mul(3, state[3]);
    temp[3] = mul(3, state[0]) ^ state[1] ^ state[2] ^ mul(2, state[3]);
    temp[4] = mul(2, state[4]) ^ mul(3, state[5]) ^ state[6] ^ state[7];
    temp[5] = state[4] ^ mul(2, state[5]) ^ mul(3, state[6]) ^ state[7];
    temp[6] = state[4] ^ state[5] ^ mul(2, state[6]) ^ mul(3, state[7]);
    temp[7] = mul(3, state[4]) ^ state[5] ^ state[6] ^ mul(2, state[7]);
    temp[8] = mul(2, state[8]) ^ mul(3, state[9]) ^ state[10] ^ state[11];
    temp[9] = state[8] ^ mul(2, state[9]) ^ mul(3, state[10]) ^ state[11];
    temp[10] = state[8] ^ state[9] ^ mul(2, state[10]) ^ mul(3, state[11]);
    temp[11] = mul(3, state[8]) ^ state[9] ^ state[10] ^ mul(2, state[11]);
    temp[12] = mul(2, state[12]) ^ mul(3, state[13]) ^ state[14] ^ state[15];
    temp[13] = state[12] ^ mul(2, state[13]) ^ mul(3, state[14]) ^ state[15];
    temp[14] = state[12] ^ state[13] ^ mul(2, state[14]) ^ mul(3, state[15]);
    temp[15] = mul(3, state[12]) ^ state[13] ^ state[14] ^ mul(2, state[15]);
    for(i = 0;i < 16;i++)state[i] = temp[i];
}

void inv_MixColumns(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = mul(0x0e, state[0]) ^ mul(0x0b, state[1]) ^ mul(0x0d, state[2]) ^ mul(0x09, state[3]);
    temp[4] = mul(0x0e, state[4]) ^ mul(0x0b, state[5]) ^ mul(0x0d, state[6]) ^ mul(0x09, state[7]);
    temp[8] = mul(0x0e, state[8]) ^ mul(0x0b, state[9]) ^ mul(0x0d, state[10]) ^ mul(0x09, state[11]);
    temp[12] = mul(0x0e, state[12]) ^ mul(0x0b, state[13]) ^ mul(0x0d, state[14]) ^ mul(0x09, state[15]);
    temp[1] = mul(0x09, state[0]) ^ mul(0x0e, state[1]) ^ mul(0x0b, state[2]) ^ mul(0x0d, state[3]);
    temp[5] = mul(0x09, state[4]) ^ mul(0x0e, state[5]) ^ mul(0x0b, state[6]) ^ mul(0x0d, state[7]);
    temp[9] = mul(0x09, state[8]) ^ mul(0x0e, state[9]) ^ mul(0x0b, state[10]) ^ mul(0x0d, state[11]);
    temp[13] = mul(0x09, state[12]) ^ mul(0x0e, state[13]) ^ mul(0x0b, state[14]) ^ mul(0x0d, state[15]);
    temp[2] = mul(0x0d, state[0]) ^ mul(0x09, state[1]) ^ mul(0x0e, state[2]) ^ mul(0x0b, state[3]);
    temp[6] = mul(0x0d, state[4]) ^ mul(0x09, state[5]) ^ mul(0x0e, state[6]) ^ mul(0x0b, state[7]);
    temp[10] = mul(0x0d, state[8]) ^ mul(0x09, state[9]) ^ mul(0x0e, state[10]) ^ mul(0x0b, state[11]);
    temp[14] = mul(0x0d, state[12]) ^ mul(0x09, state[13]) ^ mul(0x0e, state[14]) ^ mul(0x0b, state[15]);
    temp[3] = mul(0x0b, state[0]) ^ mul(0x0d, state[1]) ^ mul(0x09, state[2]) ^ mul(0x0e, state[3]);
    temp[7] = mul(0x0b, state[4]) ^ mul(0x0d, state[5]) ^ mul(  0x09, state[6]) ^ mul(0x0e, state[7]);
    temp[11] = mul(0x0b, state[8]) ^ mul(0x0d, state[9]) ^ mul(0x09, state[10]) ^ mul(0x0e, state[11]);
    temp[15] = mul(0x0b, state[12]) ^ mul(0x0d, state[13]) ^ mul(0x09, state[14]) ^ mul(0x0e, state[15]);
    for(i = 0;i < 16;i++)state[i] = temp[i];
}


