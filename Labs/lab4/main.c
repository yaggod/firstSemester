#include <stdio.h>

#define MEMBERS_COUNT 5

int IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int ParseSubexpression(char *expression, int *coefficient, int *power)
{
    int coefficientSign = 1;
    int foundAnyDigit = 0;
    *coefficient = 0;
    *power = 1;

    int lastIndex;
    for(lastIndex = 0; expression[lastIndex] != 'x'; lastIndex++)
    {
        char currentChar = expression[lastIndex];

        if(currentChar == '-')
            coefficientSign = -1;
        if(IsDigit(currentChar))
        {
            *coefficient *= 10;
            *coefficient += currentChar - '0';
            foundAnyDigit = 1;
        }
        else
        {
            if(foundAnyDigit && currentChar != '*')
            {
                *power = 0;
                *coefficient *= coefficientSign;
                return lastIndex;
            }
        }
    }
    if(*coefficient == 0)
        *coefficient = 1;
    *coefficient *= coefficientSign;
    if(expression[++lastIndex] == '^')
    {
        *power = expression[++lastIndex] - '0';
        lastIndex++;
    }
        return lastIndex;
}

double NaturalPower(double value, int power)
{
    double result = 1;
    for(int i = 0; i < power; i++)
        result *= value;
    return result;
}

double Polynome(char* expression, double x)
{
    double result = 0;
    int coefficients[MEMBERS_COUNT] = { 0 };
    while(*expression)
    {
        int currentMemberCoefficient = 0 ;
        int currentMemberPower = 0;
        int subexpressionEndIndex = ParseSubexpression(expression, &currentMemberCoefficient, &currentMemberPower);
        coefficients[currentMemberPower] = currentMemberCoefficient;

        expression += subexpressionEndIndex;
    }
    for(int i = 0; i < MEMBERS_COUNT; i++)
        result += coefficients[i] * NaturalPower(x, i);
    return result;
}


int main()
{
    char *expression = "x^4+15*x^3-3*x^2+x-2";
    double x = 1;

    printf("P(x) = %s\nP(%f) = %f", expression, x, Polynome(expression, x));
    return 0;
}
