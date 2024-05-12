#include "circle.hpp"
#include <cmath> 
#include <iostream>


Circle::Circle(Point center, std::string name, int radius)
    : Shape(center, name), radius(radius) {}

double Circle::area() const {
    return 3.1415 * radius * radius;
}

void Circle::draw(std::ostream& out) const {
    for (int y = -radius; y <= radius; y += 2) {
        for (int x = -radius; x <= radius; ++x) {
            out << (x * x + y * y <= radius * radius ? '*' : ' ');
        }
        out << '\n';
    }
}

Circle* Circle::clone() const {
    return new Circle(*this);
}
