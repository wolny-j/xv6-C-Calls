#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "x86.h"
#include "rect.h"
#include "hdc.h"
#include "spinlock.h"


int movX;
int movY;
int pen;
struct hdc hdcList[100];
int counter = 0;
/*static struct
{
    struct spinlock lock;
    int locking;
}cons;*/


void clear320x200x256() {
	// You need to put code to clear the video buffer here.  Initially, 
	// you might just set each pixel to black in a nested loop, but think
	// about faster ways to do it. 
	//
	// This function is called from videosetmode.
	uchar *VGA=(uchar*)P2V(0xA0000);
	for(int x = 0; x < 320; x++)
	{
		for(int y = 0; y < 200; y++)
		{
			
			VGA[y*320+x] = 0;
		}
	}
}

int sys_setpixel(void)
{
	int hdc;
    int x;
    int y;
	
	if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    if(argint(1, &x) < 0 )
    {
        return -1;
    }
    if(argint(2, &y) < 0 )
    {
        return -1;
    }

    
if(hdcList[hdc].index != -1)
{
	uchar *VGA=(uchar*)P2V(0xA0000);
	VGA[y*320+x] = hdcList[hdc].penIndex;
	
    return 0;
}
else
{
    return -1;
}
}

int sys_moveto(void)
{
	int hdc;
    int x;
    int y;
	
	if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    if(argint(1, &x) < 0 )
    {
        return -1;
    }
    if(argint(2, &y) < 0 )
    {
        return -1;
    }
    if(hdcList[hdc].index != -1)
    {
    hdcList[hdc].xPos = x;
    hdcList[hdc].yPos = y;
	movX = x; 
	movY = y;
	return 0;
    }
    else
    {
        return -1;
    }
}

int sys_lineto(void)
{
    int hdc;
    
    int x1;
    int y1;
    int absX;
    int absY;
    int yi = 0;
    int dx = 0;
    int dy = 0;
    int D;
    int x = 0;
    int y = 0;
    int tempX = 0;
    int tempY = 0;
    int xi= 0;
    
    uchar *VGA=(uchar*)P2V(0xA0000);
	if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    if(argint(1, &x1) < 0 )
    {
        return -1;
    }
    if(argint(2, &y1) < 0 )
    {
        return -1;
    }
   
    
    if(hdcList[hdc].index != -1)
    {
    int x0 = hdcList[hdc].xPos;
    int y0 = hdcList[hdc].yPos;
    if(x1 > 320)
    {
        x1 = 320;
    }
    else if( x1 < 0)
    {
        x1 = 0;
    }
    if(y1 > 200)
    {
        y = 200;
    }
    else if(y1 < 0)
    {
        y = 0;
    }
    
    hdcList[hdc].xPos = x1;
    hdcList[hdc].yPos = y1;
    absX = x1 - x0;
    absY = y1 - y0;
    if(absX < 0)
    {
        absX = -absX;
    }	
    if(absY < 0)
    {
        absY= -absY;
    }

    if(absY < absX)
    {
        if(x0 > x1)
        {
            tempX = x0;
            tempY = y0;
            x0 = x1;
            y0 = y1;
            x1 = tempX;
            y1 = tempY;
            dx = x1 - x0;
            dy = y1 - y0;
            yi = 1;
            if(dy < 0)
            {
                yi = -1;
                dy = -dy;
            }
            D = (2 * dy) - dx;
            y = y0;
            x = x0;
            while(x <= x1)
            {
                VGA[y*320+x] = hdcList[hdc].penIndex;;
                if(D > 0)
                {
                    y = y + yi;
                    D = D + (2 * (dy - dx));
                }
                else
                {
                    D = D + 2*dy;
                }
                x++;
            }
        }
        else
        {
            dx = x1 - x0;
            dy = y1 - y0;
            yi = 1;
            if(dy < 0)
            {
                yi = -1;
                dy = -dy;
            }
            D = (2 * dy) - dx;
            
            y = y0;
            x = x0;
            while(x <= x1)
            {
                VGA[y*320+x] = hdcList[hdc].penIndex;;
                if(D > 0)
                {
                    y = y + yi;
                    D = D + (2 * (dy - dx));
                }
                else
                {
                    D = D + 2*dy;
                }
               x++; 
            }
        }
        
    }
    else
    {
        if(y0 > y1)
        {
            tempX = x0;
            tempY = y0;
            x0 = x1;
            y0 = y1;
            x1 = tempX;
            y1 = tempY;
            dx = x1 - x0;
            dy = y1 - y0;
            xi = 1;
            if(dx < 0)
            {
                xi = -1;
                dx = -dx;
            }
            D = (2 * dx) - dy;
            y = y0;
            x = x0;
            while(y <= y1)
            {
                VGA[y*320+x] = hdcList[hdc].penIndex;;
                if(D > 0)
                {
                    x = x + xi;
                    D = D + (2 * (dx - dy));
                }
                else
                {
                    D = D + 2*dx;
                }
                y++;
            }
        }
        else
        {
            dx = x1 - x0;
            dy = y1 - y0;
            xi = 1;
            if(dx < 0)
            {
                xi = -1;
                dx = -dx;
            }
            D = (2 * dx) - dy;
            y = y0;
            x = x0;
            while(y <= y1)
            {
                VGA[y*320+x] = hdcList[hdc].penIndex;;
                if(D > 0)
                {
                    x = x + xi;
                    D = D + (2 * (dx - dy));
                }
                else
                {
                    D = D + 2*dx;
                }
                y++;
            }
        }
        
    }
   // release(&cons.lock);
    return 0;
    }
    else 
    {
        return -1;
    }
}

