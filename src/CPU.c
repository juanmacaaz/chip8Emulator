#include "CPU.h"

void initCPU(CPU_t* CPU) {
    CPU->I  = 0x0;
    CPU->PC = INI_ROM;
    CPU->SP = 0;

    for (int i = 0; i < MAX_REG; i++)
        CPU->SR[i] = 0x0;
    
    for (int i = 0; i < MAX_REG; i++)
        CPU->Vx[i] = 0x0;

    srand(time(NULL)); 
}

void runCPU(CPU_t *CPU, RAM_t *RAM, Display_t *DISPLAY) {
    uint8_t type, a , b, c;
    while(1){
        read_mem(RAM , CPU->PC, &type, &a, &b, &c);
        //printf("PC --> %x\n", CPU->PC);
        CPU->PC += 2;
        exeOPC(CPU, RAM ,DISPLAY ,type, a, b, c);
        usleep(100);
        //printFrame(DISPLAY);
        /*
        printf("OP --> %x%x%x%x\n", type, a , b, c);
        printf("PC --> %x\n", CPU->PC);
        printf("SP --> %x\n", CPU->SP);
        printf("I --> %x\n", CPU->I);
        for(int i = 0; i < 16; i++) {
            printf(" V%i-->%x ||", i, CPU->Vx[i]);
        }
        printf("\n");
        for(int i = 0; i < 16; i++) {
            printf(" SR%i-->%x ||", i, CPU->SR[i]);
        }
        printf("\n");
        
        for(int y = 0; y < HEIGHT; y++) {
            for(int x = 0; x < WIDTH; x++) {
                if(DISPLAY->screen_area[y][x] == 1) {
                    printf("X ");
                }else {
                    printf("  ");
                }
            }
            printf("\n");
        }
        printf("\n");
        */
    }
}

void exeOPC(CPU_t *CPU, RAM_t *RAM, Display_t *DISPLAY,uint8_t type, uint8_t a, uint8_t b, uint8_t c) {
    switch (type)
    {
    case 0: if (c == 0) {clsDisplay(DISPLAY);} else {CPU->PC = CPU->SR[CPU->SP]; CPU->SP--;}        break;
    case 1: CPU->PC = concat3Bits(a, b, c);                                     break;
    case 2: CPU->SP++; CPU->SR[CPU->SP] = CPU->PC; CPU->PC = concat3Bits(a,b,c);    break;
    case 3: if (CPU->Vx[a] == concat2Bits(b,c)) { CPU->PC+=2; }         break;
    case 4: if (CPU->Vx[a] != concat2Bits(b,c)) { CPU->PC+=2; }         break;
    case 5: if (CPU->Vx[a] != CPU->Vx[b])       { CPU->PC+=2; }         break;
    case 6: CPU->Vx[a] = concat2Bits(b,c);                              break;
    case 7: CPU->Vx[a] += concat2Bits(b,c);                             break;
    case 8:
        switch (c)
        {
        case 0: CPU->Vx[a] = CPU->Vx[b];              break;
        case 1: CPU->Vx[a] = CPU->Vx[a] | CPU->Vx[b]; break;
        case 2: CPU->Vx[a] = CPU->Vx[a] & CPU->Vx[b]; break;
        case 3: CPU->Vx[a] = CPU->Vx[a] ^ CPU->Vx[b]; break;
        case 4: CPU->Vx[a] = CPU->Vx[a] + CPU->Vx[b]; if(CPU->Vx[a] + CPU->Vx[b] > 255) {CPU->Vx[0xF] = 1;} else {CPU->Vx[0xF] = 0;} break;
        case 5: CPU->Vx[a] = CPU->Vx[a] - CPU->Vx[b]; if(CPU->Vx[a] > CPU->Vx[b])       {CPU->Vx[0xF] = 0;} else {CPU->Vx[0xF] = 1;} break;
        case 6: {
            uint8_t tmp = CPU->Vx[a] & 1;
            if (tmp == 1) {
                CPU->Vx[0xF] = 1;
            }else {
                CPU->Vx[0xF] = 0;
            } 
            CPU->Vx[a] = CPU->Vx[a] >> 1;
            break;
        }
        case 7: 
            CPU->Vx[a] = CPU->Vx[b] - CPU->Vx[a]; 
            if(CPU->Vx[b] > CPU->Vx[a]){
                CPU->Vx[0xF] = 0;
            } else {
                CPU->Vx[0xF] = 1;
            } 
            break;
        case 0xE: 
            uint8_t tmp = CPU->Vx[a] & 128;
            if (tmp != 0) {
                CPU->Vx[0xF] = 1;
            }else {
                CPU->Vx[0xF] = 0;
            } 
            CPU->Vx[a] = CPU->Vx[a] << 1;
            break;
        }
        break;
    case 9: if (CPU->Vx[a] != CPU->Vx[b]) {CPU->PC+=2;} break;
    case 0xA: CPU->I = concat3Bits(a, b, c); break;
    case 0xB: CPU->PC = concat3Bits(a,b,c) + CPU->Vx[0]; break; 
    case 0xC: CPU->Vx[a] = rand() & concat2Bits(b,c); break;
    case 0xD: 
        CPU->Vx[0xF] = 0;
        for(int j = 0; j < c; j++) {
            uint8_t sprite = RAM->mem[CPU->I + j];
            for(int i = 0; i < 8; i++){
                int px = (CPU->Vx[a] + i) & 63;
                int py = (CPU->Vx[b] + j) & 31;
                int pixel = (sprite & (1 << (7-i))) != 0;
                CPU->Vx[0xF] |= (DISPLAY->screen_area[py][px] & pixel);
                DISPLAY->screen_area[py][px] ^= pixel;
            }
        }
        printFrame(DISPLAY);
    break;
    default:
        break;
    }
}

uint8_t concat2Bits(uint8_t a, uint8_t b) {
    a = a << 4;
    return b | a;
}

uint16_t concat3Bits(uint8_t a, uint8_t b, uint8_t c) {
    uint16_t tmp = a << 8;
    b = b << 4;
    return tmp | b | c;
}