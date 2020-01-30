
#ifndef __GRAPHIC_H_
#define __GRAPHIC_H_

typedef struct point_structure
{
	unsigned int x;
	unsigned int y;
}point;

typedef struct colour_structure
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
}colour;

/* Grafic Library should provide all colour definations */
#define CHART_MINCOLOUR_RED 0
#define CHART_MAXCOLOUR_RED 255

#define CHART_MINCOLOUR_BLUE 0
#define CHART_MAXCOLOUR_BLUE 255

#define CHART_MINCOLOUR_GREEN 0
#define CHART_MAXCOLOUR_GREEN 255

/* Graphic Library should provide rendering API */

#endif /* __GRAPHIC_H_ */