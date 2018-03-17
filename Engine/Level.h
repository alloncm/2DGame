#pragma once
#include"Character.h"
#include"PhysicsMat.h"
#include<memory>
#include"Timer.h"
class Level
{
protected:
	std::unique_ptr<Character> hero;
	std::unique_ptr<PhysicsMat> ground;
	float gravity;
	Timer timer;
public:
	Level(Character&& h,PhysicsMat&& g,float gra);
	void Draw(Graphics& gfx);
	void Update(int dir, bool jump);
	void Input(int dir,bool jump);
};