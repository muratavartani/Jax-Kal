#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::materialHandlerInstance = nullptr;
std::map<std::string, Material> MaterialHandler::materials = std::map<std::string, Material>();

MaterialHandler::MaterialHandler()
{
}

MaterialHandler::~MaterialHandler()
{
	if (materials.size() > 0)
	{
		materials.clear();
	}
}

MaterialHandler* MaterialHandler::GetInstance()
{
	if (materialHandlerInstance.get() == nullptr)
	{
		materialHandlerInstance.reset(new MaterialHandler);
	}
	return materialHandlerInstance.get();
}

void MaterialHandler::AddMaterial(const std::string& name_, Material material_)
{
	materials.insert(std::pair<std::string, Material>(name_, material_));
}

const Material MaterialHandler::GetMaterial(const std::string& materialName_)
{
	if (materials.find(materialName_) != materials.end())
	{
		return materials[materialName_];
	}
	return Material();
}