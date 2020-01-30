# Cplusplus--Projects

Code:
- The CompositeView can be easily extended into a MapView class with inheritance. The MapView can have multiple views with multiple charts in each MapView.
- Similarly, the ViewBuilder can be easily extended to build the MapView.
- Director should be a class.
- MODEL is kept isolated from the views, only builder understands MODEL.
- Any Graphic library can be used for rendering. I have mimicked a graphic.h for the demo code. The code is structured to easily adapt a new graphic.h by inheritance.

Test:
- Unit test for the code using GTest.
