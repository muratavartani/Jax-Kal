#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Entity.h"

namespace JAX {

	using namespace MATH;

	class Model : public Entity {

	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

		unsigned int textureID[2];

	public:

		Model(const Vec3 _pos, const Vec3 _orientation);
		Model(const Model&) = delete;
		Model(Model&&) = delete;
		Model& operator = (const Model&) = delete;
		Model& operator = (Model&&) = delete;

		Vec3 getModelOrientation();

		virtual ~Model();

		void setPos(const Vec3& pos_) override;
		void setOrientation(const Vec3& orienration_) override;
		void setRotationMatrix(const Matrix4& mat);

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);

	protected:

		void updateModelMatrix();
	};
} /// end of namespace

#endif