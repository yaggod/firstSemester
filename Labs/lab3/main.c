#include <stdio.h>
#define MATRIXSIZE 8

#define NONE   0
#define LEFT    1
#define RIGHT   -1
#define DOWN    2
#define UP      -2

int IsInRange(int a, int minValue, int maxValue)
{
    return a >= minValue && a < maxValue;
}

int GetSubsequencesAtIndex(char charactersMatrix[MATRIXSIZE][MATRIXSIZE], int x, int y, int lastDirection, int letterIndex)
{
    char word[5] = "ABBA";
    int directions[4] = { LEFT, RIGHT, DOWN, UP};
    int result = 0;

    if(!IsInRange(x, 0, MATRIXSIZE) || !IsInRange(y, 0, MATRIXSIZE))
        return 0;
   if(charactersMatrix[x][y] != word[letterIndex])
        return 0;
    if(letterIndex == 3)
        return 1;

    for(int i = 0; i < 4; i++)
    {
        if(lastDirection == -directions[i])
            continue;

        int localX = x, localY = y;
        switch(directions[i])
        {
        case LEFT:
            localX--;
            break;
        case RIGHT:
            localX++;
            break;
        case DOWN:
            localY++;
            break;
        case UP:
            localY--;
            break;
        }
        result += GetSubsequencesAtIndex(charactersMatrix, localX, localY, directions[i], letterIndex + 1);
    }

    return result;
}

int ABBAFromCharacters(char charactersMatrix[MATRIXSIZE][MATRIXSIZE])
{
    int result = 0;
    for(int i = 0; i < MATRIXSIZE; i++)
        for(int j = 0; j < MATRIXSIZE; j++)
            result += GetSubsequencesAtIndex(charactersMatrix, i, j, NONE, 0);;

    return result / 2;
}

void GetHexdecimalString(char buffer[], int number)
{
    char letters[] = "0123456789ABCDEF";
    for(int i = 0; i < MATRIXSIZE; i++)
    {
        buffer[MATRIXSIZE - 1 - i] = letters[number & 0xF];
        number = number >> 4;
    }
}

int ABBA(int values[MATRIXSIZE])
{
    char hexdecimalStrings[MATRIXSIZE][MATRIXSIZE];
    for(int i = 0; i < MATRIXSIZE; i++)
    {
        GetHexdecimalString(hexdecimalStrings[i], values[i]);
    }

    return ABBAFromCharacters(hexdecimalStrings);
}

int main()
{
    int sample1[MATRIXSIZE] ={-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    printf("%d", ABBA(sample1));

    return 0;
}
