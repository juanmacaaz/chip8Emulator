#include <stdbool.h>
#include "gfx.h"

#define WIDTH   64
#define HEIGHT  32

#define SCALE   10

struct Display_t
{
    
    bool screen_area [HEIGHT][WIDTH];

} typedef Display_t;

void initDisplay(Display_t *DISPLAY);
void printFrame(Display_t *DISPLAY);