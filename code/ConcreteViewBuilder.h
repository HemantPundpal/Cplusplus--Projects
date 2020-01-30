
#ifndef __CONCRETEVIEWBUILDER_H_
#define __CONCRETEVIEWBUILDER_H_

#include "ViewBuilder.h"
#include "Model.h"

class Bad_View
{
private:

public:
	string sErr;
	Bad_View(string s) : sErr(s) { }
};

class ConcreteViewBuilder :
	public ViewBuilder
{
private: 
	CompositeView *pCv = NULL;
	unsigned int iChartCount = 0;
protected:
	void checkAttributes(point position, point size, colour colour) throw (...);
public:
	ConcreteViewBuilder();
	virtual ~ConcreteViewBuilder();

	virtual bool buildCompositeView(point viewPosition, point viewSize, colour viewColour);
	virtual bool buildChart(point chartPosition, point chartSize, colour chartColour);
	virtual bool removeView(void);
	virtual CompositeView * getCompositeView();
};

#endif /* __CONCRETEVIEWBUILDER_H_ */