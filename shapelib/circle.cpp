#include "circle.h"

using namespace std;

shape::Circle::Circle(Point& center,double radius):
    radius_(shape::ThrowIsNegative(radius)){
    type_shape_= shape::TypeShape::Circle;
    center_ = std::move(center);
}
shape::Point shape::Circle::GetPoint(double t) const{
    Point result(center_);
    result.x += radius_ * cos(t);
    result.y += radius_ * sin(t);
    return result;
}

shape::Point shape::Circle::GetVector(double t) const{
    Point result(center_);
    result.x = -radius_ * sin(t);
    result.y = radius_ * cos(t);
    return result;
}
