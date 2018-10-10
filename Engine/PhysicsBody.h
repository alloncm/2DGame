#pragma once

#include"Vec2.h"
#include"Graphics.h"
#include<vector>
#include"PhysicsMat.h"
class PhysicsBody
{
protected:
	float mass;
	Vec2_<float> velocity;
	Vec2_<float> acceleration;
	Vec2_<float> position;
	Vec2_<float> eForces;					//forces that are used all the time like gravity
	int width;
	int height;
	std::vector<Vec2_<float>>forces;		//forces which are being used only once like a punch or explosion or even jumping
	bool botoom;
protected:
	PhysicsBody(float mass, Vec2_<float>pos, int w, int h);
public:
	virtual void Draw(Graphics& gfx) = 0;
	virtual void Update(float dt, std::vector<PhysicsMat>& mats);
	virtual void UpdatePhysics( std::vector<PhysicsMat>& mats);
	virtual void MoveBody( std::vector<PhysicsMat>& mats);
	void AddConstantForce(Vec2_<float> force);
	void AddForce(Vec2_<float> force);
	void AddFraction(float f, float g);
	virtual RectI GetRect()const;
	bool Collision(PhysicsMat* mat);
	Vec2_<float> GetSumForces();
	void SetPosition(Vec2_<float> pos);
	bool HitBottom();
	virtual ~PhysicsBody() = default;
private:
	void UpdateForces();
};