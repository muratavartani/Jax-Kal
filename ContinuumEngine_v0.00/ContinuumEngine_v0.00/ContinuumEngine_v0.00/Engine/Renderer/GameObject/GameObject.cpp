#include "GameObject.h"



GameObject::GameObject(Model* model_) : position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)) {
	model = model_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		BoundaryBox = model->GetBoundaryBox();
		BoundaryBox.transform = model->GetTransform(modelInstance);

	}
}

GameObject::GameObject(Model* model_, glm::vec3 position_) : position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)) {
	model = model_;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		BoundaryBox = model->GetBoundaryBox();
		BoundaryBox.transform = model->GetTransform(modelInstance);
	}
}


GameObject::~GameObject() {
	/*if (model) {
	delete model;
	}*/
	model = nullptr;
}


void GameObject::SetPosition(glm::vec3 position_) {
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);

		BoundaryBox.transform = model->GetTransform(modelInstance);
	}
}
void GameObject::SetAngle(float angle_) {
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);

		BoundaryBox.transform = model->GetTransform(modelInstance);
	}
}
void GameObject::SetRotation(glm::vec3 rotation_) {
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);

		BoundaryBox.transform = model->GetTransform(modelInstance);
	}
}
void GameObject::SetScale(glm::vec3 scale_) {
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);

		BoundaryBox.transform = model->GetTransform(modelInstance);
	}
}

glm::vec3 GameObject::GetPosition() const {
	return position;
}
float GameObject::GetAngle() const {
	return angle;
}
glm::vec3 GameObject::GetRotation() const {
	return rotation;
}
glm::vec3 GameObject::GetScale() const {
	return scale;
}

Model* GameObject::GetModel() const
{
	return model;
}

BoundaryBox GameObject::GetBoundaryBox() {
	return BoundaryBox;
}

