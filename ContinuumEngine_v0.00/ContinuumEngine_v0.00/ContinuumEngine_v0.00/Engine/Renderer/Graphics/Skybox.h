#ifndef SKYBOX_H
#define SKYBOX_H


#include "../GameObject/GameObject.h"

class Skybox
{
public:
	Skybox(const char * positive_x_image, const char * negative_x_image, const char * positive_y_image, const char * negative_y_image, const char * positive_z_image, const char * negative_z_image);
	~Skybox();
	void Initialize();
	void Render(Camera* camera_);

private:
	const char * positive_x_image_;
	const char * negative_x_image_;
	const char * positive_y_image_;
	const char * negative_y_image_;
	const char * positive_z_image_;
	const char * negative_z_image_;

	Model * Skymodel;
	GameObject* SkyboxObj;
	GLuint textureID;
	GLuint texture;

};

#endif