#pragma once
#include"Animation.h"
#include<vector>
#include"PhysicsBody.h"
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
		Count
	};
protected:
	std::vector<Animation> animations;
	Surface* sprite;
	float holdTime;
	State iCurrent;
	float speed;
public:
	Character(float mass, Vec2_<int>pos, int w, int h,float hd, float spe);
	virtual void Update(float dt)override;
	virtual void Draw(Graphics& gfx)override;
	void HandleInput(int dir, bool jump);							// dir: 0not moving 1 right -1 left
	virtual ~Character()=default;
};