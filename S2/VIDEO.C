#include <stdio.h>
#include <DOS.H>
#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;
//Modo de video 1,3,4

/* Selecciona el modo de video deseado */
void selecciona_modo_video(BYTE modo){
    union  REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = modo;
    int86(0x10, &inregs, &outregs);
}

// hace una pausa
void pausa(){
 union REGS inregs, outregs;
 inregs.h.ah = 0x00;
 int86(0x16, &inregs, &outregs);
}

int main(){
    BYTE MODOTEXTOALTERNO = 1;
    selecciona_modo_video(MODOTEXTOALTERNO); //MODO TEXTO GRANDE
	printf("\nLETRAS GRANDES");
    pausa();
    selecciona_modo_video(MODOTEXTO); //MODO TEXTO ORIGINAL
    return 0;  
}

