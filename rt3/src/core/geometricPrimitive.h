#ifndef _GEOMETRIC_PRIMITIVE_H_
#define _GEOMETRIC_PRIMITIVE_H_

#include "primitive.h"
#include "sphere.h"
#include "material.h"

class GeometricPrimitive : public Primitive {

private:

    std::shared_ptr<Shape> shape;       //<! The shape that this class represents
    std::shared_ptr<Material> material; //<! The material of primitive

public:

    GeometricPrimitive ( std::shared_ptr<Shape> shape,
                         std::shared_ptr<Material> material)
                       : shape{shape}, material{material} {}

    ~GeometricPrimitive(){ /* Empty */ }

    bool intersect ( const Ray& r,
                     SurfaceInteraction * surface)
                     const
    { return shape->intersect(r, surface); }

    bool intersect_p( const Ray& r ) const 
    { return shape->intersect_p(r); }

    Bounds3 bounding_box () const 
    { return shape->bounding_box(); }

    std::shared_ptr<Material>
    get_material()
    { return this->material; }

};


#endif