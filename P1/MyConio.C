#include <stdio.h>
#include <dos.h>
#include <MyConio.h>

#define BYTE unsigned char
#define VGA_256_COLOR_MODE  0x13   /* use to set 256-color mode. */
#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define WRITE_DOT           0x0C      /* BIOS func to plot a pixel. */
#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */

// BYTE MODOTEXTO = 3;
// BYTE MODOGRAFICO = 4;
// BYTE *VGA = (BYTE *)0xA0000; //This point to the video memory

int _color_texto = 1;
int _color_fondo = 0;

// hace una pausa
void mi_pausa(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}

void mi_gotoxy(int x, int y){ 
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dl = x; //Posicion del cursor x
    inregs.h.dh = y; //Posicion del cursor y
    inregs.h.bh = 0;

    int86(0x10, &inregs, &outregs);
}

//establece el tipo de cursor
void mi_setcursortype(int tipo_cursor){
    union REGS inregs, outregs;	 	 	 	 																																		
    inregs.h.ah = 0x01;
    
    switch(tipo_cursor){
        case 0: //invisible
            inregs.h.ch = 010;
            inregs.h.cl = 000;
        break;

        case 1: //normal
            inregs.h.ch = 010;
            inregs.h.cl = 010;
        break;
        
        case 2: //grueso
            inregs.h.ch = 000;
            inregs.h.cl = 010;
        break;

        default: return -1;
    }
    
    int86(0x10, &inregs, &outregs);
}

// establece el modo de vídeo: 3-texto, 4-gráfico
void mi_setvideomode(BYTE modo){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = modo;
    int86(0x10, &inregs, &outregs);
}

// devuelve el modo 
int mi_getvideomode(void){ /* ERROR! CALCULA MODO VIDEO PERO NO DEVUELVE */
    union REGS inregs, outregs;
    int videomode;
    inregs.h.ah = 0x0F; 	 	 	 																											
    int86(0x10, &inregs, &outregs);
    videomode = outregs.h.al;
    return videomode;
}

// modifica el color de primer plano con que se mostrarán los caracteres
void mi_textcolor(unsigned char ctexto){
    _color_texto = ctexto;
}


// modifica el color de fondo con el que se mostrarán los caracteres
void mi_textbackground(unsigned char cfondo){
    _color_fondo = cfondo;
}

//Borra toda la pantalla CAMBIA EL MODO DE TEXTO!!
void mi_clscr(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.dh = 25;
    inregs.h.dl = 80;
    inregs.h.bh = 0x00;
    inregs.x.cx = 0x00;
    int86( 0x10, &inregs, &outregs );
    
    mi_setvideomode(3);
}



//escribe un carácter en pantalla con el color indicado actualmente
void mi_cputchar(char letra){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = letra;
    inregs.h.bl = _color_fondo << 4 | _color_texto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
    return;
}


int mi_getchar(void){
    union REGS inregs, outregs;
    int caracter;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}


//Obtiene un caracter de teclado teclado por pantalla y lo muestra
void mi_getche(void){
    int tmp;

    printf("\nPulsa una tecla: ");
    tmp = mi_getchar();
    
    printf("\nHas pulsado: ");
    mi_putchar( (char)tmp);

}