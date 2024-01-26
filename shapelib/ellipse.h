#pragma once
#include "shape.h"

namespace shape{
class Ellipse : public Shape3D{
public:
    explicit Ellipse(Point&, double, double);

    Point GetPoint(double) const override;
    Point GetVector(double) const override;
private:
    double x_radius_;
    double y_radius_;
};
} // end namespace share
