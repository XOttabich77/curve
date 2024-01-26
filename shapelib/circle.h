#pragma once
#include "shape.h"

namespace shape{
class Circle : public Shape3D{
public:
    explicit Circle(Point&,double);

    Point GetPoint(double) const override;
    Point GetVector(double) const override;
    double GetRadius(){return radius_;}
private:
    double radius_;
};
} // end namespace share
