#include <stdio.h>

#define FIRST_MATRIX_SIZE 4
#define SECOND_MATRIX_SIZE 5
#define THIRD_MATRIX_SIZE 6
#define MAXIMUM_MATRIX_SIZE 10


int isValidCoordinate(int x, int bound)
{
    return x >= 0 && x < bound;
}

int isValidCoordinates(int x, int y, int bound)
{
    return isValidCoordinate(x, bound) && isValidCoordinate(y, bound);
}

void MoveRight(int* x, int* y)
{
    *y = *y + 1;
}

void MoveDown(int *x, int*y)
{
    *x = *x + 1;
}


void SolutionForSizedMatrix(int matrix[MAXIMUM_MATRIX_SIZE][MAXIMUM_MATRIX_SIZE], int size)
{

    int currentX = 0;
    int currentY = 0;

    int isGoingUp = 0;

    for(int i = 1; i <= size * size; i++)
    {

        int tempX = currentX;
        int tempY = currentY;
        matrix[currentX][currentY] = i;
        if(isGoingUp)
        {
            tempX--;
            tempY++;
        }
        else
        {
            tempX++;
            tempY--;
        }
        if(!isValidCoordinates(tempX, tempY, size))
        {
            tempX = currentX;
            tempY = currentY;

            int canGoDown = tempX + 1 < size;
            int canGoRight = tempY + 1 < size;
            if(isGoingUp)
                canGoRight ? MoveRight(&tempX, &tempY) : MoveDown(&tempX, &tempY);
            else
                canGoDown ? MoveDown(&tempX, &tempY) : MoveRight(&tempX, &tempY);

            isGoingUp = !isGoingUp;
        }

        currentX = tempX;
        currentY = tempY;
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
    printf("\n\n");

}

int main()
{
    int firstMatrix[FIRST_MATRIX_SIZE][FIRST_MATRIX_SIZE];
    int secondMatrix[SECOND_MATRIX_SIZE][SECOND_MATRIX_SIZE];
    int thirdMatrix[THIRD_MATRIX_SIZE][THIRD_MATRIX_SIZE];
    SolutionForSizedMatrix(firstMatrix, FIRST_MATRIX_SIZE);
    SolutionForSizedMatrix(secondMatrix, SECOND_MATRIX_SIZE);
    SolutionForSizedMatrix(thirdMatrix, THIRD_MATRIX_SIZE);

}