int sys_setpencolour(void)
{
    int index;
    int r;
    int g;
    int b;
    
    if(argint(0, &index) < 0 )
        {
            return -1;
        }
    if(argint(1, &r) < 0 )
        {
            return -1;
        }
    if(argint(2, &g) < 0 )
        {
            return -1;
        }
    if(argint(3, &b) < 0 )
        {
            return -1;
        }

    if(index > 255)
    {
        index = 255;
    }
    if(index < 16)
    {
        index = 16;
    }
    if(r > 63)
    {
        r = 63;
    }
    if(r < 0)
    {
        r = 0;
    }
    if(g > 63)
    {
        g = 63;
    }
    if(g < 0)
    {
        g = 0;
    }
    if(b > 63)
    {
        b = 63;
    }
    if(b < 0)
    {
        b = 0;
    }
    
    outb(0x3C8, index);
    outb(0x3C9, r);
    outb(0x3C9, g);
    outb(0x3C9, b);
    
    return 0;
}

int sys_selectpen(void)
{
    int hdc;
    int index;
    
    if(argint(0, &hdc) < 0 )
        {
            return -1;
        }
    if(argint(1, &index) < 0 )
        {
            return -1;
        }
if(hdcList[hdc].index != -1)
{
    if(index > 255)
    {
        return -1;
    }
    pen = index;
    hdcList[hdc].penIndex = index; 
    return 0;
}
else
{
    return -1;
}

}

int sys_fillrect(void)
{
    int hdc = 0;

    struct rect *rect;

    if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    if (argptr(1, (void*)&rect, sizeof(&rect)) < 0) 
    {
        return -1;
    }
 
    if(hdcList[hdc].index != -1)
    {
    uchar *VGA=(uchar*)P2V(0xA0000);
	for(int x = rect->left; x <= rect->right; x++)
	{
		for(int y = rect->top; y <= rect->bottom; y++)
		{	
			VGA[y*320+x] = hdcList[hdc].penIndex;
		}
	}
    return 0;
    }
    else
    {
        return -1;
    }
}

int sys_beginpaint(void)
{
    struct hdc hdc;
    //acquire(&cons.lock);
    for(int i = 0; i <= 99; i++)
    {
        if(hdcList[i].index == -1)
        {
            hdc.index = i;
            hdcList[i] = hdc;
            
            return hdc.index;
            break;
        }
        
    }
    hdc.index = counter;
    hdcList[counter] = hdc;
    
    counter++;
    //release(&cons.lock);
    return hdc.index;
    
    
}

int sys_endpaint(void)
{
    int hdc;

    if(argint(0, &hdc) < 0 )
    {
        return -1;
    }
    
    hdcList[hdc].index = -1;
    
    return 0;
}


