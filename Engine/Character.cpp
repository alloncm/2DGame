#include "Character.h"

Character::Character(float mass, Vec2_<int> pos, int w, int h,float hd, float spe)
	:
	PhysicsBody(mass,pos,w,h),
	sprite(SpriteManager::GetManager().Get("Jack48x48.bmp")),
	holdTime(hd),
	iCurrent(State::IdleRight),
	speed(spe)
{
	
	std::string filename = "Jack48x48.bmp";
	int x = 0 , y = 0;
	int i;
	//idle
	for ( i = 0; i < int(State::WalkRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height,Vec2_<int>(x,y), Vec2_<int>(x+(3*this->width), y), Colors::Magenta));
		x += 3 * this->width;
	}
	y += this->height;
	x = 0;
	//walk
	for (; i < int(State::JumpUpRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (6* this->width), y), Colors::Magenta));
		y += this->height;
	}
	x = 0;
	//jump
	for (; i < int(State::Count); i+=2)
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
	PhysicsBody::Update(dt);
	animations[int(iCurrent)].Update(dt);
}

void Character::Draw(Graphics & gfx)
{
	animations[int(iCurrent)].Draw(this->position,gfx);
}

void Character::HandleInput(int dir, bool jump)
{
	//in the enum struct State all the states facing right are even while all the states facing left are odd
	bool face = (int(iCurrent) % 2)!=0;		//false is Left true is Right
	switch (dir)
	{
	case -1:
		iCurrent = State::WalkLeft;
		break;
	case 1:
		iCurrent = State::WalkRight;
		break;
	default:
		iCurrent = State(int(face));
		break;
	}

	//the force is awkward to control with
	//AddForce(Vec2_<float>(dir*speed, 0));

	velocity.x = dir*speed;
}
