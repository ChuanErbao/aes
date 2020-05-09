//
// Created by 船宝儿 on 2020/5/9.
//

#include "aes.h"

// key_length:128, 192, 256
// block_length: 128
// irreducible polynomial: m(x) = x^8 + x^4 + x^3 + x + 1

static void add(uint8_t c, uint8_t a, uint8_t b){
    c = a^b;
}

static void mul(uint8_t c, uint8_t a, uint8_t b){
    while (b > 1){
        if(a & 0x80){
            add(c, c, (a<<1)^0x1b);
        }
        else{
            add(c, c, a<<1);
        }
        b -= 2;
    }
    if(b == 1){
        add(c, c, a);
    }
}

static void AddRoundKey(uint8_t *state, uint8_t *round_key){

}

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


static void MixColumns(uint8_t *state){

}


