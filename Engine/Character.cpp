#include "Character.h"

Character::Character(float mass, Vec2_<int> pos, int w, int h,float hd)
	:
	PhysicsBody(mass,pos,w,h),
	sprite(SpriteManager::GetManager().Get("Jack48x48.bmp")),
	holdTime(hd),
	iCurrent(State::IdleLeft)
{
	
	std::string filename = "Jack48x48.bmp";
	int x = 0 , y = 0;

	//idle
	for (int i = 0; i < int(State::WalkRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height,Vec2_<int>(x,y), Vec2_<int>(x+(3*this->width), y), Colors::Magenta));
		x += 3 * this->width;
	}
	y += this->height;
	x = 0;
	//walk
	for (int i = 0; i < int(State::JumpUpRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (6* this->width), y), Colors::Magenta));
		y += this->height;
	}
	y += this->height;
	x = 0;
	//jump
	for (int i = 0; i < int(State::Count); i+=2)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (3 * this->width), y), Colors::Magenta));
		x += 3 * this->width;
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (3 * this->width), y), Colors::Magenta));
		x = 0;
		y += this->height;
	}
	
}

void Character::Update(float dt)
{
	animations[int(iCurrent)].Update(dt);
}

void Character::Draw(Graphics & gfx)
{
	animations[int(iCurrent)].Draw(this->position,gfx);
}
