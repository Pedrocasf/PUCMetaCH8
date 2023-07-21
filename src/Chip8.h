//
// Created by pedro on 17/07/2023.
//

#ifndef PUCMETACH8_CHIP8_H
#define PUCMETACH8_CHIP8_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
typedef struct Chip8_VM_state{
    uint16_t pc;
    uint16_t i;
    uint16_t *stack;
    uint8_t sp;
    uint8_t *v;
    uint8_t *memory;
}Chip8_VM_state;
void build_ch8_vm_state(Chip8_VM_state** state, char* rom_name);
#endif //PUCMETACH8_CHIP8_H
