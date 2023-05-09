#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 10002

char num[MAX_DIGITS];
char largest[MAX_DIGITS];
char dig[2];
int carry, digit, t, c, z, n, one, max, count, length;

int main(int argc, char *argv[])
{   
    if (argc == 1)
    {
        printf("\n== Collatz Conjecture Calculator (for large numbers) - Shpati Koleka, MMXXI ==\n");
        printf("\nInput value: ");
        fgets(num, MAX_DIGITS, stdin);
    }
    else
    {
        strncpy(num, argv[1], MAX_DIGITS - 1);
        num[MAX_DIGITS - 1] = '\0';
        if ((argc < 3))
            printf("\nInput value: %s\n", num);
    }

    length = (int)strlen(num);
    for (int i = length; i > -1; i--)
        num[i + 1] = num[i];
    num[0] = '0';
    length++;
    max = 0;
    count = 0;
    one = 1;

    if ((argc < 3))
        printf("\nSequence: ");

    while (one != 0)
    {
        // Add trailing zero if first character is not zero
        if (num[0] != '0')
        {
            for (int i = length; i > -1; i--)
                num[i + 1] = num[i];
            num[0] = '0';
            length++;
        }

        // Remove trailing zeroes and print number string
        z = 0;
        n = 0;
        count++;
        one++;
        if ((one != 2) && ((argc < 3)))
            printf(", ");
        for (int i = 0; i < length; i++)
        {
            c = z;
            if (num[i] != '0')
                z = 1;
            if (z == 1)
            {
                if ((argc < 3))
                    printf("%c", num[i]);
                n++;
            }
        }

        if (max < n)
        {
            max = n;
            strncpy(largest, num, MAX_DIGITS);
        }
        if (max == n)
        {
            if ((largest[1] - '0') < (num[1] - '0'))
                strncpy(largest, num, MAX_DIGITS);
        }

        // Find the one
        if ((c == 0) && (num[length - 1] == '1'))
            one = 0;

        if (num[length - 1] % 2 == 0)
        {
            // Even number
            carry = 0;
            for (int i = 0; i < length; i++)
            {
                t = ((num[i] - '0') + carry * 10);
                digit = t / 2;
                sprintf(dig, "%d", digit);
                if (t != 0)
                    num[i] = dig[0];
                carry = t % 2;
            }
        }
        else
        {
            // Odd number
            carry = 0;
            for (int i = length - 1; i > -1; i--)
            {
                t = (num[i] - '0') * 3 + carry;
                digit = t % 10;
                carry = (t - digit) / 10;
                sprintf(dig, "%d", digit);
                num[i] = dig[0];
            }
            carry = 1;
            for (int i = length - 1; i > -1; i--)
            {
                t = (num[i] - '0') + carry;
                digit = t % 10;
                carry = (t - digit) / 10;
                sprintf(dig, "%d", digit);
                num[i] = dig[0];
                if (carry == 0)
                    break;
            }
        }
    }

    // Print the number of steps
    if ((argc < 3))
        printf("\n");
    if ((argc < 4))
        printf("\nSteps:");
    printf(" %d ", count - 1);

    // Print largest value
    if ((argc < 4))
        printf("\n\nLargest value: ");
    printf("%s\n", largest);

    return 0;
}
