
#ifndef __COMPOSITEVIEW_H_
#define __COMPOSITEVIEW_H_

#include "View.h"
#include <list>
#include <iostream>

using namespace std;

class CompositeView : public View
{
private:
	point viewPosition;
	point viewSize;
	colour viewColour;
	list <View *> viewList;
public:
	CompositeView() = delete;
	CompositeView(point viewPosition, point viewSize, colour viewColour) :
		viewPosition(viewPosition), viewSize(viewSize), viewColour(viewColour) {
		cout << "In Composite View Constructor" << endl;
	}
	virtual ~CompositeView();

	void addView(View * v);
	void removeView(View * v);
	list<View *>::iterator createIterator();

	bool getColour(point p, unsigned int &iColour);
	virtual point getPosition() { return viewPosition; };
	virtual point getSize() { return viewSize; };
	virtual bool doChartsOverlap();
	virtual bool doPointOverlap(point p);
	virtual bool deleteCharts();
};

#endif /* __COMPOSITEVIEW_H_ */