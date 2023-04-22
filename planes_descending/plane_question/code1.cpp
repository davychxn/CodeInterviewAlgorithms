// Davy Chen - April 21st, 2023 - Coding Test

#include "code1.h"

int maxDefendingPlanes(int* planePositions, int* planeDescendingSpeeds, int planeNum)
{
	int* landingSeconds = new int[planeNum];
	int* landingCounters = new int[planeNum];
	int minlandingSeconds = INT_MAX;
	// First time scan
	// Get landing time cost for each plane
	for (int i = 0; i < planeNum; i++)
	{
		int seconds = ceil((float)planePositions[i] / (float)planeDescendingSpeeds[i]);
		landingSeconds[i] = seconds;
		minlandingSeconds = minlandingSeconds > seconds ? seconds : minlandingSeconds;
		landingCounters[i] = 0;
	}

	int securePlaneNum = 0;
	// Second time scan
	// Get planes landing counts for each second
	for (int i2 = 0; i2 < planeNum; i2++)
	{
		if (landingSeconds[i2] < 0)
		{
			// Enough time to shoot, ignore them
			continue;
		}
		int distance = landingSeconds[i2] - minlandingSeconds;
		if (distance < planeNum)
		{
			landingCounters[distance]++;
		}
		else
		{
			// We always have enough time for those
			securePlaneNum++;
		}
	}

	int defendingCount = 0;
	// Third time scan
	// Count how many planes we can defend
	for (int i3 = 0; i3 < planeNum; i3++)
	{
		defendingCount += landingCounters[i3];
		int seconds = minlandingSeconds + i3;
		// We can defend 1 plane each second, can't defend more than time allows
		if (defendingCount >= seconds)
		{
			delete[] landingSeconds;
			delete[] landingCounters;
			return seconds;
		}
	}

	// We defended all!
	delete[] landingSeconds;
	delete[] landingCounters;
	return defendingCount + securePlaneNum;
}

int maxDefendingPlanesVerify(int* planePositions, int* planeDescendingSpeeds, int planeNum)
{
	int defendingCount = 0;
	int seconds = 0;
	int toLandNum = 0;
	int round = 1;
	while (true)
	{
		// Descend planes second by second
		round++;
		seconds++;
		for (int i = 0; i < planeNum; i++)
		{
			if (planePositions[i] <= 0)
			{
				// Already landed, ignore
				if (i == (planeNum - 1))
				{
					if (toLandNum == 0)
					{
						// All planes landed
						return planeNum;
					}
					else
					{
						// Round skipped, clear it
						toLandNum = 0;
					}
				}
				continue;
			}
			toLandNum++;
			// Do descending
			int position = planePositions[i] - planeDescendingSpeeds[i];
			planePositions[i] = position;
			if (position <= 0)
			{
				// Land now
				defendingCount++;
				if (defendingCount >= seconds)
				{
					// Time won't allow us to land more planes
					return seconds;
				}
			}
		}
		toLandNum = 0;
	}

	// All planes landed
	return planeNum;
}

bool run(int maxDescendingSpeed, int maxPlanesNum)
{
	int planesNum = (rand() % maxPlanesNum) + 1;
	int* planePositions = new int[planesNum];
	int* planeSpeeds = new int[planesNum];

	// Init input planes' data
	for (int i = 0; i < planesNum; i++)
	{
		planePositions[i] = (rand() % (maxDescendingSpeed * planesNum)) + 1;
		planeSpeeds[i] = (rand() % maxDescendingSpeed) + 1;
	}

	// Algorithm itself
	int max = maxDefendingPlanes(planePositions, planeSpeeds, planesNum);
	// Verification function
	int verify = maxDefendingPlanesVerify(planePositions, planeSpeeds, planesNum);
	printf("Maximum planes we can defend: %d. Verification: %d\n", max, verify);

	return (max == verify);
}
