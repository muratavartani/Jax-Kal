#include "SceneEnvironment.h"

namespace JAX {

	std::unique_ptr<JAX::SceneEnvironment> JAX::SceneEnvironment::instance(nullptr);


	JAX::SceneEnvironment* SceneEnvironment::getInstance()
	{
		if (instance.get() == nullptr) {
			/// I originally set the unique_ptr to be null in the constructor - 
			/// reset() sets the new address
			instance.reset(new SceneEnvironment());
		}
		return instance.get();
	}
}
