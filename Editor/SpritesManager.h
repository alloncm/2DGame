#pragma once
#include<vector>
#include<utility>
#include<string>
#include"Surface.h"
class SpriteManager
{
private:
	class Entry
	{
	public:
		Entry(std::string k,Surface* s)
			:
			key(k),
			pSur(s)
		{
		}
		std::string key;
		Surface* pSur;
	};
private:
	std::vector<Entry> Surfaces;
	int count;
public:
	//static int countInstances;
public:
	static SpriteManager& GetManager();
	Surface* Get(std::string source);		//checks if this surface exists if no adds it. returns a reffernce to the sufface named source
	~SpriteManager(); 
private:
	void Add(std::string source);				//adds new surface to the vector
	SpriteManager();

};
