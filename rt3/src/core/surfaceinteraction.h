#ifndef SURFACE_INTERACTION_H
#define SURFACE_INTERACTION_H

#include "rt3.h"

namespace rt3
{
class SurfaceInteraction {

public:

    SurfaceInteraction( const Point3f&p, const Vector3f&n, const Vector3f&wo,
                        float time, const Point2f uv, const Primitive *pri)
                    :   p{p}, n{n}, wo{wo}, time{time}, uv{uv}, 
                        primitive{pri} 
                    {  };

    SurfaceInteraction (){}
    
    ~SurfaceInteraction(){}

    SurfaceInteraction (Point3f p) : p{p}{}

     SurfaceInteraction& operator= ( const SurfaceInteraction &s ){
        this->p = s.p;
        this->n = s.n;
        this->wo = s.wo;
        this->time = s.time;
        this->uv = s.uv;
        this->m = s.m;
        this->primitive = primitive;
        this->t = t;

        return *this;
    }

    Point3f p;    
    Vector3f n;    
    Vector3f wo;   
    float time;  
    Point2f uv;  
    Material * m;  
    const Primitive *primitive = nullptr; 

    float t; 

};
}
#endif