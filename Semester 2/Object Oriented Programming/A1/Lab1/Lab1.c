#include <stdio.h>


// We create our own Vector type.
typedef struct
{
    int arr[100];
    int size;
} Vector;

/*
    Reads a vector of integer numbers.
    Input: ~
    Output: v ~ Vector
*/
Vector readVector()
{
    Vector a;
    a.size = 0;
    printf("Input elements of the array(stops at 0): \n");
    do {
        scanf("%d", &a.arr[a.size++]);
    } while (a.arr[a.size - 1]);
    a.size--;
    return a;
}


/*
    Checks if the number(element variable) is Prime or not.
    Input: a number - limit
    Output: 1 if element is prime, 0 if it is not.
*/
int isPrime(int element)
{
    int flag = 0;
    if (element < 2)
        return 0;
    else
    {
        for (int i = 2; i <= element/2; ++i)
        {
            
            if (element % i == 0)
                flag = 1;
        }
    }
    if (flag)
        return 0;
    else
        return 1;
}


/*
    Finds out the longest subsequence such that the sum of 2 consecutive numbers is a prime number.
    Input: Vector
    Output: Longest subsequence of that requirement
*/
void longestSequence(Vector v, int* startIdx, int* endIdx) 
{
    int i = 0, counter = 0, maxx = 0;
    for (i = 0; i < v.size - 1; i++)
    {
        if (isPrime(v.arr[i] + v.arr[i + 1]))
        {
            counter++;
        }
        else
        {
            if (counter > maxx)
            {
                maxx = counter;
                counter = 1;
                *endIdx = i;
                *startIdx = i - maxx;
            }
        }
    }
    if (counter > maxx)
    {
        maxx = counter;
        counter = 1;
        *endIdx = i;
        *startIdx = i - maxx;
    }
}


/*
    Prints the longest sequence to the user.
    Input: Vector
    Output: Longest sequence from startIdx to endIdx
*/
void printLongestSeq(Vector v, int startIdx, int endIdx) 
{
    for (int i = startIdx; i <= endIdx; i++)
        printf("%d ", v.arr[i]);
}

int main()
{
    int option;
    while (1)
    {
        printf("Choose an option: \n");
        printf("1. Generate all the prime numbers smaller than a given natural number n \n");
        printf("2. Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number. \n");
        printf("3. exit \n");
        scanf("%d", &option);
        if (option == 1)
        {
            int n;
            printf("Number: ");
            scanf("%d", &n);
            for (int i = 2; i <= n; i++)
            {
                if (isPrime(i))
                {
                    printf("%d \n", i);
                }
            }
        }
        else if (option == 2)
        {
            int startIdx = 0, endIdx = 0;
            Vector v = readVector();
            printf("The longest subsequence is: \n");
            longestSequence(v, &startIdx, &endIdx);
            printLongestSeq(v, startIdx, endIdx);
        }
        else if (option == 3)
            return 0;
    }
    return 0;
}
