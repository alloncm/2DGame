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

void Level::Update()
{
	if (ground->IsColiding(Cast(hero->GetRect())))
	{
		hero->AddForce(Vec2_<float>(0, -gravity));
		hero->AddFraction(ground->GetFraction(), gravity);
		hero->Collision(ground.get());
	}
	float dt = timer.Tick();
	hero->Update(dt);
}

void Level::Input(int dir, bool jump)
{
	hero->HandleInput(dir, jump);
}

