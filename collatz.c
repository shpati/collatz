#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char num[256];
char largest[256];
char dig[1];
int carry, digit, t, c, z, n, one, max, count, length;

int main(int argc, char *argv[]) 
{	
	if (argc == 1)
	{
		printf("\n== Collatz Conjecture Calculator (for large numbers) - Shpati Koleka, MMXXI ==\n");
		printf("\nInput value: %s",num);
		gets(num);
	}
	else
	{
		strcpy(num, argv[1]);
		if ((argc < 3))
			printf("\nInput value: ");
		printf("%s",num);
		if ((argc < 3))
			printf("\n");
	}

	length = (char) strlen(num);
	for (int i = length; i > -1; i--)
		num[i+1] = num[i];
	num[0] = '0';
	length++;
	max = 0;
	count = 0;
	one = 1;

	if ((argc < 3))
		printf("\nSequence: \n");
	while (one != 0)
	{
		// Add trailing zero if first character is not zero
		if (num[0] != '0')
		{	
			for (int i = length; i > -1; i--)
				num[i+1] = num[i];
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
			//largest = (char *) malloc(length); --> for when using dynamic arrays
			for (int i = 0; i < length; i++)
					largest[i] = num[i];
		}
		if (max == n)
			if ((largest[1] - '0') < (num[1] - '0'))
				for (int i = 0; i < length; i++)
					largest[i] = num[i];

		// Find the one
		if ((c == 0) && (num[length-1] == '1'))
			one = 0;

		// The below line is needed for debugging only
		//printf(" : %d %d %c %d %d %d\n", strlen(num), length, num[length-1], count-1, n, max);

		if (num[length - 1] % 2 == 0)
		{	// Even number
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
		{	// Odd number
			carry = 0;
			for (int i = length - 1 ; i > -1; i--)
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
		printf("\n\nSteps:");
	printf(" %d ", count-1);

	// Print largest value
	if ((argc < 3))
		printf("\n\nLargest value: ");
	for (int i = 1; i < length; i++)
		printf("%c", largest[i]);
	printf("\n");

	free(num);
	free(largest);

	return 0;
}