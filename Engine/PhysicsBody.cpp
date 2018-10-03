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
		
		position += v;
		
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

	//the vector needs to detects one pixel to each side cause he is on it not in it
	if (matRect.IsColliding(this->GetRect()))
	{
		std::vector<Vec2_<int>> vectors;
		Vec2_<int>* vecs = matRect.GetPvectors();
		for (int i = 0; i < 4; i++)
		{
			if (rect.IsInside(*(vecs + i)))
			{
				
				if (vectors.size()<2)
				{
					vectors.emplace_back(*(vecs + i));
				}
			}
		}
		delete[] vecs;
		vecs = nullptr;
		if (vectors.size() < 2)
		{
			vecs = rect.GetPvectors();
			for (int i = 0; i < 4; i++)
			{
				if (matRect.IsInside(*(vecs+i)))
				{
					if (vectors.size()<2)
					{
						vectors.emplace_back(*(vecs + i));
					}
				}
			}
			delete[] vecs;
			vecs = nullptr;
		}
		
		Vec2_<int> v = vectors[0] - vectors[1];
		if (std::abs(v.x) > std::abs(v.y))
		{
			this->velocity.y = 0;
		}
		else if (std::abs(v.x) < std::abs(v.y))
		{
			this->velocity.x = 0;
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
