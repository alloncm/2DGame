#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float m, Vec2_<int> pos, int w, int h)
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

void PhysicsBody::Update(float dt)
{
	UpdateForces();

	velocity = velocity + (acceleration*dt);
	position += Vec2_<int>(int(velocity.x),int(velocity.y));
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
	RectI matRect = mat->GetRect();
	//needs to check only the standing animation rect and not the falling animation for example
	if (this->GetRect().IsColliding(matRect))
	{
		if (matRect.GetTopLeft().y<(this->position.y-this->height)&&matRect.GetBotoomRight().y>this->position.y)
		{
			velocity.x = 0;

			//adjust the position of the body after hitting the material
			//check this piece of code
			if (matRect.GetTopLeft().x > this->position.x)
			{
				this->position.x = matRect.GetTopLeft().x + this->width;
			}
			else if (matRect.GetBotoomRight().x < this->position.x)
			{
				this->position.x = matRect.GetBotoomRight().x;
			}
		}
		else
		{
			velocity.y = 0;

			//adjust the position of the body after hitting the material
			if (matRect.GetTopLeft().y > this->position.y)		//the body is on the mat
			{
				this->position.y = matRect.GetTopLeft().y - this->height;
			}
			else if (matRect.GetBotoomRight().y < this->position.y)
			{
				this->position.y = matRect.GetBotoomRight().y;
			}
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

void PhysicsBody::SetPosition(Vec2_<int> pos)
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
