#ifndef SHAPE_SHAPE_H
#define SHAPE_SHAPE_H

#include <iostream>
#include <algorithm>
#include <map>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

enum class ShapeType{
    RECT,
    CIRCLE
};

struct Point{
    int x;
    int y;
};

struct Shape{
    int id;
    ShapeType type;
    Point pos1;
    Point pos2;
    Point center;
    int radius;
    std::unique_ptr<sf::RectangleShape> rect;
    std::unique_ptr<sf::CircleShape> circle;
};

void create_rectangle(Point& pos1, Point& pos2);
void create_circle(Point& center, int radius);
void move_shape(int id, int x, int y);
void sort_shapes();
int find_furthest_shape();
void remove_shape_by_id(int id);
void align_shapes();
void print_shapes();
void draw_shapes(sf::RenderWindow& window);

#endif //SHAPE_SHAPE_H