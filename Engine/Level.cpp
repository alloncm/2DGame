#include "Level.h"

Level::Level(Character&& h, PhysicsMat&& g,float gra)
	:
	gravity(gra)
{
	hero = std::make_unique<Character>(std::move(h));
	ground = std::make_unique<PhysicsMat>(std::move(g));

	hero->AddConstantForce(Vec2_<float>(0, gravity));
}

void Level::Draw(Graphics & gfx)
{
	hero->Draw(gfx);
	ground->Draw(gfx);
}

void Level::Update(int dir, bool jump)
{
	bool onGround = false;
	if (hero->Collision(ground.get()))
	{
		hero->AddForce(Vec2_<float>(0, -gravity));
		onGround = true;
		//make walking faster on the ground cause of the fraction
	}

	Input(dir, jump&&onGround);
	float dt = timer.Tick();
	hero->Update(dt);
}

void Level::Input(int dir, bool jump)
{
	hero->HandleInput(dir, jump);
}

