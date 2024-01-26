#include "helixe.h"

using namespace std;

shape::Helixe::Helixe(Point& center, double radius, double step):
    radius_(shape::ThrowIsNegative(radius)),
    step_(step){
   // type_shape_="Helixe"s;
    type_shape_= shape::TypeShape::Helix;
    center_ = std::move(center);
}

shape::Point shape::Helixe::GetPoint(double t) const{
    Point result(center_);
    result.x += radius_ * cos(t) * t;
    result.y += radius_ * sin(t) * t;
    result.z += step_ * t;
    return result;
}

shape::Point shape::Helixe::GetVector(double t) const{
    Point result(center_);
    result.x = radius_ * (cos(t) - t * sin(t));
    result.y = radius_ * (sin(t) + t * cos(t));
    result.z = step_;
    return result;
}
