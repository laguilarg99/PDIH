#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <MyConio.h>

#include <conio.h>

#define BYTE unsigned char
#define VGA_256_COLOR_MODE  0x13   /* use to set 256-color mode. */
#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define WRITE_DOT           0x0C      /* BIOS func to plot a pixel. */
#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;
BYTE *VGA = (BYTE *)0xA0000; //This point to the video memory

void plot_pixel_slow(int x,int y,BYTE color){
  
  union REGS inregs, outregs;

  inregs.h.ah = WRITE_DOT;
  inregs.h.al = color;
  inregs.x.cx = x;
  inregs.x.dx = y;

  int86(VIDEO_INT, &inregs, &outregs);

}

void dibujos_sencillos(void){
    int x,y,color,i;
    
    mi_setvideomode(VGA_256_COLOR_MODE);
    
    for(i=0;i<30000L;i++)               
    {
        x=rand()%SCREEN_WIDTH;
        y=rand()%SCREEN_HEIGHT;
        color=rand()%NUM_COLORS;
        plot_pixel_slow(x,y,color);
    }

    mi_pausa();
}


void dibujos_sencillos2(void){
    int x,y,color,i,j;
    int centro = 320/2;

    mi_setvideomode(VGA_256_COLOR_MODE);

    for(i = 0; i < 200; i++){

        color = rand()%NUM_COLORS;

        for(j = 0; j < 320; j++){
            plot_pixel_slow(j,i,color);
        }
    }

    for(i = 0; i < 200; i++){

        color = rand()%NUM_COLORS;

        for(j = 0; j < 320; j++){
            if (j == centro-i){
                plot_pixel_slow(j,i,0);
                plot_pixel_slow(j-1,i,0);
            } 
             
            if ( j == centro+1+i){
                plot_pixel_slow(j,i,0);
                plot_pixel_slow(j-1,i,0);
            }

            if(i == 100){
                plot_pixel_slow(j,i,0);
            }
        }
    }
}

void dibujos_sencillos3(int l_x, int l_y, int r_x, int r_y){
    int x,y,i,j;
    int pixels = 320*200;
    int color_start = 32, color_limit = 16, color = 0;


    if(r_x - l_x <=0){
        return 0;
    }

    j = l_y;

    for(i = l_x; i<r_x+1; i++){
        plot_pixel_slow(i,j,color+color_start);
        plot_pixel_slow(i,r_y,color+color_start);
        color++;
        color = color%color_limit;
    }

    for(j = l_y; j<r_y+1; j++){
        plot_pixel_slow(i,j,color+color_start);
        plot_pixel_slow(l_y,j,color+color_start);
        color++;
        color = color%color_limit;
    }

    dibujos_sencillos3(l_x+1,l_y+1,r_x-1,r_y-1);

}

void dibujos_sencillos4(int l_x, int l_y, int r_x, int r_y, int in_color){
    int x,y,i,j;
    int pixels = 320*200;
    int color_start = 32, color_limit = 16, color = 0;


    if(r_y - l_y <= 0){
        return 0;
    }

    j = l_y;

    for(i = l_x; i<r_x+1; i++){
        plot_pixel_slow(i,j,in_color+color_start);
        plot_pixel_slow(i,r_y,in_color+color_start);
    }

    for(j = l_y; j<r_y+1; j++){
        plot_pixel_slow(i,j,in_color+color_start);
        plot_pixel_slow(l_y,j,in_color+color_start);
    }

    in_color++;
    in_color = in_color%color_limit;

    dibujos_sencillos4(l_x+1,l_y+1,r_x-1,r_y-1,in_color);

}

int main(void){
    dibujos_sencillos();
    mi_pausa();
    mi_clscr();
    dibujos_sencillos2();
    mi_pausa();
    mi_clscr();
    mi_setvideomode(VGA_256_COLOR_MODE);
    dibujos_sencillos3(0,0,320,200);
    mi_pausa();
    mi_clscr();
    mi_setvideomode(VGA_256_COLOR_MODE);
    dibujos_sencillos4(0,0,320,200,1);
    mi_pausa();
    mi_clscr();
}