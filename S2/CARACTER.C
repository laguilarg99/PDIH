#include <stdio.h>
#include <dos.h>

int mi_getchar(){
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

int main(){
    
    int tmp;
    
    while ( (char) tmp != 'e')
    {
        printf("\nPulsa una tecla (e para salir): ");
        tmp = mi_getchar();
    
        printf("\nHas pulsado: ");
        mi_putchar( (char)tmp);
    }
    

  
    return 0;
}