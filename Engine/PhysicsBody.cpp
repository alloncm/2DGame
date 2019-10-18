#include "PhysicsBody.h"


PhysicsBody::PhysicsBody(float m, Vec2_<float> pos, int w, int h)
	:
	mass(m),
	position(pos),
	velocity(Vec2_<float>(0.0f, 0.0f)),
	acceleration(Vec2_<float>(0.0f, 0.0f)),
	eForces(Vec2_<float>(0.0f, 0.0f)),
	width(w),
	height(h),
	botoom(false)
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
	MoveBody(mats);
}

void PhysicsBody::MoveBody(std::vector<PhysicsMat>& mats)
{
	botoom = false;
	float length = velocity.GetLength();
	auto v = velocity;
	v.Normalize();

	for (float f = 0.0f; f < length; f += v.GetLength())
	{
		//checks x axis for invalid movement
		this->position.x += v.x;
		for (int i = 0; i < mats.size(); i++)
		{
			if (Collision(&mats[i]))
			{
				this->velocity.x = 0;
				this->position.x -= v.x;
			}
		}

		//checks y axis for invalid movement
		this->position.y += v.y;
		for (int i = 0; i < mats.size(); i++)
		{
			if (Collision(&mats[i]))
			{
				if (velocity.y > 0)
				{
					botoom = true;
				}

				this->velocity.y = 0;
				this->position.y -= v.y;
			}
		}
	}

	if (!botoom)
	{
		position.y++;
		for (int i = 0; i < mats.size(); i++)
		{
			if (Collision(&mats[i]))
			{
				botoom = true;
			}
		}
		position.y--;
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

void PhysicsBody::AddFraction(float f, float g)
{
	Vec2_<float> force(0, 0);
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
	return RectI(position.x, position.y, width, height);
}

bool PhysicsBody::Collision(PhysicsMat * mat)
{
	auto matRect = mat->GetRect();
	auto rect = this->GetRect();

	return rect.IsColliding(matRect);
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

bool PhysicsBody::HitBottom()
{
	return botoom;
}


void PhysicsBody::UpdateForces()
{
	Vec2_<float> sumForces(0, 0);
	for (Vec2_<float>& f : forces)
	{
		sumForces += f;
	}

	//clear all the the forces that are not constant
	forces.clear();

	//get the acceleration based on Sigma F = m*a
	acceleration = (eForces + sumForces) / mass;
}
