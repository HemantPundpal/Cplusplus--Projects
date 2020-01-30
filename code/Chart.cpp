#include "Chart.h"

unsigned int Chart::iCnt = 0;

Chart::~Chart()
{
	iCnt--;
	cout << "In chart destructor" << endl;
}

bool Chart::getColour(point p, unsigned int &iColour)
{
	bool bStatus = false;
	/* check is p is within the chart */
	if (Chart::doPointOverlap(p))
	{
		iColour += (Chart::chartColour.blue + Chart::chartColour.red + Chart::chartColour.green);
		bStatus = true;
	}
	return bStatus;
}

point Chart::getPosition()
{
	return Chart::chartPosition;
}

point Chart::getSize()
{
	return Chart::chartSize;
}

bool Chart::doPointOverlap(point p)
{
	bool bStatus = false;
	/* check is p is within the chart */
	if (p.x <= Chart::chartSize.x)
	{
		if (p.y <= Chart::chartSize.y)
		{
			if (p.x >= Chart::chartPosition.x)
			{
				if (p.y >= Chart::chartPosition.y)
				{
					bStatus = true;
				}
			}
		}
	}

	return bStatus;
}
