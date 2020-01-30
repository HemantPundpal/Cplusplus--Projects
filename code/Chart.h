
#ifndef __CHART_H_
#define __CHART_H_

#include "View.h"
#include <iostream>

class Chart : public View
{
private:
	point chartPosition;
	point chartSize;
	colour chartColour;
	//void checkChartAttributes(point position, point size, colour colour) throw (...);

public:
	static unsigned int iCnt;
	Chart() = delete;
	Chart(point chartPosition, point chartSize, colour chartColour) :
		chartPosition(chartPosition), chartSize(chartSize), chartColour(chartColour) {
		iCnt++;
		cout << "In Chart Constructor - " << iCnt << endl;
	}
	virtual ~Chart();
	
	virtual bool getColour(point p, unsigned int &iColour);
	virtual point getPosition();
	virtual point getSize();
	virtual bool doPointOverlap(point p);
};

#endif /* __CHART_H_ */