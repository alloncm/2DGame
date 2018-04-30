#include "SpritesManager.h"

SpriteManager::SpriteManager()
{
	count = 0;
}



SpriteManager & SpriteManager::GetManager()
{
	static SpriteManager Spm;
	return Spm;
}

//still need to make insertion and getting more efficient
Surface* SpriteManager::Get(std::string source)
{
	for (int i = 0; i < count; i++)
	{
		if (Surfaces[i].key.compare(source) == 0)
		{
			return Surfaces[i].pSur;
		}
	}
	Add(source);
	return Surfaces[count - 1].pSur;
}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < count; i++)
	{
		delete Surfaces[i].pSur;
	}
}

void SpriteManager::Add(std::string source)
{
	auto f = new Surface(source);
	Surfaces.insert(Surfaces.begin() + count, Entry(source,f));
	count++; 
}
