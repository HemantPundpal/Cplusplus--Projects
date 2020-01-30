// View_Chart.cpp : This file contains the 'main' function. Program execution begins and ends there.
// THIS IS A DEMO CONTROL CODE USING THE VIEW

#include <string>
#include <iostream>
#include <sstream>
#include "CompositeView.h"
#include "Graphic.h"
#include "ConcreteViewBuilder.h"

using namespace std;

/* Director can be a Class, this is a mock */
CompositeView * DirectorBuildView(ConcreteViewBuilder * pViewBuilder)
{
	point p;
	point s;
	colour c;

	/* View Size */
	p.x = 0;
	p.y = 0;
	s.x = 100;
	s.y = 100;
	/* White */
	c.blue = 255;
	c.red = 255;
	c.green = 255;
	/* Build View */
	pViewBuilder->buildCompositeView(p, s, c);
	
	/* Chart 1 Size */
	s.x = 70;
	s.y = 70;
	/* Blue */
	c.blue = 255;
	c.red = 0;
	c.green = 0;
	/* Build Chart */
	pViewBuilder->buildChart(p, s, c);

	/* Chart 2 Size */
	p.x = 30;
	p.y = 30;
	s.x = 90;
	s.y = 90;
	/* Red */
	c.blue = 0;
	c.red = 255;
	c.green = 0;
	pViewBuilder->buildChart(p, s, c);

	return pViewBuilder->getCompositeView();
}


bool DirectorRemoveView(ConcreteViewBuilder * pViewBuilder)
{
	return pViewBuilder->removeView();
}

int main()
{
	point p;
	CompositeView *pCv = NULL;
	unsigned int iColour = 0;
	ConcreteViewBuilder *pViewBuilder = new ConcreteViewBuilder();
	
	try
	{
		pCv = DirectorBuildView(pViewBuilder);
		p.x = 90;
		p.y = 20;
		iColour = 0;
		pCv->getColour(p, iColour);
		cout << "colour: " << iColour << endl;
		cout << "Overlap: " << (pCv->doChartsOverlap() ? "TRUE" : "FALSE") << endl;

		DirectorRemoveView(pViewBuilder);
	}
	catch (Bad_View bv)
	{
		cout << "/*******************************EXCEPTION: " << bv.sErr << endl;
	}
	catch (...)
	{
		cout << "/*******************************EXCEPTION: something is wrong" << endl;
	}

	return 0;
}
