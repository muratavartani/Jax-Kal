#include "Skybox.h"



Skybox::Skybox(const char * positive_x_image, const char * negative_x_image, const char * positive_y_image, const char * negative_y_image, const char * positive_z_image, const char * negative_z_image)
{

	positive_x_image_ = positive_x_image;
	negative_x_image_ = negative_x_image;
	positive_y_image_ = positive_y_image;
	negative_y_image_ = negative_y_image;
	positive_z_image_ = positive_z_image;
	negative_z_image_ = negative_z_image;

	Initialize();
}


Skybox::~Skybox()
{
}


void Skybox::Initialize() {

	Skymodel = new Model("Engine/GlobalElements/Resources/Models/sphere.obj", "Skybox", "SkyboxShader", false);
	SkyboxObj = new GameObject(Skymodel);
	SDL_Surface *textureSurface;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	textureSurface = IMG_Load(positive_x_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(negative_x_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(positive_y_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(negative_y_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(positive_z_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(negative_z_image_);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	//glUseProgram(ShaderHandler::GetInstance()->GetShader("SkyboxShader"));

}

void Skybox::Render(Camera* camera_) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	glUseProgram(ShaderHandler::GetInstance()->GetShader("SkyboxShader"));
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glUniformMatrix4fv(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("SkyboxShader"), "proj"), 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("SkyboxShader"), "view"), 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	Skymodel->Render(camera_, "SkyboxShader");


}