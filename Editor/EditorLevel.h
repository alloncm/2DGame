#pragma once
#include"Vec2.h"
#include<vector>
#include"Graphics.h"
#include"PhysicsMat.h"
#include<algorithm>

class EditorLevel
{
public:
	
	struct Object
	{
		enum class Type
		{
			NoType = -1,
			Tile,
			RightTile,
			LeftTile,
			RightCornerTile,
			LeftCotnerTile,
			Hero
		};


		Type type;
		PhysicsMat* mat;
		std::vector<PhysicsMat> samples
		{
			PhysicsMat(Rect<float>(50, 550, 64, 32), 0.2, "busterTiles.bmp", Rect<int>(0,0,64,32)),
			PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(0,32,32,64)),
			PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(32,32,32,64)),
			PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(256,0,32,45)),
			PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(288,0,32,45)),
			PhysicsMat(Rect<float>(50,500,48,48),0.2,"busterComplete.bmp",Rect<int>(0,0,48,48))
		};
		Object( PhysicsMat& pm)
			:
			type(Type(-1)),
			mat(&pm)
		{
		}
		Object& operator=(const Object& obj)
		{
			this->mat = obj.mat;
			this->type = obj.type;
			return *this;
		}
		bool operator==(const Object& obj)
		{
			return this->type == obj.type;
		}
	};
private:
	std::vector<Object> objects;
public:
	EditorLevel() = default;
	void Add( PhysicsMat& lo);
	void Remove(const Object& lo);
	void Draw(Graphics& gfx);
	void Save(std::string filename);
	Object::Type GetType(const Object& lo);
};


