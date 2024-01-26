#include <iostream>
#include <memory>
#include <algorithm>
#include <random>
#include <execution>
#include <thread>
#include <omp.h>

#include "shapelib/circle.h"
#include "shapelib/ellipse.h"
#include "shapelib/helixe.h"

#include "log_duration.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;
using namespace shape;

using Object = std::shared_ptr<Shape3D>;
using ObjectCircle = std::shared_ptr<Circle>;

double SumRadiusParallel(vector<ObjectCircle>& obj){
    [[maybe_unused]] size_t cores_count = thread::hardware_concurrency();

    double sum = 0;
    size_t i ;
    #pragma omp parallel shared(obj, i) reduction (+: sum) num_threads(cores_count)
    {
        # pragma omp for
        for(i = 0; i < obj.size(); ++i){
            sum += obj[i]->GetRadius();
        }
    }
    return sum;
}

double RandomArgument(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(-100000,100000);
    return static_cast<double>(dist(gen)) / 1000 ;
}

ostream& operator <<(ostream& os, const Point& point){
    os <<" X = "s <<point.x
       <<" Y = "s <<point.y
       <<" Z = "s <<point.z;
    return os;
}

ostream& operator <<(ostream& os, const TypeShape& type_shape){
    switch (type_shape) {
    case shape::TypeShape::Circle :
        os << "Circle "s;
        break;
    case shape::TypeShape::Ellipse :
        os << "Ellipse "s;
        break;
    case shape::TypeShape::Helix :
        os << "Helix "s;
    }
    return os;
}

int main(){

    const size_t object_count = 200;
    const double t = M_PI/4;

    vector<Object> object;
    object.reserve(object_count);
    for(size_t i = 0; i <object_count;++i){
        Point center({RandomArgument(),RandomArgument(),0});
        double radius = std::abs(RandomArgument());
        int variant = (static_cast<int>(RandomArgument()) % 3);
        if(variant == 0){
            object.emplace_back(std::make_shared<Circle>(center,radius));
        } else if(variant == 1){
            double y_radius = std::abs(RandomArgument());
            object.emplace_back(std::make_shared<Ellipse>(center,radius,y_radius));
        } else {
            double step = RandomArgument();
            center.z = RandomArgument();
            object.emplace_back(std::make_shared<Helixe>(center,radius,step));
        }
        cout  << "Created: " <<object.back()->GetType() <<"with Center :"<< object.back()->GetCenter() <<", t=PI/4 Point: " <<object.back()->GetPoint(t) << ", Vector: " << object.back()->GetVector(t) <<endl;
    }

    vector<ObjectCircle> only_cicrle;
    for(const auto& el:object){
        if(el->GetType() == TypeShape::Circle){
            only_cicrle.emplace_back(dynamic_pointer_cast<Circle>(el));
        }
    }

    auto pred = [](const ObjectCircle& a,const ObjectCircle& b){return a->GetRadius() < b->GetRadius();};
    {
        LOG_DURATION("Sequence Sort Time: "s);
        //STL
        sort(only_cicrle.begin(),only_cicrle.end(),pred);
    }

    {
        LOG_DURATION("Parallel Sort Time: "s);
        // Parallel
        sort(std::execution::par, only_cicrle.begin(),only_cicrle.end(),pred);
    }
    {
        LOG_DURATION("Sequence Time: "s);
        double sum_sequence  = accumulate(only_cicrle.begin(),only_cicrle.end(),0.0,[](double s, auto el ){return s+=el->GetRadius();});
        cout << "Sequence Sum : " <<sum_sequence <<endl;
    }
    {
        LOG_DURATION("Parallel Time: "s);
        double sum_parallel = SumRadiusParallel(only_cicrle);
        cout << "Parallel Sum : " <<sum_parallel <<endl;
    }


}
