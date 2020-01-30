
#ifndef __VIEW_H_
#define __VIEW_H_
#include "Graphic.h"
#include <iostream>

using namespace std;

class View
{
protected:
	View();
public:
	virtual ~View();

	virtual void addView(View *) {}
	virtual void removeView(View *) {}

	virtual bool getColour(point p, unsigned int &iColour) { return false; } // this can be returning signed int, where return of 0XFFFFFFFF is point does not overlap situation.
	virtual point getPosition() { point p; p.x = 0; p.y = 0; return p; }
	virtual point getSize() { point s; s.x = 0; s.y = 0; return s; }
	virtual bool doChartsOverlap() { return false;  }
	virtual bool doPointOverlap(point p) { return false;  }
	virtual bool deleteCharts() { return false; }
};

#endif /* __VIEW_H_ */

