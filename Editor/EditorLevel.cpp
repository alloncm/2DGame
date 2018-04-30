#include"EditorLevel.h"

void EditorLevel::Add( PhysicsMat & lo)
{
	Object obj(lo);
	auto it = std::find(obj.samples.begin(), obj.samples.end(), lo);
	int i = obj.samples.begin() - it;
	obj.type = EditorLevel::Object::Type(i);
	objects.emplace_back(obj); 
}

void EditorLevel::Remove(const EditorLevel::Object & lo)
{
	
	auto it = std::find(objects.begin(), objects.end(), lo);
	if (it!=objects.end())
	{
		objects.erase(it);
	}
	
}


EditorLevel::Object::Type EditorLevel::GetType(const Object& lo)
{
	
	auto it = std::find(objects.begin(), objects.end(), lo);
	
	if (it != objects.end())
	{
		return it->type;
	}
	return Object::Type::NoType;
}
void EditorLevel::Draw(Graphics& gfx)
{
	for (Object& obj : objects)
	{
		obj.mat->Draw(gfx);
	}
}

void EditorLevel::Save(std::string filename)
{
}
