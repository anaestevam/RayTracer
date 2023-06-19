#ifndef BOUNDS3F_H
#define BOUNDS3F_H

#include <limits>
#include <algorithm>
#include "rt3.h"

namespace rt3
{
class Bounds3 {

public:

    Vector3f pMin, pMax;

    Bounds3(){
        float minNum = std::numeric_limits<float>::lowest();
        float maxNum = std::numeric_limits<float>::max();
        pMin = Vector3f(maxNum, maxNum, maxNum);
        pMax = Vector3f(minNum, minNum, minNum);
    }

    virtual ~Bounds3() = default;

    Bounds3( const Vector3f &p ) 
        : pMin(p), pMax(p) 
        {  }

    Bounds3 ( const Vector3f &p1, const Vector3f &p2 )
        : pMin{ Vector3f {std::min(p1[0], p2[0]), 
                        std::min(p1[1], p2[1]), 
                        std::min(p1[2], p2[2])} },
          pMax{ Vector3f {std::max(p1[0], p2[0]), 
                        std::max(p1[1], p2[1]),
                        std::max(p1[2], p2[2])} } 
        {  }

    const Vector3f  &operator[] (int i) const;

    Vector3f &operator[](int i);

    Vector3f corner( int corner ) const {

        return Vector3f ( (*this)[(corner & 1)][0],
                        (*this)[(corner & 2) ? 1 : 0][1],
                        (*this)[(corner & 4) ? 1 : 0][2] );
    }

    Bounds3 get_union( const Bounds3 &b, const Vector3f &p){

        return Bounds3(

            Vector3f {std::min(b.pMin[0], p[0]),
                    std::min(b.pMin[1], p[1]),
                    std::min(b.pMin[2], p[2])},

            Vector3f {std::max(b.pMax[0], p[0]),
                    std::max(b.pMax[1], p[1]),
                    std::max(b.pMax[2], p[2])}
            );
    }

    Bounds3 get_union( const Bounds3 &b1, const Bounds3 &b2 ){
        return Bounds3(
            Vector3f (std::min(b1.pMin[0], b2.pMin[0]),
                    std::min(b1.pMin[1], b2.pMin[1]),
                    std::min(b1.pMin[2], b2.pMin[2])),
            Vector3f (std::max(b1.pMax[0], b2.pMax[0]),
                    std::max(b1.pMax[1], b2.pMax[1]),
                    std::max(b1.pMax[2], b2.pMax[2])));
    }

    Bounds3 intersect( const Bounds3 &b1, const Bounds3 &b2 ){
        return Bounds3(
            Vector3f (std::max(b1.pMin[0], b2.pMin[0]),
                    std::max(b1.pMin[1], b2.pMin[1]),
                    std::max(b1.pMin[2], b2.pMin[2])),
            Vector3f (std::min(b1.pMax[0], b2.pMax[0]),
                    std::min(b1.pMax[1], b2.pMax[1]),
                    std::min(b1.pMax[2], b2.pMax[2])));        
    }

    bool overlaps(const Bounds3 &b1, const Bounds3 &b2) {

        bool x = ( b1.pMax[0] >= b2.pMin[0] ) && ( b1.pMin[0] <= b2.pMax[0] );
        bool y = ( b1.pMax[1] >= b2.pMin[1] ) && ( b1.pMin[1] <= b2.pMax[1] );
        bool z = ( b1.pMax[2] >= b2.pMin[2] ) && ( b1.pMin[2] <= b2.pMax[2] );

        return ( x && y && z );

    }

    bool inside(const Vector3f &p, const Bounds3 &b) {
        return (p[0] >= b.pMin[0] && p[0] <= b.pMax[0] &&
                p[1] >= b.pMin[1] && p[1] <= b.pMax[1] &&
                p[2] >= b.pMin[2] && p[2] <= b.pMax[2]);
    }

    bool inside_exclusive(const Vector3f &p, const Bounds3 &b) {
        return (p[0] >= b.pMin[0] && p[0] < b.pMax[0] &&
                p[1] >= b.pMin[1] && p[1] < b.pMax[1] &&
                p[2] >= b.pMin[2] && p[2] < b.pMax[2]);
    }

    Bounds3 expand(const Bounds3 &b, float delta);

    Vector3f diagonal() const;

    float surface_area() const;

    float volume () const;

    int maximum_extent() const;

    Vector3f offset( const Vector3f &p ) const;

    void bounding_to_sphere ( Vector3f *center, float *radius );

};
} // namespace rt3

#endif