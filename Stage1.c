#include "types.h"
#include "user.h"
#include "rect.h"
#include "hdc.h"

int Stage1(int argc, char *argv[]) {
    setvideomode(0x13);
    int hdc = beginpaint(0);
    
   
    selectpen(hdc, 15);
    setpixel(hdc, 30, 20);
    setpixel(hdc, 33, 20);
    setpixel(hdc, 36, 20);
    moveto(hdc, 100, 50);
    lineto(hdc, 200, 50);
    lineto(hdc, 200, 150);
    lineto(hdc, 100, 150);
    lineto(hdc, 100, 50);
    
    endpaint(hdc);
    
    getch();
    setvideomode(0x03);
    exit();
}