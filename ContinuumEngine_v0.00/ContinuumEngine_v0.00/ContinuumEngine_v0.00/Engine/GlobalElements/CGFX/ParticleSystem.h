#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "../../Renderer/GameObject/GameObject.h"

struct Particle
{
	GameObject* particle = nullptr;
	glm::vec3 velocity = glm::vec3(0.0f);
	float lifetime = 1.0f;
	float currentLife = 0.0f;

	Particle()
	{

	}

	Particle(Model* model_, glm::vec3 scale_, glm::vec3 rotation_)
	{
		particle = new GameObject(model_);
		particle->SetScale(scale_);
		particle->SetRotation(rotation_);
	}
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void CreateSystem(Model* particle_, int particleAmount_, glm::vec3 particleScale_, glm::vec3 particleRotation_, glm::vec3 minVel_, glm::vec3 maxVel_, float minLifetime_, float maxLifetime_);
	void CreateSystem(Model* particle_, Model* secondaryParticle_, int particleAmount_, glm::vec3 particleScale_, glm::vec3 particleRotation_, glm::vec3 minVel_, glm::vec3 maxVel_, float minLifetime_, float maxLifetime_);
	void SetOrigin(glm::vec3 origin_);
	glm::vec3 GetOrigin();
	void SetRotationSpeed(float rotSpeed_);
	void StartSystem();
	void StopSystem();

	float Randomize(float min_, float max_);
	void SetGravity(float gravScale_);
	void SetInitialBurst(bool doesBurst_);

	void Update(float delataTime_);
	void Render(Camera* camera_);
private:
	std::vector<Particle*> particles;
	glm::vec3 origin;
	int particleAmount;
	glm::vec3 particleScale;
	glm::vec3 minVelocity, maxVelocity;
	float minLifetime, maxLifetime;
	glm::vec3 acceleration = glm::vec3(1.0f);
	float rotationSpeed = 1.0f;
	bool initialBurst = false;
	bool isPlaying;
};


#endif // !PARTICLESYSTEM_H