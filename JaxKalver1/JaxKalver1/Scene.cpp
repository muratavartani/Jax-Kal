#include "Scene.h"

using namespace JAX;
/// All this constructor does is set the windowPtr 
Scene::Scene(Window& windowRef) : windowPtr(&windowRef) {}
Scene::~Scene() {}