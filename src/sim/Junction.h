#ifndef __JUNCTION_H__
#define __JUNCTION_H__

#include "sim_local.h"
#include "Shape.h"
#include "Coord.h"

class CEdge : public CShape {
	class CJunction *a, *b;
public:
	CEdge(CJunction * _a, CJunction * _b) {
		this->a = _a;
		this->b = _b;
	}
	virtual const char *getClassName() const {
		return "CEdge";
	}
	float drawInformation2D(float x, float h);
	virtual void translate(const Coord &o);
	const Coord &getPositionA() const;
	const Coord &getPositionB() const;
	class CJunction *getOther(CJunction *x) {
		if (x == a)
			return b;
		return a;
	}
};

class CJunction : public CShape {
	std::string name;
	int gpioIndex;
	TArray<class CJunction *> linked;
	TArray<class CEdge*> myEdges;
	float voltage;
	int visitCount;
	bool bCurrentSource;
public:
	CJunction() {

	}
	CJunction(int _x, int _y, const char *s, int gpio = -1) {
		this->setPosition(_x, _y);
		this->name = s;
		this->gpioIndex = gpio;
		this->voltage = -1;
		this->visitCount = 0;
		this->bCurrentSource = false;
	}
	virtual ~CJunction();
	virtual CShape *cloneShape();
	void setCurrentSource(bool b) {
		bCurrentSource = b;
	}
	bool isCurrentSource() const {
		return bCurrentSource;
	}
	bool hasName(const char *s) const {
		return !stricmp(s, name.c_str());
	}
	float getVoltage() const {
		return voltage;
	}
	int getGPIO() const {
		return gpioIndex;
	}
	void setVoltage(float f) {
		voltage = f;
	}
	void setVisitCount(int i) {
		visitCount = i;
	}
	int getVisitCount() const {
		return visitCount;
	}
	float drawInformation2D(float x, float h);
	virtual const char *getClassName() const {
		return "CJunction";
	}
	bool shouldLightUpBulb(class CJunction *other);
	void translateLinked(const Coord &o);
	void setPosLinked(const Coord &o);
	void rotateDegreesAround_internal(float f, const Coord &p);
	void unlink(class CJunction *o);
	bool isWireJunction() const;
	void clearLinks() {
		linked.clear();
	}
	int getLinksCount() const {
		return linked.size();
	}
	class CJunction *getLink(int i) {
		return linked[i];
	}
	int getEdgesCount() const {
		return myEdges.size();
	}
	void addEdge(CEdge *ed) {
		myEdges.push_back(ed);
	}
	class CEdge *getEdge(int i) {
		return myEdges[i];
	}
	virtual bool isJunction() const {
		return true;
	}
	bool hasLinkedOnlyWires() const;
	virtual void translate(const Coord &o);
	void addLink(CJunction *j) {
		linked.add_unique(j);
	}
	virtual void drawShape();
};


#endif // __JUNCTION_H__