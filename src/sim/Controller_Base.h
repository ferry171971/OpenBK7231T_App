#ifndef __CONTROLLER_BASE_H__
#define __CONTROLLER_BASE_H__

#include "sim_local.h"

class CControllerBase {

public:
	virtual void onDrawn() { }
	virtual void sendEvent(int code) { }
	virtual void rotateDegreesAround(float f, const class Coord &p) { }
	// for buttons
	virtual class CJunction *findOtherJunctionIfPassable(class CJunction *ju) { return 0; }
};


#endif // __CONTROLLER_BASE_H__
