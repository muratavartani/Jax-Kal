#include "ParticleSystem.h"



ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
	for (Particle* p : particles)
	{
		delete p;
		p = nullptr;
	}
}

void ParticleSystem::CreateSystem(Model* particle_, int particleAmount_, glm::vec3 particleScale_, glm::vec3 particleRotation_, glm::vec3 minVel_, glm::vec3 maxVel_, float minLifetime_, float maxLifetime_)
{
	particleAmount = particleAmount_;
	particles = std::vector<Particle*>(particleAmount);
	for (int i = 0; i < particleAmount; i++)
	{
		particles[i] = new Particle(particle_, particleScale_, particleRotation_);
	}
	minVelocity = minVel_;
	maxVelocity = maxVel_;
	minLifetime = minLifetime_;
	maxLifetime = maxLifetime_;
}

void ParticleSystem::CreateSystem(Model* particle_, Model* secondaryParticle_, int particleAmount_, glm::vec3 particleScale_, glm::vec3 particleRotation_, glm::vec3 minVel_, glm::vec3 maxVel_, float minLifetime_, float maxLifetime_)
{
	particleAmount = particleAmount_;
	particles = std::vector<Particle*>(particleAmount);
	for (int i = 0; i < particleAmount; i++)
	{
		if (i % 2 == 0)
			particles[i] = new Particle(particle_, particleScale_, particleRotation_);
		else
			particles[i] = new Particle(secondaryParticle_, particleScale_, particleRotation_);
	}
	minVelocity = minVel_;
	maxVelocity = maxVel_;
	minLifetime = minLifetime_;
	maxLifetime = maxLifetime_;
}

void ParticleSystem::SetOrigin(glm::vec3 origin_)
{
	origin = origin_;
}

glm::vec3 ParticleSystem::GetOrigin()
{
	return origin;
}

void ParticleSystem::SetRotationSpeed(float rotSpeed_)
{
	rotationSpeed = rotSpeed_;
}

void ParticleSystem::StartSystem()
{
	isPlaying = true;
}

void ParticleSystem::StopSystem()
{
	isPlaying = false;
}

float ParticleSystem::Randomize(float min_, float max_)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max_ - min_;
	float r = random * diff;
	return min_ + r;
}

void ParticleSystem::SetGravity(float gravScale_)
{
	acceleration.y = -9.8 * gravScale_;
}

void ParticleSystem::SetInitialBurst(bool doesBurst_)
{
	initialBurst = doesBurst_;
}

void ParticleSystem::Update(const float deltaTime_)
{
	if (isPlaying)
	{
		for (int i = 0; i < particleAmount; i++)
		{
			if (particles[i]->currentLife == 0.0f)
			{
				particles[i]->velocity.x = Randomize(minVelocity.x, maxVelocity.x);
				particles[i]->velocity.y = Randomize(minVelocity.y, maxVelocity.y);
				particles[i]->velocity.z = Randomize(minVelocity.z, maxVelocity.z);
				particles[i]->lifetime = Randomize(minLifetime, maxLifetime);
				particles[i]->particle->SetPosition(glm::vec3(Randomize(origin.x - 0.1, origin.x + 0.1), Randomize(origin.y - 0.1, origin.y + 0.1), Randomize(origin.z - 0.1, origin.z + 0.1)));
			}
			particles[i]->particle->SetPosition(particles[i]->particle->GetPosition() + ((particles[i]->velocity * deltaTime_ + (0.5f * acceleration * deltaTime_* deltaTime_))));
			particles[i]->particle->SetAngle(particles[i]->particle->GetAngle() + (deltaTime_ * Randomize(0.0f, rotationSpeed)));
			particles[i]->currentLife += deltaTime_;
			if (particles[i]->currentLife >= particles[i]->lifetime)
			{
				particles[i]->particle->SetPosition(glm::vec3(Randomize(origin.x - 0.1f, origin.x + 0.1f), Randomize(origin.y - 0.1f, origin.y + 0.1f), Randomize(origin.z - 0.1f, origin.z + 0.1f)));
				particles[i]->currentLife = 0.0f;
			}
		}
	}
}

void ParticleSystem::Render(Camera* camera_)
{
	if (isPlaying)
	{
		for (Particle* p : particles)
		{
			p->particle->GetModel()->Render(camera_,"baseShader");
		}
	}
}