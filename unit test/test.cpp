#include "view.h"
#include "Chart.h"
#include "Graphic.h"
#include "Model.h"
#include "CompositeView.h"

/* JUST A DEMO - Can be enhanced to check all boundary */

class Bad_Chart
{
private:

public:
	string sErr;
	Bad_Chart(string s) : sErr(s) { }
};

void checkAttributes(point position, point size, colour colour) throw (...)
{
	/* this a mock for model checks, does not cover every condition */
	bool bStatus = true;
	if ((position.x > MAXSIZE_X) || (position.x < START_X) || (position.y > MAXSIZE_Y) || (position.y < START_Y))
	{
		throw Bad_Chart("Bad Position");
	}
	if ((size.x > MAXSIZE_Y) || (size.x < START_X) || (size.y > MAXSIZE_Y) || (size.y < START_Y))
	{
		throw Bad_Chart("Bad Size");
	}

	if(((size.x > position.x ? (size.x - position.x) : (MINSIZE_X - 1)) < MINSIZE_X)
		|| ((size.y > position.y ? (size.y - position.y) : (MINSIZE_Y - 1)) < MINSIZE_Y))
	{
		throw Bad_Chart("Bad Chart Dimension");
	}

	if ((colour.blue > CHART_MAXCOLOUR_BLUE) || (colour.blue < CHART_MINCOLOUR_BLUE)
		|| (colour.green > CHART_MAXCOLOUR_GREEN) || (colour.green < CHART_MINCOLOUR_GREEN)
		|| (colour.red > CHART_MAXCOLOUR_RED) || (colour.red < CHART_MINCOLOUR_RED))
	{
		throw Bad_Chart("Bad Colour");
	}
}

struct MyChartTest : public testing::Test
{
	point p;
	point s;
	colour c;
	CompositeView *pCv = NULL;
	Chart *pCh1 = NULL;
	Chart *pCh2 = NULL;
	unsigned int iColour = 0;

	void SetUp()
	{
		try
		{
			/* View Size */
			p.x = 0;
			p.y = 0;
			s.x = 100;
			s.y = 100;
			/* White */
			c.blue = 255;
			c.red = 255;
			c.green = 255;

			for (int i = 0; i < MAX_MAPVIEW; i++)
			{
				checkAttributes(p, s, c);
				pCv = new CompositeView(p, s, c);
			}

			for (int i = 0; i < MAX_CHART; i++)
			{
				switch (i)
				{
				case 0:
					s.x = 70;
					s.y = 70;
					c.blue = 255;
					c.red = 0;
					c.green = 0;
					checkAttributes(p, s, c);
					pCh1 = new Chart(p, s, c);
					if (pCv && pCh1)
					{
						pCv->addView(pCh1);
					}
					break;
				case 1:
					p.x = 30;
					p.y = 30;
					s.x = 90;
					s.y = 90;
					c.blue = 0;
					c.red = 255;
					c.green = 0;
					checkAttributes(p, s, c);
					pCh2 = new Chart(p, s, c);
					if (pCv && pCh2)
					{
						pCv->addView(pCh2);
					}
					break;
				default:
					cout << "only two charts per MapView" << endl;
					break;
				}//switch close
			}//for close
		}
		catch (Bad_Chart bc)
		{
			cout << "/*******************************EXCEPTION: " << bc.sErr << endl;
		}
		catch (...)
		{
			cout << "/*******************************EXCEPTION: something is wrong" << endl;
		}
	
	}
	
	void TearDown() 
	{
		delete pCh1;
		delete pCh2;
		delete pCv;
	}
};

TEST(InitialTest, TestName_0)
{
	EXPECT_EQ((Chart::iCnt), 0);
}

TEST_F(MyChartTest, TestName_1)
{
	//checkAttributes(p, s, c);
	EXPECT_EQ((Chart::iCnt), 2);
	EXPECT_EQ(pCh1->getPosition().x, 0);
	EXPECT_EQ(pCh1->getPosition().y, 0);
	EXPECT_EQ(pCh1->getSize().x, 70);
	EXPECT_EQ(pCh1->getSize().y, 70);
}

TEST_F(MyChartTest, TestName_2)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 90;
	p.y = 20;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), false);
	EXPECT_EQ(pCh1->doPointOverlap(p), false);
	ASSERT_EQ(iColour, 0);
}

