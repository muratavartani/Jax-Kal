#ifndef GAME_H
#define GAME_H

#include "../Engine/ContinuumEngine.h"
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
	GameObject* object1;
};

#endif