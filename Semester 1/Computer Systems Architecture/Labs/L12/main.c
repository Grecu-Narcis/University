#include <stdio.h>

int convert(int);

int main()
{
    int a;
    
    scanf("%d", &a);
    
    while (a != 0)
    {
        printf("%o\n", convert(a));
        
        scanf("%d", &a);
    }
    
    return 0;
}