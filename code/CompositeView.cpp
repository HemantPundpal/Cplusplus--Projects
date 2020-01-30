#include "CompositeView.h"


CompositeView::~CompositeView()
{
	CompositeView::viewList.clear();
	cout << "In composite view destructor" << endl;
}

void CompositeView::addView(View * v)
{
	CompositeView::viewList.push_back(v);
}

void CompositeView::removeView(View * v)
{
	/* Does not delete the Chart, creater can reuse the Chart */
	CompositeView::viewList.remove(v);
}

bool CompositeView::deleteCharts()
{
	bool bStatus = false;

	list<View *>::iterator i = CompositeView::viewList.begin();
	for (; i != CompositeView::viewList.end(); ++i)
	{
		bStatus = true;
		delete (*i);
	}

	CompositeView::viewList.clear();
	return bStatus;
}

list<View *>::iterator CompositeView::createIterator()
{
	return CompositeView::viewList.begin();
}

bool CompositeView::getColour(point p, unsigned int &iColour)
{
	unsigned int iCount = 0, iTempColour = 0;
	bool bStatus = false;
	
	list<View *>::iterator i = CompositeView::viewList.begin();

	if (CompositeView::doPointOverlap(p))
	{
		bStatus = true;
		for (; i != CompositeView::viewList.end(); ++i)
		{
			if ((*i)->getColour(p, iTempColour))
			{
				iCount++;
				iColour += iTempColour;
				iTempColour = 0;
			}
		}
	}

	if (iCount == 0)
	{
		iColour = (CompositeView::viewColour.blue + CompositeView::viewColour.red + CompositeView::viewColour.green);
	}

	return iColour;
}


bool CompositeView::doChartsOverlap() 
{
	point ch1_p, ch1_s, ch2_p, ch2_s;
	bool bOverlap = false;
	
	if (viewList.size() <= 1)
	{
		return bOverlap;
	}
	
	list<View *>::iterator i = viewList.begin();
	ch1_p = (*i)->getPosition();
	ch1_s = (*i)->getSize();
	++i;
	ch2_p = (*i)->getPosition();
	ch2_s = (*i)->getSize();
	
	/* x = lenght and y = breath */
	
	/* line overlap is not-concidered as overlap */
		
	/* is Ch1 Above or below Ch2 */
	if (!(ch1_s.y <= ch2_p.y)) 
	{
		/* this means Ch1 is not above Ch2 */

		if (!(ch2_s.y <= ch1_p.y))
		{
			/* this means Ch1 is not below Ch2 */
			
			/* may be Ch1 on left or on right of Ch2 */
			if (!(ch1_s.x <= ch2_p.x))
			{
				/* this means Ch1 is not on left if Ch2 */

				if (!(ch2_s.x <= ch1_p.x))
				{
					/* this means CH1 is not on right of Ch2 */

					/* OK - Overlap */
					bOverlap = true;
				}
			}
				
		}
	}

	return bOverlap;
}

bool CompositeView::doPointOverlap(point p)
{
	bool bStatus = false;
	/* check is p is within the chart */
	if (p.x <= (CompositeView::viewSize.x))
	{
		if (p.y <= (CompositeView::viewSize.y))
		{
			if (p.x >= CompositeView::viewPosition.x)
			{
				if (p.y >= CompositeView::viewPosition.y)
				{
					bStatus = true;
				}
			}
		}
	}

	return bStatus;
}
