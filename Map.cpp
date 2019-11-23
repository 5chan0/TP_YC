#include "Map.h"
#include "Vector3.h"

Map::Map(float x, float y) { setXYZ(x, y); }
void Map::setXYZ(float x, float y) { this->xyz[0] = x; this->xyz[1] = y; this->xyz[2] = 0; }
void Map::set_assign(bool num) { this->assigned = num; }
bool Map::get_assign() const { return assigned; }
void Map::set_search(bool num) { this->searched = num; }
bool Map::get_search() const { return searched; }
void Map::set_line(int num) { this->line = num; }
int Map::get_line() const { return this->line; }