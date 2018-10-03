#pragma once
#include"Animation.h"
#include<vector>
#include"PhysicsBody.h"
#include<thread>
class Character : public PhysicsBody
{
protected:
	enum struct State
	{
		IdleRight,
		IdleLeft,
		WalkRight,
		WalkLeft,
		JumpUpRight,
		JumpUpLeft,
		JumpDownRight,
		JumpDownLeft,
		AttackRight,
		AttackLeft,
		Count
	};
protected:
	std::vector<Animation> animations;
	Surface* sprite;
	float holdTime;
	State iCurrent;
	float speed;
	bool attacking;
	Rect<int> toRemove;
	/*
	might need to add a vector to store all the rects
	of the moves of the character cause the rect when
	attacking is differnt than the one walking or moving or falling. 
	*/
public:
	Character(float mass, Vec2_<float>pos, int w, int h,float hd, float spe);
	virtual void Update(float dt, std::vector<PhysicsMat>& mats)override;
	virtual void Draw(Graphics& gfx)override;
	void HandleInput(int dir, bool jump,bool attack);							// dir: 0 not moving 1 right -1 left
	virtual RectI GetRect()const override;
	virtual ~Character()=default;
};