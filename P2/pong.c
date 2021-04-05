#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 3000000

int main(int argc, char *argv[])
{
    int rows, cols;
    int x = 0, y = 0;

    //Cuadro de presentación de controles

    initscr();
    refresh();
    getmaxyx(stdscr, rows, cols);

    WINDOW *window = newwin(rows, cols, 0, 0);
    box(window, '|', '-');
    
    mvwprintw(window, 10, 10, "Jugador1: W - Arriba  S - Abajo");
    mvwprintw(window, 15, 10, "Jugador2: O - Arriba  K - Abajo");
    wrefresh(window);
    
    usleep(DELAY);
    endwin();

    
    //Juego

    //Rango de movimiento del pong
    int max_y = rows, max_x = cols;
    
    //posicion inicial de la pelota
    int next_x = max_x/2;
    int next_y = max_y/2;
    x = max_x/2;
    y = max_y/2;

    //posicion del jugador 1
    int next_j1_x = 0;
    int next_j1_y = 0;

    //posicion del jugador 2
    int next_j2_x = max_x - 1;
    int next_j2_y = 0;

    //direccion de la pelota
    int direction_x = 1;
    int direction_y = 1;

    //Puntuaciones
    int score_J1 = 0;
    int score_J2 = 0;

    initscr();
    noecho();
    curs_set(FALSE);
    
    timeout(50);

    while (1)
    {
       
        clear();
        
        //Score 
        mvprintw(0, max_x/2 - 11, "Score 1: %d |  Score 2: %d",score_J1,score_J2);
        
        //pintar pelota
        mvprintw(next_y, next_x, "o");
        
        //Pintar al jugador 1
        mvprintw(next_j1_y + 1, next_j1_x,"|");
        mvprintw(next_j1_y + 2, next_j1_x,"|");
        mvprintw(next_j1_y + 3, next_j1_x,"|");
        mvprintw(next_j1_y + 4, next_j1_x,"|");
        
        //Pintar al jugador 2
        mvprintw(next_j2_y + 1, next_j2_x,"|");
        mvprintw(next_j2_y + 2, next_j2_x,"|");
        mvprintw(next_j2_y + 3, next_j2_x,"|");
        mvprintw(next_j2_y + 4, next_j2_x,"|");

        refresh();
        

        //Movimiento de la pelota
        next_y = y + direction_y;
        next_x = x + direction_x*2;
    

        //Calculo del movimiento pelota eje y
        if (next_y >= max_y || next_y <= 0)
        {
            direction_y *= -1;
        }else{
            y += direction_y;
        }

        //Calculo del movimiento pelota eje x
        if (next_x == next_j2_x && (next_y <= next_j2_y + 4 && next_y >= next_j2_y)){
            direction_x *= -1;
        } 
        else if (next_x == next_j1_x && (next_y <= next_j1_y + 4 && next_y >= next_j1_y)){
            direction_x *= -1;
        }else{
            x += direction_x;
        }

        //Scores
        if (next_x > next_j2_x){
            next_x = max_x/2;
            next_y = max_y/2;
            x = max_x / 2;
            y = max_y / 2;
            score_J1++;
        } 
        else if (next_x < next_j1_x){
            next_x = max_x/2;
            next_y = max_y/2;
            x = max_x / 2;
            y = max_y / 2;
            score_J2++;
        }


        switch (getch())
        {

            //Movimiento jugador 1
            case 'w':
                if (next_j1_y >= 2)
                    next_j1_y -= 1;
                break;

            case 's':
                if (next_j1_y + 3 <= max_y - 3)
                    next_j1_y += 1;
                break;

            //Movimiento jugador 2
            case 'o':
                if (next_j2_y >= 2)
                    next_j2_y -= 1;
                break;

            case 'k':
                if (next_j2_y + 3 <= max_y - 3)
                    next_j2_y += 1;
                break;

            default:
                break;
        }

    }
    
    endwin();
}