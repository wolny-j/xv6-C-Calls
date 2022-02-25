#include "types.h"
#include "user.h"
#include "rect.h"
#include "hdc.h"

int Stage2(int argc, char *argv[]) {
    setvideomode(0x13);
    int hdc = beginpaint(0);
    
    
    struct rect r = {100, 100, 150, 250};
    
    setpencolour(16, 63, 63, 63); 
    setpencolour(17, 63, 0, 0);
    
    selectpen(hdc, 17);
    
    fillrect(hdc, &r);
    selectpen(hdc, 16);
    r.top = 50;
    r.left = 100;
    r.bottom = 95;
    r.right = 250;
    fillrect(hdc, &r);
    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}