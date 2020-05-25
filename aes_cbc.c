//
// Created by 船宝儿 on 2020/5/25.
//

#include "aes.h"
#include <stdio.h>


void aes_cbc_encrypt(uint8_t *plaintext, uint8_t *seed_key, uint8_t *cipher, int length, int padded) {
    uint8_t *IV = getIV();
    uint8_t current[] = {0, 0, 0, 0, 0, 0, 0, 0};

    // key expansion
    word keys[44];
    uint8_t round_key[16];
    key_expansion(seed_key, keys);
    uint8_t i = 0, j = 0, k = 0;

    for (i = 0; i < padded-15; i++) {
        // copy a block
        if (!((i + 1) % 16) ) {
            for (j = i - 15; j != i; j++)current[j - (i - 15)] = plaintext[j];
            // add prev/IV
            add_Round_key(current, IV);
            encrypt(current, seed_key);
            for (j = 0; j < 16; j++)IV[i] = current[i];
            for (j = i - 15; j != i; j++)cipher[j] = current[j - (i - 15)];
        }
        if (i+16 == padded){
            for(j = 0;j < 16;j++){
                if(i+j < length)current[j] = plaintext[i+j];
                else current[j] = (uint8_t)0;
            }
            add_Round_key(current, IV);
            encrypt(current, seed_key);
            for (j = 0; j < 16; j++)cipher[i+j] = current[j];
        }
    }
}