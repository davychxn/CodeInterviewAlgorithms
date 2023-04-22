// Davy Chen - April 21st, 2023 - Coding Test

#include <iostream>
#include "code1.h"

int main()
{
    std::cout << "Hello World!\n";

    srand(time(NULL));

	// Settings
    int maxDescendingSpeed = 5;
    int maxPlanesNum = 20000000;
	int testNum = 200;
	int passCount = 0;

	// Verify correctness
	for (int i = 0; i < testNum; i++)
	{
		printf("Test #%d, planes number: %d\n", i + 1, maxPlanesNum);
		// Verfy here
		bool valid = run(maxDescendingSpeed, maxPlanesNum);
		if (valid)
		{
			passCount++;
			printf("PASS!!!\n");
		}
		else
		{
			printf("FAIL!!!\n");
		}
	}

	printf("\nTESTS: %d, PASS: %d, FAIL: %d\n", testNum, passCount, testNum - passCount);
}
