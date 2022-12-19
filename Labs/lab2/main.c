#include <stdio.h>

#define UNKNOWN_DIGIT -1
#define ERROR_VALUE -234962347

#define SWAP(first, second) { int temp = first; first = second; second = temp; }

int GetIndexOf(char character, char *source)
{
    for(int i = 0; source[i]; i++)
    {
        if (source[i] == character)
            return i;
    }
    return -1;
}

void ApplyOperators(char *operators, char *expression)
{
    operators[0] = expression[1];
    operators[1] = expression[3];
}

int CharToDigit(char character)
{
    if(character >= '0' && character <= '9')
        return character - '0';
    return UNKNOWN_DIGIT;
}

void ApplyValues(int *buffer, char *expression)
{
    buffer[0] = CharToDigit(expression[0]);
    buffer[1] = CharToDigit(expression[2]);
    buffer[2] = CharToDigit(expression[4]);
}

void SwapSides(char *operators, int *values)
{
    if(operators[0] == '=')
    {
        SWAP(values[0], values[1]);
    }
    else
    {
        SWAP(values[0], values[2]);
    }
    SWAP(values[1], values[2]);
    SWAP(operators[0], operators[1]);
}

void GetExpressionPattern(char* buffer, char *operators, int *values)
{
    buffer[1] = operators[0];
    buffer[3] = operators[1];
    for(int i = 0; i < 3; i++)
        if(values[i] == UNKNOWN_DIGIT)
            buffer[2*i] = 'x';

}

int GetSolutionForUnknownBaseMod(int value, int modResult)
{
    int result;
    int resultsCount = 0;
    for(int i = 1; i <= value / 2; i++)
    {
        if(value%i == modResult)
        {
            result = i;
            resultsCount++;
        }
    }
    return resultsCount == 1 ? result : ERROR_VALUE;
}


int IsSimilarStrings(char *first, char *second)
{
    int result = 1;
    for(int i = 0; first[i] && second[i]; i++)
    {
        if(first[i] != second[i])
            return 0;
    }
    return 1;
}

int GetSolutionFromPattern(char *pattern, char *operators, int *values)
{
    int first = values[0];
    int second = values[1];
    int third = values[2];
    if(IsSimilarStrings(pattern,"d+x=d")) // Свитч не завезли
        return third - first;
    else if(IsSimilarStrings(pattern,"x-d=d"))
        return third + second;
    else if(IsSimilarStrings(pattern,"d*x=d"))
        return third / first;
    else if(IsSimilarStrings(pattern,"x/d=d"))
        return third * second;
    else if(IsSimilarStrings(pattern,"x+d=d"))
        return third - second;
    else if(IsSimilarStrings(pattern,"d-x=d"))
        return first - third;
    else if(IsSimilarStrings(pattern,"x*d=d"))
        return third / second;
    else if(IsSimilarStrings(pattern,"d/x=d"))
        return first / third;
    else if(IsSimilarStrings(pattern,"d%x=d"))
        return GetSolutionForUnknownBaseMod(first, third);
    else if(IsSimilarStrings(pattern,"x=d+d"))
        return second + third;
    else if(IsSimilarStrings(pattern,"x=d-d"))
        return second - third;
    else if(IsSimilarStrings(pattern,"x=d*d"))
        return second * third;
    else if(IsSimilarStrings(pattern,"x=d/d"))
        return second / third;
    else if(IsSimilarStrings(pattern,"x=d%d"))
        return second % third;



    return ERROR_VALUE;
}

int Calculate(char *expression)
{
    char operators[2];
    int values[3];
    ApplyOperators(operators, expression);
    ApplyValues(values, expression);
    int rootIndex = GetIndexOf('x', expression);
    int equalityIndex = GetIndexOf('=', expression);
    if(rootIndex > equalityIndex)
        SwapSides(operators, values);
    char expressionPattern[6] = "ddddd";

    GetExpressionPattern(expressionPattern, operators, values);
    return GetSolutionFromPattern(expressionPattern, operators, values);
    return 0;
}


int main()
{
    printf("Started!\n");
    char *expressions[] =
    {
        "5+x=9",
        "5-x=9",
        "2*x=4",
        "6/x=3",
        "x+5=9",
        "x-5=9",
        "x*2=4",
        "x/2=4",
        "x=8+5",
        "x=8-5",
        "x=8*5",
        "x=8/2",
        "x=8%5",
    };
    int expressionsCount = sizeof(expressions) / sizeof(char*);
    for(int i = 0; i < expressionsCount; i++)
    {
        printf("%s x = %d\n", expressions[i], Calculate(expressions[i]));

    }

    //Calculator("2+5=x");

}