TEST_F(MyChartTest, TestName_3)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 70;
	p.y = 50;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), true);
	EXPECT_EQ(pCh1->doPointOverlap(p), true);
	ASSERT_EQ(iColour, 255);
}

TEST_F(MyChartTest, TestName_4)
{
	EXPECT_EQ((Chart::iCnt), 2);
	EXPECT_EQ(pCh2->getPosition().x, 30);
	EXPECT_EQ(pCh2->getPosition().y, 30);
	EXPECT_EQ(pCh2->getSize().x, 90);
	ASSERT_EQ(pCh2->getSize().y, 90);
}

TEST_F(MyChartTest, TestName_5)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 90;
	p.y = 20;
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), false);
	EXPECT_EQ(pCh2->doPointOverlap(p), false);
	ASSERT_EQ(iColour, 0);
}

TEST_F(MyChartTest, TestName_6)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 90;
	p.y = 50;
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), true);
	EXPECT_EQ(pCh2->doPointOverlap(p), true);
	ASSERT_EQ(iColour, 255);
}

TEST_F(MyChartTest, TestName_7)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 90;
	p.y = 50;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), true);
	ASSERT_EQ(iColour, 255);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), true);
	ASSERT_EQ(iColour, 255);
}

TEST_F(MyChartTest, TestName_8)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 50;
	p.y = 50;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), true);
	ASSERT_EQ(iColour, 255);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), true);
	ASSERT_EQ(iColour, 255);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), true);
	ASSERT_EQ(iColour, 510);
}

TEST_F(MyChartTest, TestName_9)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 95;
	p.y = 95;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), true);
	ASSERT_EQ(iColour, 765);
}

struct MyCompositViewTest : public testing::Test
{
	point p;
	point s;
	colour c;
	CompositeView *pCv = NULL;
	Chart *pCh1 = NULL;
	Chart *pCh2 = NULL;
	unsigned int iColour = 0;

	void SetUp()
	{
		try
		{
			/* View Size */
			p.x = 0;
			p.y = 0;
			s.x = 100;
			s.y = 100;
			/* White */
			c.blue = 255;
			c.red = 255;
			c.green = 255;

			for (int i = 0; i < MAX_MAPVIEW; i++)
			{
				checkAttributes(p, s, c);
				pCv = new CompositeView(p, s, c);
			}

			for (int i = 0; i < MAX_CHART; i++)
			{
				switch (i)
				{
				case 0:
					s.x = 30;
					s.y = 30;
					c.blue = 255;
					c.red = 0;
					c.green = 0;
					checkAttributes(p, s, c);
					pCh1 = new Chart(p, s, c);
					if (pCv && pCh1)
					{
						pCv->addView(pCh1);
					}
					break;
				case 1:
					p.x = 31;
					p.y = 31;
					s.x = 90;
					s.y = 90;
					c.blue = 0;
					c.red = 255;
					c.green = 0;
					checkAttributes(p, s, c);
					pCh2 = new Chart(p, s, c);
					if (pCv && pCh2)
					{
						pCv->addView(pCh2);
					}
					break;
				default:
					cout << "only two charts per MapView" << endl;
					break;
				}//switch close
			}//for close
		}
		catch (Bad_Chart bc)
		{
			cout << "/*******************************EXCEPTION: " << bc.sErr << endl;
		}
		catch (...)
		{
			cout << "something is wrong" << endl;
		}

	}

	void TearDown()
	{
		delete pCh1;
		delete pCh2;
		delete pCv;
	}
};

TEST_F(MyCompositViewTest, TestName_10)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 90;
	p.y = 50;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), true);
	ASSERT_EQ(iColour, 255);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), false);
	ASSERT_EQ(iColour, 255);
}

TEST_F(MyCompositViewTest, TestName_11)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 23;
	p.y = 25;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), true);
	ASSERT_EQ(iColour, 255);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), false);
	ASSERT_EQ(iColour, 255);
}

TEST_F(MyCompositViewTest, TestName_12)
{
	EXPECT_EQ((Chart::iCnt), 2);
	p.x = 35;
	p.y = 30;
	iColour = 0;
	EXPECT_EQ(pCh1->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCh2->getColour(p, iColour), false);
	ASSERT_EQ(iColour, 0);
	iColour = 0;
	EXPECT_EQ(pCv->getColour(p, iColour), true);
	EXPECT_EQ(pCv->doPointOverlap(p), true);
	EXPECT_EQ(pCv->doChartsOverlap(), false);
	ASSERT_EQ(iColour, 765);
}

