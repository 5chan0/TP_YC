#pragma once
#include "Vector3.h"
class Map {
public:
	Map();
	Map(float x, float y);
	Map(const Map& map) {
		xyz = map.getXYZ();
		my_index = map.my_index;
		line = map.get_line();
		assigned = map.get_assign();
		searched = map.get_search();
		end = map.get_end();
		color = map.get_color();
		holding_sphere_index = map.holding_sphere_index;
	}
	void setXYZ(float x, float y);
	Vector3 getXYZ() const { return xyz; }
	void set_assign(bool);
	bool get_assign() const;
	void set_search(bool);
	bool get_search() const;
	void set_line(int num);
	int get_line() const;
	int my_index;
	int holding_sphere_index;
	void set_color(int col) { color = col; }
	int get_color() const { return color; }
	void set_end(int num) { end = num; }
	int get_end() const { return end; }
private:
	Vector3 xyz;
	int line;
	bool assigned = false;
	bool searched = false;
	int end = 0; // -1이면 왼쪽, 1이면 오른쪽
	int color = -1; // 0~3, -1 means EMPTY
};