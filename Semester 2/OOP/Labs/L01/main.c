#include <stdio.h>

void printMenu()
{
	printf("Press 1 to compute square root.\n");
	printf("Press 2 to read a vector of numbers.\n");
	printf("Press 3 to find the longest contiguous subsequence.\n");
	printf("Press 4 to exit.\n");
}


float computeSquareOfNumber(float numberToCompute)
{
	return numberToCompute * numberToCompute;
}


float computeAbsoluteValue(float numberToCompute)
{
	if (numberToCompute < 0)
		numberToCompute *= -1;

	return numberToCompute;
}


float computeSquareRoot(float numberToCompute, float precision)
{
	float lowerBound = 0, upperBound = numberToCompute;
	float result = 0;

	while (lowerBound < upperBound)
	{
		float squareRootApproximation = (lowerBound + upperBound) / 2;

		if (computeAbsoluteValue(computeSquareOfNumber(squareRootApproximation) - numberToCompute) < precision)
		{
			result = squareRootApproximation;
			break;
		}

		else if (computeSquareOfNumber(squareRootApproximation) < numberToCompute)
			lowerBound = squareRootApproximation;

		else
			upperBound = squareRootApproximation;
	}

	return result;
}


int isPrime(int numberToCheck)
{
	if (numberToCheck < 2)
		return 0;

	if (numberToCheck == 2)
		return 1;

	if (numberToCheck % 2 == 0)
		return 0;

	for (int divisor = 3; divisor * divisor <= numberToCheck; divisor += 2)
		if (numberToCheck % divisor == 0)
			return 0;

	return 1;
}

void readVectorOfNumbers(int numbers[], int numberOfElements)
{
	for (int i = 0; i < numberOfElements; i++)
		scanf("%d", &numbers[i]);
}

int findLongestContiguousSubsequence(int numbers[], int numberOfElements)
{
	int maximumLength = 0, currentLength = 1, longestSequenceStart = 0, longestSequenceEnd = 0;
	int currentSequenceStart = 0;

	for (int i = 1; i < numberOfElements; i++)
	{
		if (isPrime(numbers[i] - numbers[i - 1]))
			currentLength++;

		else
		{
			if (currentLength > maximumLength)
			{
				maximumLength = currentLength;
				longestSequenceStart = currentSequenceStart;
				longestSequenceEnd = i - 1;
			}

			currentLength = 1;
			currentSequenceStart = i;
		}
	}

	if (currentLength > maximumLength)
	{
		maximumLength = currentLength;
		longestSequenceStart = currentSequenceStart;
		longestSequenceEnd = numberOfElements - 1;
	}

	printf("The sequence is: ");

	for (int i = longestSequenceStart; i <= longestSequenceEnd; i++)
		printf("%d ", numbers[i]);

	printf("\n");

	return maximumLength;
}

int main()
{
	char userOption;
	int userNumbers[101] = {0}, numberOfElements = 0;

	while (1)
	{
		printMenu();

		printf("Your option is: ");
		scanf("%c", &userOption);
		
		if (userOption == '\n')
			continue;

		if (userOption == '1')
		{
			float userNumberForSquareRoot, userPrecision;

			printf("Enter number to compute square root: ");
			scanf("%f", &userNumberForSquareRoot);

			printf("Enter precision for square root computation: ");
			scanf("%f", &userPrecision);

			printf("The square root is: %f\n", computeSquareRoot(userNumberForSquareRoot, userPrecision));
		}

		else if (userOption == '2')
		{
			printf("Enter the number of elements to read: ");
			scanf("%d", &numberOfElements);

			readVectorOfNumbers(userNumbers, numberOfElements);
		}

		else if (userOption == '3')
		{
			printf("The maximum length is: %d\n", findLongestContiguousSubsequence(userNumbers, numberOfElements));
		}

		else if (userOption == '4')
		{
			break;
		}

		else
			printf("Invalid option!\n");
	}

	return 0;
}