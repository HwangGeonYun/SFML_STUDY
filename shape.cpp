#include <cmath>
#include <math.h>
#include <vector>
#include <memory>
#include "shape.h"

std::vector<Shape> shape_list;
int next_id = 0;

void create_rectangle(Point& pos1, Point& pos2){
    int*pid = &next_id;
    Point cenPoint {(pos1.x + pos2.x)/2, (pos1.y + pos2.y)/2};
    int radius = std::min(abs(pos2.x - cenPoint.x), abs(pos2.y - cenPoint.y));
    shape_list.push_back(Shape{*pid, ShapeType::RECT, pos1, pos2, cenPoint, radius, nullptr, nullptr});
    (*pid)++;
}

void create_circle(Point& center, int radius){
    int* pid = &next_id;
    Shape createdCircle;
    Point leftBottom{abs(center.x-radius), abs(center.y - radius)};
    Point rightTop {abs(center.x + radius), abs(center.y + radius)};
    shape_list.push_back(Shape{*pid, ShapeType::CIRCLE, leftBottom, rightTop, center, radius, nullptr, nullptr});

    (*pid)++;
}

void move_shape(int id, int x, int y){
    auto movedShapeAddress = std::find_if(shape_list.begin(), shape_list.end(), [&id](const Shape& shape){
        return shape.id == id;
    });
    movedShapeAddress->pos1.x += x;
    movedShapeAddress->pos2.x += x;
    movedShapeAddress->pos1.y += y;
    movedShapeAddress->pos2.y += y;

    movedShapeAddress->center.x = x;
    movedShapeAddress->center.y = y;
}

float area(const Shape& shape){
    if(shape.type == ShapeType::RECT){
        return abs(shape.pos2.x - shape.pos1.x)*(abs(shape.pos2.y-shape.pos1.y));
    }
    else if(shape.type == ShapeType::CIRCLE){
        return shape.radius * shape.radius * 3.14;
    }
}

void sort_shapes(){
    std::sort(shape_list.begin(), shape_list.end(), [](Shape& shape1, Shape& shape2){
        return area(shape1) < area(shape2);
    });
}

int find_furthest_shape(){
    std::map<Shape, double> shapeAndDistance;

    std::max_element(shape_list.begin(), shape_list.begin(), [](const Shape& furthest, const Shape& shape){
        return sqrt(pow(furthest.center.x, 2) +pow(furthest.center.y, 2)) < sqrt(pow(shape.center.x,2) + pow(shape.center.y, 2));
    });
}

void remove_shape_by_id(int id){
    std::remove_if(shape_list.begin(), shape_list.end(), [&id](const Shape& shape){
        return shape.id == id;
    });
}

void select_center(Shape& shape, int& borderPoint){
    if(shape.type == ShapeType::CIRCLE){
        if(shape.radius > borderPoint){
            shape.center.x = shape.radius;
            shape.center.y = shape.radius;
        }
        else{
            shape.center.x = borderPoint + shape.radius;
            shape.center.y = borderPoint + shape.radius;
        }
        borderPoint += 2*shape.radius;
    }
    else if(shape.type == ShapeType::RECT){
        int width = abs(shape.pos2.x - shape.pos1.x);
        int height = abs(shape.pos2.y - shape.pos1.y);

        if(std::max(width/2, height/2) > borderPoint){
            shape.center.x = std::max(width/2, height/2);
            shape.center.y = std::max(width/2, height/2);
        }
        else{
            shape.center.x = borderPoint + std::max(width/2, height/2);
            shape.center.y = borderPoint + std::max(width/2, height/2);
        }
        shape.pos1.x = shape.center.x - width/2;
        shape.pos1.y = shape.center.y - height/2;
        shape.pos2.x = shape.center.x + width/2;
        shape.pos2.y = shape.center.y + height/2;
    }
}

void align_shapes(){
    sort_shapes();
    int borderPoint = 0;

    std::for_each(shape_list.begin(), shape_list.end(), [&borderPoint](Shape& shape){select_center(shape, borderPoint);});
}

void print_by_shapes(const Shape& shape){
    if(shape.type == ShapeType::RECT){
        std::cout << "ID:" << shape.id << ", Type: RECT, Position: ("
                  << shape.center.x << ", " << shape.center.y << "), Width: " << abs(shape.pos2.x - shape.pos1.x)
                  << ", Height: " << abs(shape.pos2.y - shape.pos1.y) <<", Area: " << area(shape);
    }
    else if(shape.type == ShapeType::CIRCLE){
        std::cout << "ID:" << shape.id << ", Type: CIRCLE, Position: ("
                  << shape.center.x << ", " << shape.center.y << "), Radius: " << shape.radius
                  <<", Area: " << area(shape);
    }
    std::cout << shape.id<<"\n";
}

void print_shapes(){
    std::for_each(shape_list.begin(), shape_list.end(), [](const Shape& shape){
        print_by_shapes(shape);
    });
}

void draw_shapes(sf::RenderWindow& window) {
    window.clear();
    for (auto& shape : shape_list) {

        //std::cout << "draw_shapes"; 잘돌아감
        if (shape.type == ShapeType::RECT) {
            shape.rect = std::make_unique<sf::RectangleShape>();
            //std::cout << "draw_shapes_setSize";
            shape.rect->setSize(sf::Vector2f(shape.pos2.x - shape.pos1.x, shape.pos2.y - shape.pos1.y));
            //std::cout << "draw_shapes_setPosition";
            shape.rect->setPosition(shape.pos1.x, shape.pos1.y);
            //std::cout << "draw_shapes_setFillcolor";
            shape.rect->setFillColor(sf::Color::White);
            //std::cout << "draw";
            window.draw(*shape.rect);
        } else {
            shape.circle = std::make_unique<sf::CircleShape>();
            //std::cout << "draw_shapes_set_radius";
            shape.circle->setRadius(shape.radius);
            //std::cout << "draw_shapes_setPosition_cir";
            shape.circle->setPosition(shape.center.x - shape.radius, shape.center.y - shape.radius);
            //std::cout << "draw_shapes_setfillcolor_cir";
            shape.circle->setFillColor(sf::Color::White);
            //std::cout << "draw_shapes_draw_cir";
            window.draw(*shape.circle);
        }
        std::shared_ptr<sf::CircleShape> point = std::make_shared<sf::CircleShape>();
        point->sf::CircleShape::setRadius(5);
        point->sf::CircleShape::setPosition(shape.center.x-5, shape.center.y-5);
        point->sf::CircleShape::setFillColor(sf::Color::Black);
        window.draw(*point);
    }
    window.display();
}
