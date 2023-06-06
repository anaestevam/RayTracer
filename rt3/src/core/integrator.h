#ifndef INTEGRATOR_H
#define INTEGRATOR_H


#include "rt3.h"
#include "scene.h"
namespace rt3
{
class Integrator {
	public:
		virtual ~Integrator();
		virtual void render( const rt3::Scene& scene ) =0;
		virtual Integrator* create_integrator(const rt3::ParamSet &ps,rt3::Camera* cam );

};

}
#endif