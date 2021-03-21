#ifndef MYCONIO_H_ 
#define MYCONIO_H_

#define BYTE unsigned char

void mi_gotoxy(int x, int y);
void mi_setcursortype(int tipo_cursor);
void mi_setvideomode(BYTE modo);
int mi_getvideomode(void);
void mi_textcolor(unsigned char ctexto);
void mi_textbackground(unsigned char cfondo);
void mi_clscr(void);
void mi_cputchar( char letra);
void mi_putchar(char c);
int mi_getchar(void);
void mi_getche(void);

void mi_pausa(void);


#endif // MYCONIO_H_