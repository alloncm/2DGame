#include"Vec2.h"
#include"Graphics.h"
#include<vector>
class PhysicsBody
{
protected:
	float mass;
	Vec2_<float> velocity;
	Vec2_<float> acceleration;
	Vec2_<int> position;
	Vec2_<float> eForces;					//forces that are used all the time like gravity
	int width;
	int height;
	std::vector<Vec2_<float>>forces;		//forces which are being used only once like a punch or explosion or even jumping
protected:
	PhysicsBody(float mass, Vec2_<int>pos,int w,int h);
public:
	virtual void Draw(Graphics& gfx) = 0;
	virtual void Update(float dt);
	void AddConstantForce(Vec2_<float> force);
	void AddForce(Vec2_<float> force);
private:
	void UpdateForces();
};