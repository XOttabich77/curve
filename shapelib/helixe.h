#pragma once
#include "shape.h"

namespace shape{
class Helixe : public Shape3D{
public:
    explicit Helixe(Point&, double, double);

    Point GetPoint(double) const override;
    Point GetVector(double) const override;
private:
    double radius_;
    double step_;
};
} // end namespace share
