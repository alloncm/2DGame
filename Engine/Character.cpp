#include "Character.h"

Character::Character(float mass, Vec2_<float> pos, int w, int h,float hd, float spe)
	:
	PhysicsBody(mass,pos,w,h),
	sprite(SpriteManager::GetManager().Get("busterComplete.bmp")),
	holdTime(hd),
	iCurrent(State::IdleRight),
	speed(spe),
	attacking(false)
{
	std::string filename = "busterComplete.bmp";
	int x = 0 , y = 0;
	int i;
	int top = 0, left = 0, bottom = 0, right = 0;
	//idle
	for ( i = 0; i < int(State::WalkRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height,Vec2_<int>(x,y), Vec2_<int>(x+(3*this->width), y), Colors::Magenta));
		x += 3 * this->width;
		auto rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
	}
	y += this->height;
	x = 0;
	//walk
	for (; i < int(State::JumpUpRight); i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (6* this->width), y), Colors::Magenta));
		y += this->height;
		auto rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
	}
	x = 0;
	//jump
	for (; i < int(State::AttackRight); i+=2)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (3 * this->width), y), Colors::Magenta));
		x += 3 * this->width;
		auto rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(x + (3 * this->width), y), Colors::Magenta));
		x = 0;
		y += this->height;
		rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
	}

	//attack
	for (; i<int(State::Count);i++)
	{
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(4 * this->width, y), Colors::Magenta));
		x = 0;
		y += this->height;
		auto rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
		animations.emplace_back(Animation(filename, holdTime, this->width, this->height, Vec2_<int>(x, y), Vec2_<int>(4 * this->width, y), Colors::Magenta));
		rect = animations[animations.size() - 1].GetRectToDel();
		top = max(rect.GetTopLeft().y, top);
		left = max(rect.GetTopLeft().x, left);
		bottom = max(rect.GetBotoomRight().y, bottom);
		right = max(rect.GetBotoomRight().x, right);
	}
	toRemove =  RectI(Vec2_<int>(left, top), Vec2_<int>(right, bottom));
}

void Character::Update(float dt, std::vector<PhysicsMat>& mats)
{
	PhysicsBody::Update(dt,mats);
	animations[int(iCurrent)].Update(dt);
}

void Character::Draw(Graphics & gfx)
{
	//animations[int(iCurrent)].Draw(Cast(this->position),gfx);
	gfx.DrawRect(this->GetRect(), Colors::Red);
}

void Character::HandleInput(int dir, bool jump,bool attack)
{
	//in the enum struct State all the states facing right are even while all the states facing left are odd
	bool face = (int(iCurrent) % 2)!=0;		//false is Right true is Left


	if (!attacking)
	{
		if (this->velocity.y == 0)
		{
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
		}
		else if (this->velocity.y < 0)
		{
			switch (dir)
			{
			case -1:
				iCurrent = State::JumpUpLeft;
				break;
			case 1:
				iCurrent = State::JumpUpRight;
				break;
			default:
				iCurrent = State(int(State::JumpUpRight) + face);
				break;
			}

		}
		else if (this->velocity.y > 0)
		{
			switch (dir)
			{
			case -1:
				iCurrent = State::JumpDownLeft;
				break;
			case 1:
				iCurrent = State::JumpDownRight;
				break;
			default:
				iCurrent = State(int(State::JumpDownRight) + face);
				break;
			}

		}

		if (jump)
		{
			velocity.y = -6;
		}
		if (attack)
		{
			iCurrent = State(int(State::AttackRight) + face);
			attacking = true;
			//reseting the cycle of the animation to make sure the attacking is being completed
			animations[int(iCurrent)].ResetCycle();
		}
	}
	else
	{
		attacking = !animations[int(iCurrent)].FinishedCycle();
	}
	
	//the force is awkward to control with
	//AddForce(Vec2_<float>(dir*speed, 0));

	velocity.x = dir*speed;
}

RectI Character::GetRect() const
{
	//gets the original rect
	auto rect = PhysicsBody::GetRect();

	//remove the leftovers
	rect.SetTopLeft(rect.GetTopLeft() + toRemove.GetTopLeft());
	rect.SetBottomRight(rect.GetBotoomRight() - toRemove.GetBotoomRight());
	return rect;
}
