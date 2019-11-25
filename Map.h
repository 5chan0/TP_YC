#pragma once
#include "Vector3.h"
#include "SolidSphere.h"

class Map {
public:
	Map(float x, float y);
	Map(const Map& map) {
		xyz = map.getXYZ();
		my_index = map.my_index;
		line = map.get_line();
		assigned = map.get_assign();
		searched = map.get_search();
		end = map.get_end();
		color = map.get_color();
		holding_sphere = map.holding_sphere;
	}
	void setXYZ(float x, float y);
	Vector3 getXYZ() const { return xyz; }
	SolidSphere* holding_sphere = nullptr;
	void set_assign(bool);
	bool get_assign() const;
	void set_search(bool);
	bool get_search() const;
	void set_line(int num);
	int get_line() const;
	void set_color(int col) { color = col; }
	int get_color() const { return color; }
	void set_end(int num) { end = num; }
	int get_end() const { return end; }
	void set_my_index(int num) { my_index = num; }
	int get_my_index() { return my_index; }
	void set_connected(int c) { connected = c; }
	int get_connected() { return connected; }
private:
	int my_index;
	Vector3 xyz;
	int line;
	bool assigned = false;
	bool searched = false;
	int connected = -1;
	int end = 0; // -1이면 왼쪽, 1이면 오른쪽
	int color = -1; // 0~3, -1 means EMPTY
};