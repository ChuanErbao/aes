#include <stdio.h>
#include "aes.h"

int main() {
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
    return 0;
}
