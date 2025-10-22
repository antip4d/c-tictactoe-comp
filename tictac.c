#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 3

void initializedBoard(char area[][MAX_SIZE]);
void drawMatrix(char area[][MAX_SIZE]);
void player_move(char area[][MAX_SIZE]);
int checkWinPlayer(char area[][MAX_SIZE], char player);
int find_winning_move(char area[][MAX_SIZE], char player, int *row, int *col);
void smart_comp_move(char area[][MAX_SIZE]);


int player = 0;

int main()
{   
    srand(time(NULL));
    char area[MAX_SIZE][MAX_SIZE];
    initializedBoard(area);
    printf("Game VS bot\n");
    while(1)
    {
        drawMatrix(area);
        if(player == 0)
        {
            player_move(area);
        }
        else
        {
            smart_comp_move(area);
        }
        if(checkWinPlayer(area,'X'))
        {
            drawMatrix(area);
            printf("You win!");
            break;
        }
        if(checkWinPlayer(area,'O'))
        {
            drawMatrix(area);
            printf("You lose!");
            break;
        }
        int full = 1;
        for(int i =0 ; i < MAX_SIZE; i ++)
        {
            for(int j = 0; j < MAX_SIZE; j++)
            {
                if(area[i][j] == ' ' )
                {
                    full = 0;
                }
            }
        }
        if(full){
            drawMatrix(area);
            printf("Nichya");
            break;
        }
        player = !player;
    }
}

void initializedBoard(char area[][MAX_SIZE])
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            area[i][j] = ' ';
        }
    }
}
void drawMatrix(char area[][MAX_SIZE])
{
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        printf("===");
    }
    printf("\n");
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        for (size_t j = 0; j < MAX_SIZE; j++)
        {
            printf("|%c|", area[i][j]);
        }
        printf("\n");
    }
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        printf("===");
    }
}
void player_move(char area[][MAX_SIZE])
{
    int row;
    int col;
    printf("\nYour turn (row,col) ");
    scanf("%d%d", &row, &col);
    row--;
    col--;
    while (1)
    {
        if (row >= 0 && row < MAX_SIZE && col >= 0 && col < MAX_SIZE && area[row][col] == ' ')
        {
            area[row][col] = 'X';
            break;
        }
        else
        {
            printf("Error");
        }
    }
}
int checkWinPlayer(char area[][MAX_SIZE], char player)
{
    for(int i =0; i < MAX_SIZE; i++)
    {
        if(area[i][0] == player && area[i][1] == player && area[i][2] == player)
        {
            return 1;
        }
    }
    for(int i = 0; i < MAX_SIZE; i++ )
    {
        if(area[0][i] == player && area[1][i] == player && area[2][i] == player)
        {
            return 1;
        }
    }
    if(area[0][0] == player && area[1][1] == player && area[2][2] == player)
    {
        return 1;
    }
    
    if(area[0][2] == player && area[1][1] == player && area[2][0] == player)
    {
        return 1;
    }
    return 0;
}
int find_winning_move(char area[][MAX_SIZE], char player, int *row, int *col)
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            if(area[i][j] == ' ')
            {
                area[i][j] = player;
                if(checkWinPlayer(area,player) == 1)
                {
                    area[i][j] = ' ';
                    *row = i;
                    *col = j;
                    return 1;
                }
                area[i][j] = ' ';
            }
        }
    }
    return 0;
}
void smart_comp_move(char area[][MAX_SIZE])
{
    int row,col;
    if(find_winning_move(area,'O',&row,&col))
    {
        area[row][col] = 'O';
        printf("Bot %d %d",row+1, col+1);
        return;
    }
    if(find_winning_move(area, 'X',&row,&col))
    {
        area[row][col] = 'O';
        printf("Bot %d %d",row+1, col+1);
        return;
    }
    do {
        row = rand() % MAX_SIZE;
        col = rand() % MAX_SIZE;
    } while(area[row][col] != ' ');
    
    area[row][col] = 'O';
    printf("Bot %d %d",row+1, col+1);
}