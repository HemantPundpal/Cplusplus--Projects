#include "ConcreteViewBuilder.h"


ConcreteViewBuilder::ConcreteViewBuilder()
{
}


ConcreteViewBuilder::~ConcreteViewBuilder()
{
}

bool ConcreteViewBuilder::buildCompositeView(point viewPosition, point viewSize, colour viewColour)
{
	bool bStatus = false;
	if (!pCv)
	{
		ConcreteViewBuilder::checkAttributes(viewPosition, viewSize, viewColour);
		ConcreteViewBuilder::pCv = new CompositeView(viewPosition, viewSize, viewColour);
		iChartCount = 0;
		bStatus = true;
	}

	return bStatus;
}

bool ConcreteViewBuilder::buildChart(point chartPosition, point chartSize, colour chartColour)
{
	bool bStatus = false;
	if ((pCv) && (iChartCount < MAX_CHART))
	{
		ConcreteViewBuilder::checkAttributes(chartPosition, chartSize, chartColour);
		ConcreteViewBuilder::pCv->addView(new Chart(chartPosition, chartSize, chartColour));
		iChartCount++;
		bStatus = true;
	}

	return bStatus;
}

bool ConcreteViewBuilder::removeView(void)
{
	bool bStatus = false;

	if (pCv)
	{
		pCv->deleteCharts();
		delete pCv;
		iChartCount = 0;
		bStatus = true;
	}

	return bStatus;
}

CompositeView * ConcreteViewBuilder::getCompositeView()
{
	return ConcreteViewBuilder::pCv;
}

void ConcreteViewBuilder::checkAttributes(point position, point size, colour colour) throw (...)
{
	/* this a mock for model checks written for this example code, may not cover every condition */
	bool bStatus = true;
	if ((position.x > MAXSIZE_X) || (position.x < START_X) || (position.y > MAXSIZE_Y) || (position.y < START_Y))
	{
		throw Bad_View("Bad Position");
	}
	if ((size.x > MAXSIZE_Y) || (size.x < START_X) || (size.y > MAXSIZE_Y) || (size.y < START_Y))
	{
		throw Bad_View("Bad Size");
	}

	if (((size.x > position.x ? (size.x - position.x) : (MINSIZE_X - 1)) < MINSIZE_X)
		|| ((size.y > position.y ? (size.y - position.y) : (MINSIZE_Y - 1)) < MINSIZE_Y))
	{
		throw Bad_View("Bad Chart Dimension");
	}

	if ((colour.blue > CHART_MAXCOLOUR_BLUE) || (colour.blue < CHART_MINCOLOUR_BLUE)
		|| (colour.green > CHART_MAXCOLOUR_GREEN) || (colour.green < CHART_MINCOLOUR_GREEN)
		|| (colour.red > CHART_MAXCOLOUR_RED) || (colour.red < CHART_MINCOLOUR_RED))
	{
		throw Bad_View("Bad Colour");
	}
}