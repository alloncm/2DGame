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
	position += Vec2_<int>(velocity.x,velocity.y);
}

void PhysicsBody::AddConstantForce(Vec2_<float> force)
{
	eForces += force;
}

void PhysicsBody::AddForce(Vec2_<float> force)
{
	forces.emplace_back(force);
}

void PhysicsBody::UpdateForces()
{
	Vec2_<float> sumForces(0, 0);
	for (Vec2_<float>& f: forces)
	{
		sumForces += f;
	}
	acceleration = (eForces+sumForces) / mass;
}
