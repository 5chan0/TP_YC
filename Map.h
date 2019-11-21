#pragma once
#include "Vector3.h"
class Map {
public:
	Map(float x, float y);
	void setXYZ(float x, float y);
	Vector3 getXYZ() const { return xyz; }
	void set_assign(bool);
	bool get_assign();
	void set_search(bool);
	bool get_search();
	void set_line(int num);
	int get_line() const;
	int index;
private:
	Vector3 xyz;
	int line;
	bool assigned = false;
	bool searched = false;
	int color = -1; // 0~3, -1 means EMPTY
};