#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

struct coord
{
    int x;
    int y;
};
struct alive_tab
{
    int length;
    struct coord alive[50];
};

struct the_board
{
    int is_alive;
    int point;
};

int main(int argc, char *argv[])
{

    struct the_board board[12][17];
    int board_length = 12;
    int board_width = 17;
    

    struct alive_tab AliveTab;
    AliveTab.length = 0;
    int condition = 1;

    //board initialization :
    for (int i = 0; i <= board_length; i++)
    {
        for (int j = 0; j <= board_width; j++)
        {
            board[i][j].is_alive = 0;
            board[i][j].point = 0;
        }
    }

    //taking user input for alive cells
    printf("combien de cellules vivantes = ");
    int nbrAliveCells = 0;
    scanf("%d", &nbrAliveCells);
    printf("\n");
    int coordX = 0;
    int coordY = 0;
    AliveTab.length = nbrAliveCells;
    printf("Remarque : les indices commencent de [1,1]\n");
    for (int i = 0; i < nbrAliveCells; i++)
    {
        printf("coordonné de la cellule %d = ", i);
        scanf("%d", &coordX);
        scanf("%d", &coordY);
        board[coordX][coordY].is_alive = 1;
        AliveTab.alive[i].x = coordX;
        AliveTab.alive[i].y = coordY;
        printf("\n");
    }



    // drawing the board
    for (int i = 0; i <= board_length; i++)
    {
        for (int j = 0; j <= board_width; j++)
        {
            if ((i != 0) && (j != 0))
            {
                if (board[i][j].is_alive == 1)
                {
                    printf("  @  ");
                }
                else
                {
                    printf("  .  ");
                }
                if (j == board_width)
                {
                    printf("\n\n");
                }
            }
        }
    }

    int nbrTour = 1;

    while (condition)
    {
        printf("---------- Tour numéro %d ---------\n", nbrTour);
        for (int i = 0; i < AliveTab.length; i++)
        {
            int x = AliveTab.alive[i].x;
            int y = AliveTab.alive[i].y;

            board[x][y + 1].point = board[x][y + 1].point + 1;

            board[x][y - 1].point = board[x][y - 1].point + 1;

            board[x + 1][y - 1].point = board[x + 1][y - 1].point + 1;
            board[x + 1][y].point = board[x + 1][y].point + 1;
            board[x + 1][y + 1].point = board[x + 1][y + 1].point + 1;

            board[x - 1][y - 1].point = board[x - 1][y - 1].point + 1;
            board[x - 1][y].point = board[x - 1][y].point + 1;
            board[x - 1][y + 1].point = board[x - 1][y + 1].point + 1;
        }
        AliveTab.length = 0; // on va reconstruire un nouveau Tableau des cellules vivantes
        for (int i = 1; i <= board_length - 2; i++)
        {
            for (int j = 1; j <= board_width - 2; j++)
            {
                if (board[i][j].is_alive == 1)
                {
                    if ((board[i][j].point > 3) || (board[i][j].point < 2))
                    {
                        board[i][j].is_alive = 0; // mourir de sur charge ou moins voisin
                        //printf("cellue va mourir = [%d,%d] \n", i, j);
                    }
                    else
                    {
                        AliveTab.alive[AliveTab.length].x = i;
                        AliveTab.alive[AliveTab.length].y = j;
                        AliveTab.length++;
                        // printf("cellue survie = [%d,%d] \n", i, j);
                    }
                }
                else
                {
                    if (board[i][j].point == 3)
                    {
                        board[i][j].is_alive = 1; // naissance de la cellule
                        AliveTab.alive[AliveTab.length].x = i;
                        AliveTab.alive[AliveTab.length].y = j;
                        AliveTab.length++;
                        //  printf("naissance de [%d,%d]\n", i, j);
                    }
                }
                board[i][j].point = 0;
            }
        }

        for (int i = 0; i <= board_length; i++)
        {
            for (int j = 0; j <= board_width; j++)
            {
                if ((i != 0) && (j != 0))
                {
                    if (board[i][j].is_alive == 1)
                    {
                        printf("  @  ");
                    }
                    else
                    {
                        printf("  .  ");
                    }
                    if (j == board_width)
                    {
                        printf("\n\n");
                    }
                }
            }
        }
        nbrTour++;
        getchar();
    }
}