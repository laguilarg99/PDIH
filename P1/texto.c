#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

// hace una pausa
void pausa(void){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}

//TODO

//coloca el cursor en una posición determinada
void my_gotoxy(int x, int y){
    union REGS inregs, outregs;
    if (x < 0)
    {
        return -1;
    }

    if (y < 0)
    {
        return -1;
    }

    inregs.h.ah = 0x02;

    inregs.h.dh = x;
    inregs.h.dl = y;

    inregs.h.bh = 0;

    int86(0x10, &inregs, &outregs);
}

//fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
    // Esta función viene hecha en el ejemplo
void my_setcursortype(int tipo_cursor){
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

//fija el modo de video deseado
    //También estaba en el ejemplo
void my_setvideomode(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

//obtiene el modo de video actual
void my_getvideomode(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
   
    if(inregs.h.al == 4){
        printf("Grafico");
    } else printf("texto");
}

//modifica el color de primer plano con que se mostrarán los caracteres
void my_textcolor(void){
    // union REGS inregs, outregs;
    // inregs.h.ah = 0xB;
    // inregs.h.bh = 0x1;
    // inregs.h.bl = 0x10;

    // int86(0x10, &inregs, &outregs);
}

//modifica el color de fondo con que se mostrarán los caracteres
void my_textbackground(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = 0x00;
    inregs.h.bh = 0x10;

    int86(0x10, &inregs, &outregs);
}

//borra toda la pantalla
void my_clrscr(void){

}

//escribe un carácter en pantalla con el color indicado actualmente
void my_cputchar(void){

}

//obtiene un carácter de teclado y lo muestra en pantalla
void my_getche(void){

}

//EXTRA

//Permite dibujar un recuadro en la	pantalla en	modo texto.
// Params: coordenada superior izquierda, coordenada inferior derecha del recuadro,
//  color de primer plano y el color de fondo.

void textborder(void){

}

//Establece el modo VGA para crear dibujos sencillos en pantalla
void setDrawVGA(void){

}

int main(){
   int i;
   
    my_setvideomode(MODOTEXTO);

    my_gotoxy(6,6);

    my_setcursortype(2);

   // my_textbackground();

    my_getvideomode();

    pausa();


    return 0;
}
