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

// Permite dibujar un recuadro en pantalla en modo texto
// Params coordenada superior izquierda y coordenada inferior derecha
//      Color de primer plano y el color del texto
void modoTextoRecuadro(int l_x, int l_y, int r_x, int r_y, unsigned char ctexto, unsigned char cfondo){

    int i;
    char myChar = ' ';

    //Cambiar color del texto
    mi_textcolor(ctexto);
    mi_textbackground(cfondo);

    //Dibujar arista superior 
    for(i = l_x; i<r_x-1; i++){       
        mi_gotoxy(i,l_y);
        mi_cputchar(myChar);
    }

    //Dibujar laterales
    for(i = l_y; i<r_y; i++){       
        mi_gotoxy(r_x-1,i);
        mi_cputchar(myChar);
        mi_gotoxy(l_x,i);
        mi_cputchar(myChar);
    }

    //Dibujar arista inferior
    for(i = l_x; i<r_x-1; i++){       
        mi_gotoxy(i,r_y-1);
        mi_cputchar(myChar);
    }
}

int main(void){

    mi_setvideomode(3);
    modoTextoRecuadro(1,1,9,9,1,3);
    modoTextoRecuadro(10,10,14,14,0,15);
    modoTextoRecuadro(15,1,27,9,2,6);

    mi_pausa();
    mi_clscr();

    return 0;
}