#include <stdint.h>
#include <stdio.h>

#define MAX_MEM 4096
#define INI_ROM 0x200

struct RAM_t
{

    uint8_t mem [MAX_MEM];  // Memoria RAM virtual
    
} typedef RAM_t;

void read_rom(RAM_t*,char *file);
void read_mem(RAM_t*,uint16_t dir, uint8_t* type, uint8_t *a, uint8_t *b, uint8_t *c);