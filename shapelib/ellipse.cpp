#include "ellipse.h"

using namespace std;

shape::Ellipse::Ellipse(Point& center, double x_radius, double y_radius):
    x_radius_(shape::ThrowIsNegative(x_radius)),
    y_radius_(shape::ThrowIsNegative(y_radius)){
    type_shape_= shape::TypeShape::Ellipse;
    center_ = std::move(center);
}

shape::Point shape::Ellipse::GetPoint(double t) const{
    Point result(center_);
    result.x += x_radius_ * cos(t);
    result.y += y_radius_ * sin(t);
    return result;
}

shape::Point shape::Ellipse::GetVector(double t) const{
    Point result(center_);
    result.x = -x_radius_ * sin(t);
    result.y = y_radius_ * cos(t);
    return result;
}
