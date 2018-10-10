#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float m, Vec2_<float> pos, int w, int h)
	:
	mass(m),
	position(pos),
	velocity(Vec2_<float>(0.0f,0.0f)),
	acceleration(Vec2_<float>(0.0f, 0.0f)),
	eForces(Vec2_<float>(0.0f, 0.0f)),
	width(w),
	height(h)
{
}

void PhysicsBody::Update(float dt, std::vector<PhysicsMat>& mats)
{
	UpdateForces();
	velocity = velocity + (acceleration*dt);
	UpdatePhysics(mats);
}

void PhysicsBody::UpdatePhysics(std::vector<PhysicsMat>& mats)
{
	for (int i = 0; i < mats.size(); i++)
	{
		Collision(&mats[i]);
	}
	MoveBody(mats);
}

void PhysicsBody::MoveBody(std::vector<PhysicsMat>& mats)
{

	float length = velocity.GetLength();
	auto v = velocity.Normalize();

	int countColl = 0;
	for (float f = 0.0f; f < length; f += v.GetLength())
	{
		position += v;
		for (int i = 0; i < mats.size(); i++)
		{
			if (Collision(&mats[i]))
			{
				countColl++;
			}
		}
		
		
		if (countColl > 0)
		{
			length = velocity.GetLength();
			v = velocity.Normalize();
		}
		
		
		countColl = 0;
	}


}

void PhysicsBody::AddConstantForce(Vec2_<float> force)
{
	eForces += force;
}

void PhysicsBody::AddForce(Vec2_<float> force)
{
	forces.emplace_back(force);
}

void PhysicsBody::AddFraction(float f,float g)
{
	Vec2_<float> force(0,0);
	if (velocity.x != 0)
	{
		force.x = f*-g*mass;			//its already negatice cause gravity is negative
		if (velocity.x < 0)			//if he walks left make the force positive
		{
			force.x *= -1;
		}
	}
	AddForce(force);
}

RectI PhysicsBody::GetRect() const
{
	return RectI(position.x,position.y,width,height);
}

bool PhysicsBody::Collision(PhysicsMat * mat)
{
	auto matRect = mat->GetRect();
	auto rect = this->GetRect();
	auto IsBetween = [](int t, int b, int x)->bool 
	{
		return((x<t&&x>b)||(x<b&&x>t));
	};
	int top = matRect.GetTopLeft().y;
	int bottom = matRect.GetBotoomRight().y;
	auto IsHeroBetweenHeight = [&top,&bottom,IsBetween](int hero)->bool
	{ 
		return (IsBetween(top, bottom, hero) || IsBetween(top, bottom, hero));
	};

	if (matRect.IsColliding(this->GetRect()))
	{
		//the body hit his left side in the mat
		if ((rect.GetTopLeft().x == matRect.GetBotoomRight().x) && (IsHeroBetweenHeight(rect.GetTopLeft().y) || IsHeroBetweenHeight(rect.GetBotoomRight().y)))
		{
			if (this->velocity.x > 0)
			{
				this->velocity.x = 0;
			}
		}
		//the body hit with his right side in the mat
		else if (rect.GetBotoomRight().x == matRect.GetTopLeft().x && (IsHeroBetweenHeight(rect.GetTopLeft().y) || IsHeroBetweenHeight(rect.GetBotoomRight().y)))
		{
			if (this->velocity.x < 0)
			{
				this->velocity.x = 0;
			}
		}
		//the body hit with his bottom in the mat
		else if (rect.GetBotoomRight().y == matRect.GetTopLeft().y)
		{
			if (this->velocity.y > 0)
			{
				this->velocity.y = 0;
			}
		}
		//the body hit with his top in the mat
		else if (rect.GetTopLeft().y == matRect.GetBotoomRight().y)
		{
			if (this->velocity.y < 0)
			{
				this->velocity.y = 0;
			}
		}
		//the body got into the mat and i dont know what to do yet
		else
		{
			throw std::exception("collision got into the mat and the collison detection is not good enough");
		}
		return true;
	}
	
	return false;
}

Vec2_<float> PhysicsBody::GetSumForces()
{
	Vec2_<float> sumForces(0, 0);
	for (Vec2_<float>& f : forces)
	{
		sumForces += f;
	}
	sumForces += eForces;
	return sumForces;
}

void PhysicsBody::SetPosition(Vec2_<float> pos)
{
	this->position = pos;
}

void PhysicsBody::UpdateForces()
{
	Vec2_<float> sumForces(0, 0);
	for (Vec2_<float>& f: forces)
	{
		sumForces += f;
	}

	//clear all the the forces that are not constant
	forces.clear();

	//get the acceleration based on Sigma F = m*a
	acceleration = (eForces+sumForces) / mass;
}
