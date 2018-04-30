#pragma once
#include"Character.h"
#include"PhysicsMat.h"
#include<memory>
#include"Timer.h"
#include<fstream>
class Level
{
public:
	enum class Object
	{
		Tile,
		RightTile,
		LeftTile,
		RightCornerTile,
		LeftCotnerTile,
		Hero
	};

	struct LevelObject
	{
		Object obj;
		Vec2_<int> position;
	};
public:
	std::vector<PhysicsMat> samples
	{
		PhysicsMat(Rect<float>(50, 550, 64, 32), 0.2, "busterTiles.bmp", Rect<int>(0,0,64,32)),
		PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(0,32,32,64)),
		PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(32,32,32,64)),
		PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(256,0,32,45)),
		PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(288,0,32,45))
	};
protected:
	std::unique_ptr<Character> hero;
	float gravity;
	Timer timer;
	std::vector<PhysicsMat> ground;
public:
	Level(Character&& h,PhysicsMat&& g,float gra);
	void Draw(Graphics& gfx);
	void Update(int dir, bool jump,bool attack);
	void Input(int dir,bool jump,bool attack);
	void GenerateFromFile(std::string filename);
};