#ifndef RENDERMACHINE_H
#define RENDERMACHINE_H

#include <vector>
#include "../../ContinuumEngine.h"


class RenderMachine
{
public:
	RenderMachine(const RenderMachine&) = delete;
	RenderMachine(RenderMachine&&) = delete;
	RenderMachine& operator=(const RenderMachine&) = delete;
	RenderMachine& operator=(RenderMachine&&) = delete;

	static RenderMachine* GetInstance();
	void Render(std::vector<Model*> models_, float delta_);
	Skybox* SkyboxObj;

private:
	RenderMachine();
	~RenderMachine();

	static std::unique_ptr<RenderMachine> RenderMachineInstance;
	friend std::default_delete<RenderMachine>;

	float delta;

};

#endif