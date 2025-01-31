#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "sim_local.h"
#include "Coord.h"
#include "Bounds.h"


class CShape {
	bool bActive;
	CShape *parent;
	TArray<class CShape*> shapes;
	class CControllerBase *controller;
	float rotationAccum;
	//class CControlelrBase *referencedController;
	
	virtual void rotateDegreesAround_internal(float f, const Coord &p);
	virtual void recalcBoundsSelf() {}
protected:
	bool bFill;
	Bounds bounds;
	Coord pos;
public:
	CShape() {
		parent = 0;
		controller = 0;
		bActive = true;
		bFill = false;
		rotationAccum = 0;
	}
	void snapToGrid();
	void cloneShapeTo(CShape *o);
	virtual CShape *cloneShape();
	void setFill(bool b) {
		bFill = b;
	}
	void setActive(bool b) {
		bActive = b;
	}
	bool isActive() const {
		return bActive;
	}
	class CControllerBase *findOwnerController_r() {
		CShape *c = this;
		while (c) {
			if (c->getController() != 0)
				return c->getController();
			c = c->parent;
		}
		return 0;
	}
	virtual ~CShape();
	virtual const char *getClassName() const {
		return "CShape";
	}
	float drawInformation2D(float x, float y);
	virtual float drawPrivateInformation2D(float x, float y);
	int getShapesCount() const {
		return shapes.size();
	}
	CShape *getShape(int s) {
		return shapes[s];
	}
	void setParent(CShape *p) {
		parent = p;
	}
	const CShape *getParent() const {
		return parent;
	}
	CShape *getParent() {
		return parent;
	}
	float positionDistance(const CShape *o) const {
		return getPosition().dist(o->getPosition());
	}
	float absPositionDistance(const CShape *o) const {
		return getAbsPosition().dist(o->getAbsPosition());
	}
	virtual float moveTowards(const Coord &tg, float dt);
	void setController(CControllerBase *c) {
		controller = c;
	}
	CControllerBase *getController() {
		return controller;
	}
	const Bounds &getBounds() const {
		return bounds;
	}
	const Coord &getPosition() const {
		return pos;
	}
	Coord getAbsPosition() const;
	void setPosition(const Coord &c) {
		pos = c;
	}
	CShape* setPosition(float nX, float nY) {
		pos.set(nX, nY);
		return this;
	}
	void translate(float oX, float oY) {
		translate(Coord(oX, oY));
	}
	float getRotationAccum() const {
		return rotationAccum;
	}
	virtual void translate(const Coord &o);
	float getX() const {
		return pos.getX();
	}
	float getY() const {
		return pos.getY();
	}
	virtual bool isWire() const {
		return false;
	}
	virtual bool isJunction() const {
		return false;
	}
	virtual void drawWithChildren(int depth);
	virtual void drawShape() { }

	void rotateDegreesAround(float f, const Coord &p);
	void rotateDegreesAroundSelf(float f);
	class CShape* addLine(int x, int y, int x2, int y2);
	class CShape* addRect(int x, int y, int w, int h);
	class CShape* addCircle(float x, float y, float r);
	class CShape* addText(int x, int y, const char *s);
	class CJunction* addJunction(int x, int y, const char *name = "", int gpio = -1);
	class CShape* addShape(CShape *p);
	void recalcBoundsAll();
	bool hasWorldPointInside(const Coord &p)const;
	bool hasLocalPointInside(const Coord &p)const;
	void translateEachChild(float oX, float oY);
};

#endif 

