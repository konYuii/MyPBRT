#include "Core\FeimosRender.h"
#include "Shape\Sphere.h"


namespace Feimos {

Bounds3f Sphere::ObjectBound() const {
    return Bounds3f(Point3f(-radius, -radius, -radius),
                    Point3f(radius, radius, radius));
}

float Sphere::Area() const { return 4 * Pi * radius * radius; }



}










