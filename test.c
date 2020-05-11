#include <stdio.h>
#include "aes.h"

void test_mix(){
    // test MixColumns
    printf("\n***********test MixColumns:***********\n\nExpected output:\n");
    uint8_t state[16] = {0x87, 0x6e, 0x46, 0xa6, 0xf2, 0x4c, 0xe7, 0x8c, 0x4d, 0x90, 0x4a, 0xd8, 0x97, 0xec, 0xc3, 0x95};
    printf("47 40 a3 4c\n37 d4 70 9f\n94 e4 3a 42\ned a5  a6 bc\n");
    MixColumns(state);
    printf("Mix:\n");
    printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n", state[0], state[4], state[8], state[12], state[1],
           state[5], state[9], state[13], state[2], state[6], state[10], state[14], state[3], state[7], state[11], state[15]);
    printf("inv:\n");
    inv_MixColumns(state);
    printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n", state[0], state[4], state[8], state[12], state[1],
           state[5], state[9], state[13], state[2], state[6], state[10], state[14], state[3], state[7], state[11], state[15]);
}

void test_key_expansion(){
    uint8_t i;
    uint8_t seed[16]  = {0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59, 0x0c, 0xb7, 0xad, 0xd6, 0xaf, 0x7f, 0x67, 0x98};
    word keys[44];
    key_expansion(seed, keys);
    printf("\n***************test key expansion*****************\nexpected output:\nw8:d2 c9 6d b7\noutput:\nw8:");
    for(i = 0;i < 4;i++)printf("%02x ", keys[42][i]);
}

void test_encrypt(){
    uint8_t i;
    uint8_t plaintext[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t seed_key[16] = {0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59, 0x0c, 0xb7, 0xad, 0xd6, 0xaf, 0x7f, 0x67, 0x98};
    printf("\n*****************test encrypt******************\n");
    encrypt(plaintext, seed_key);
    printf("\nencrypted: ");
    for (i = 0;i < 16;i++)printf("%02x", plaintext[i]);
    printf("\n*****************test decrypt******************\n");
    decrypt(plaintext, seed_key);
    printf("\ndecrypted: ");
    for (i = 0;i < 16;i++)printf("%02x", plaintext[i]);
}

int main() {
    // key expansion checked
    test_encrypt();
    return 0;
}
