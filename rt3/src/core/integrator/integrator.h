#ifndef INTEGRATOR_H
#define INTEGRATOR_H


#include "../rt3.h"
#include "../scene.h"

namespace rt3
{
class Integrator {

	public:
        Integrator(Camera *camera) : camera(camera) {}
    	virtual ~Integrator() = default;
		virtual void render( const Scene& scene ) =0;
        // virtual void preprocess(const Scene& scene)  = 0;

     Camera* camera;

};

}
#endif