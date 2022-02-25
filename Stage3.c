#include "types.h"
#include "user.h"
#include "rect.h"
#include "hdc.h"


int Stage3(int argc, char *argv[]) {
    setvideomode(0x13);
    int forkID = fork();
    if(forkID == 0)
    {
        int hdc = beginpaint(0);
        
        moveto(hdc, 50, 50);

        setpencolour(16, 66, 66, 66);
        setpencolour(17, 255, 1, 20);
        setpencolour(18, 10, 50, 130);
        selectpen(hdc, 17);
        lineto(hdc, 0, 50);
        lineto(hdc, 0, 150);
        lineto(hdc, 50, 150);
        lineto(hdc, 50, 50);
        
        endpaint(hdc);
    }
    else
    {
        int hdc2 = beginpaint(0);
        selectpen(hdc2, 18);
        moveto(hdc2, 100, 50);
        lineto(hdc2, 200, 50);
        lineto(hdc2, 200, 150);
 
        lineto(hdc2, 100, 150);
        lineto(hdc2, 100, 50);
        endpaint(hdc2);
        wait();
    }
    
   
    
    
    
    
    getch();
    setvideomode(0x03);
    exit();
}