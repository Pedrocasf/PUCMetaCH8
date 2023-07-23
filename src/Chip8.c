//
// Created by pedro on 17/07/2023.
//

#include "Chip8.h"
const uint16_t MAX_ROM_SIZE = 3584;
const uint8_t ch8_font[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, //1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
        0x90, 0x90, 0xF0, 0x10, 0x10, //4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
        0xF0, 0x10, 0x20, 0x40, 0x40, //7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
        0xF0, 0x90, 0xF0, 0x90, 0x90, //A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
        0xF0, 0x80, 0x80, 0x80, 0xF0, //C
        0xE0, 0x90, 0x90, 0x90, 0xE0, //D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
        0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};
const uint8_t FONT_LEN = 0x50;
const uint16_t MEMORY_SIZE = 0x1000;
const uint8_t STACK_SIZE = 0x10;
const uint8_t REGISTERS_COUNT = 0x10;
void build_ch8_vm_state(Chip8_VM_state** state, char* rom_name){
    *state = (Chip8_VM_state*)calloc(1,sizeof(Chip8_VM_state));
    (*state)->memory = calloc(MEMORY_SIZE, sizeof(uint8_t));
    (*state)->stack = calloc(STACK_SIZE, sizeof(uint16_t));
    (*state)->v = calloc(REGISTERS_COUNT, sizeof(uint8_t));
    void* result = memcpy((*state)->memory, ch8_font, FONT_LEN);
    if (result < 0){
        printf("Failed to copy font, continuing, games might be broken!\n");
    }
    FILE *rom_ptr = NULL;
    rom_ptr = fopen(rom_name, "rb");
    if (rom_ptr == NULL){
        printf("Could not open file '%s'\n",
                  rom_name);
    }else{
        fseek(rom_ptr,0L,SEEK_END);
        uint64_t size = ftell(rom_ptr);
        fseek(rom_ptr, 0L, SEEK_SET);
        if(size <= MAX_ROM_SIZE){
            uint32_t result2 = fread((*state)->memory+512, sizeof(uint8_t), size, rom_ptr);
            if (result2 != size){
                printf("Read file is %d bytes long, but %d bytes were read\n",size, result2);
            }
        }else{
            printf("ROM file too big\n");
        }
        fclose(rom_ptr);
    }
}