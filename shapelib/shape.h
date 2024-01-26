#pragma once

#include <vector>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <cmath>


namespace shape{

#define Z_COORDINATE 0

struct Point{
    double x;
    double y;
    double z = Z_COORDINATE;
};

enum class TypeShape{
    Circle,
    Ellipse,
    Helix
};

class Shape3D{
public:
    Shape3D() = default;
    Shape3D(Shape3D&) = delete;
    Shape3D(Shape3D&&) = delete;
    Shape3D& operator=(Shape3D&) = delete;
    Shape3D& operator=(Shape3D&&) = delete;

    virtual Point GetPoint(double) const = 0;
    virtual Point GetVector(double) const = 0;

    TypeShape GetType() const { return type_shape_;}
    Point GetCenter(){return center_;}

    virtual ~Shape3D(){}

protected:
    Point center_;  
    TypeShape type_shape_;
};

inline double ThrowIsNegative(double radius){
    if(radius < 0){
        throw std::runtime_error("Negative radius");
    }
    return radius;
}
} //end namespase Shape
