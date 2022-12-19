#include <stdio.h>
#include <math.h>
#define MAX_POINTS_COUNT 50
void Swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
void GetIndexesOfOrderedArray(float originalArray[], int indexesArray[], int elementsCount)
{
    for(int i = 0; i < elementsCount; i++)
        for(int j = i + 1; j < elementsCount; j++)
            if(originalArray[indexesArray[i]] < originalArray[indexesArray[j]])
                Swap(&indexesArray[i], &indexesArray[j]);
}
float Travese_Clockwise(float coordinates[], int pointsCount)
{
    float result = 0, averageX = 0, averageY = 0, angles[MAX_POINTS_COUNT] = { 0 };
    int angles_Order[MAX_POINTS_COUNT] = { 0 };
    for(int i = 0; i < pointsCount; i++)
    {
        averageX += coordinates[2*i] / pointsCount;
        averageY += coordinates[2*i + 1] / pointsCount;
        angles_Order[i] = i;
    }
    for(int i = 0; i < pointsCount; i++)
        angles[i] = atan2(coordinates[2*i + 1] - averageY, coordinates[2*i] - averageX);
    GetIndexesOfOrderedArray(angles, angles_Order, pointsCount);
    for(int i = 0; i < pointsCount; i++)
    {
        float deltaX = coordinates[2*angles_Order[i]] - coordinates[2*angles_Order[(i + 1) % pointsCount]], deltaY = coordinates[2*angles_Order[i] + 1] - coordinates[2*angles_Order[(i + 1) % pointsCount] + 1];
        result += sqrt(deltaX*deltaX + deltaY*deltaY);
    }
    return result;
}
int main()
{
    float coordinates[] = { 76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7,  21.3, 0.76};
    int pointsCount = sizeof(coordinates) / sizeof(coordinates[0]) / 2;
    printf("Result: %f", Travese_Clockwise(coordinates, pointsCount));
}
