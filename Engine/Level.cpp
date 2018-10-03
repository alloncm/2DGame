
#include "Level.h"

Level::Level(Character&& h,float gra,std::string level)
	:
	gravity(gra)
{
	hero = std::make_unique<Character>(std::move(h));

	hero->AddConstantForce(Vec2_<float>(0, gravity));

	LoadLevel(level);
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
	hero->Update(dt,ground);
}

void Level::Input(int dir, bool jump,bool attack)
{
	hero->HandleInput(dir, jump,attack);
}

void Level::LoadLevel(std::string filename)
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
	
	if (size % sizeof(Object) != 0)
	{
		std::string msg = "the file " + filename + " is corrupted\n";
		throw std::exception(msg.c_str());
	}
	Object temp;
	for(int i=0;i<size;i+=sizeof(Object))
	{
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));

		switch (temp.type)
		{
		case(Type::Hero):
			hero->SetPosition(Cast(temp.position));
			break;
		default:
			if (temp.type <= (Type::LeftCornerTile) && temp.type >= Type(0))
			{
				ground.emplace_back(samples[int(temp.type)]);
				ground[ground.size() - 1].SetPosition(temp.position);
			}
			break;
		}
	}
}

