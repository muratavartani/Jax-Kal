#ifndef GAME_H
#define GAME_H

#include "../Engine/Renderer/Graphics/RenderMachine.h"
#include <glm/gtx/string_cast.hpp>
class Game : public GameInterface
{
public:
	Game();
	virtual ~Game();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();
private:
	Model * model;
	Model * model1;
	Model * model2;
	Model * model3;
	Model * model4;
	Model * model5;
	std::vector<Model*> models;
	GameObject* object1;
	GameObject* object2;
	GameObject* object3;
	GameObject* object4;
	GameObject* object5;
	
	float delta = 0.0f;
};

#endif