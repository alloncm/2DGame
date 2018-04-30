
#include "Level.h"

Level::Level(Character&& h, PhysicsMat&& g,float gra)
	:
	gravity(gra)
{
	hero = std::make_unique<Character>(std::move(h));
	ground.emplace_back(samples[4]);

	hero->AddConstantForce(Vec2_<float>(0, gravity));

	std::ofstream fout ("binfile.lvl", std::ios::binary);
	int a = 0, b = 0, c = 0;
	fout.write(reinterpret_cast<char* > (&a), sizeof(int));
	fout.write(reinterpret_cast<char* >(&b), sizeof(int));
	fout.write(reinterpret_cast<char* >(&c), sizeof(int));

}



void Level::Draw(Graphics & gfx)
{
	hero->Draw(gfx);
	for (int i = 0; i < ground.size(); i++)
	{
		ground[i].Draw(gfx);
	}
}

void Level::Update(int dir, bool jump,bool attack)
{
	bool onGround = false;
	for (int i = 0; i < ground.size(); i++)
	{
		if (hero->Collision(&ground[i]))
		{
			onGround = true;
		}
	}
	if (onGround)
	{
		hero->AddForce(Vec2_<float>(0, -gravity));
		//TODO: make walking faster on the ground cause of the fraction
	}

	Input(dir, jump&&onGround,attack);
	float dt = timer.Tick();
	hero->Update(dt);
}

void Level::Input(int dir, bool jump,bool attack)
{
	hero->HandleInput(dir, jump,attack);
}

void Level::GenerateFromFile(std::string filename)
{
	std::ifstream fin(filename,std::ios::binary|std::ios::ate);
	fin.exceptions(std::ios::badbit | std::ios::failbit);
	if (!fin.is_open())
	{
		std::string str = "cannot open file " + filename;
		throw std::exception(str.c_str());
	}
	int size = fin.tellg();
	fin.seekg(0, std::ios::beg);

	int obj=0;
	int x = 0;
	int y = 0;
	
	while (fin.tellg()<size)
	{
		fin.read(reinterpret_cast<char*>(&obj), sizeof(int));
		fin.read(reinterpret_cast<char*>(&x), sizeof(int));
		fin.read(reinterpret_cast<char*>(&y), sizeof(int));

		switch (obj)
		{
		case(int(Object::Hero)):
			hero->SetPosition(Vec2_<int>(x, y));
			break;
		default:
			if (obj <= int(Object::LeftCotnerTile) && obj >= 0)
			{
				ground.emplace_back(samples[int(Object::Tile)]);
				ground[ground.size() - 1].SetPosition(Vec2_<int>(x, y));
			}
			break;
		}
	}
	
}

