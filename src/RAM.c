#include "RAM.h"

void read_rom(RAM_t* RAM,char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
    }

    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(RAM->mem + INI_ROM, length, 1 , fp);
    fclose(fp);
}

/*
    uint16_t operation = RAM.mem[INI_ROM] << 8 | RAM.mem[INI_ROM + 1];
    opcode = opcode >> 12;
    printf("%x",opcode);*/

void read_mem(RAM_t *RAM ,uint16_t dir, uint8_t* type, uint8_t *a, uint8_t *b, uint8_t *c) {
    *type = RAM->mem[dir] >> 4;
    *a = (RAM->mem[dir] << 4);
    *a = *a >> 4;

    *b = RAM->mem[dir + 1] >> 4;
    *c = RAM->mem[dir + 1] << 4;
    *c = *c >> 4;
}