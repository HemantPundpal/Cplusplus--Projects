
#ifndef __VIEWBUILDER_H_
#define __VIEWBUILDER_H_

#include "Graphic.h"
#include "Chart.h"
#include "CompositeView.h"

class ViewBuilder
{
protected:
	ViewBuilder();
public:
	virtual ~ViewBuilder();

	virtual bool buildCompositeView(point viewPosition, point viewSize, colour viewColour) { return false; }
	virtual bool buildChart(point chartPosition, point chartSize, colour chartColour) { return false; }
	virtual bool removeView(void) { return false; }
	virtual CompositeView * getCompositeView() { return NULL; }
};

#endif /* __VIEWBUILDER_H_ */