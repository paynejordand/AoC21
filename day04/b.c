#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int layout[5][5];
    int called[5][5];
    int won;
} bingo;

void readDraws(int* draws)
{
    char c;
    do
    {
        scanf("%d", draws++);
    } while ((c = fgetc(stdin)) == ',');
}

void readBoards(bingo* inBoard)
{
    while(!feof(stdin))
    {
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                scanf("%d ", &(inBoard->layout[i][j]));
                inBoard->called[i][j] = 0;
            }
        }
        (inBoard++)->won = 0;
    }
}

int checkHoriz(bingo board, int row)
{
    for(int i = 0; i < 5; i++)
    {
        if(!board.called[row][i])
            return 0;
    }
    return 1;
}

int checkVert(bingo board, int col)
{
    for(int i = 0; i < 5; i++)
    {
        if(!board.called[i][col])
            return 0;
    }
    return 1;
}

void checkBoards(bingo* boards, int draw, int* winningBoard, int * win)
{
    for(int i = 0; i < 100; i++)
    {
        if (boards->won)
        {
            boards++;
            continue;
        }
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 5; k++)
            {
                if(boards->layout[j][k] == draw)
                {
                    boards->called[j][k] = 1;
                    if (checkVert(*boards, k) || checkHoriz(*boards, j))
                    {
                        (*winningBoard) = i;
                        *win = i;
                        boards->won = 1;
                    }
                }
            }
        }
        boards++;
    }
}

void playBingo(int* draws, bingo* boards, int *winningBoard, int *lastDraw)
{
    int winCount = 0;
    for(int i = 0; i < 100; i++)
    {
        int draw = *draws++;
        int win = 0;
        checkBoards(boards, draw, winningBoard, &win);
        if(win)
        {
            *lastDraw = draw;
            winCount++;
            if (winCount == 100)
                return;
        }
    }
}

int calcBoard(bingo board, int lastDraw)
{
    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(!board.called[i][j])
                sum += board.layout[i][j];
        }
    }
    return lastDraw * sum;
}

int main(void)
{
    int winningBoard = -1;
    int lastDraw;
    int* draws = malloc(sizeof(int) *100);
    bingo* inputBoard = malloc(sizeof(bingo) * 100);


    readDraws(draws);
    readBoards(inputBoard);

    playBingo(draws, inputBoard, &winningBoard, &lastDraw);

    printf("%d\n", calcBoard(inputBoard[winningBoard], lastDraw));

    free(draws);
    free(inputBoard);
    return 0;
}