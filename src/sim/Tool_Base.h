#ifndef __TOOL_BASE_H__
#define __TOOL_BASE_H__

#include "sim_local.h"

class Tool_Base {
protected:
	class CSimulator *sim;
public:
	Tool_Base() {
		sim = 0;
	}
	void setSimulator(class CSimulator *s) {
		this->sim = s;
	}
	virtual const char *getName() const {
		return "UnnamedTool";
	}
	virtual void onKeyDown(int button) {

	}
	virtual void onMouseDown(const class Coord &pos, int button) {

	}
	virtual void onMouseUp(const class Coord &pos, int button) {

	}
	virtual void drawTool() {

	}
	virtual void onBegin() {

	}
	virtual void onEnd() {

	}
	virtual int drawTextStats(int h) {
		return h;
	}
};

#endif // __TOOL_BASE_H__
