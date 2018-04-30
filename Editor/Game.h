/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include"EditorLevel.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	EditorLevel level;
	PhysicsMat* mat = nullptr;
	/********************************/
	const std::vector<PhysicsMat> samples
	{
		PhysicsMat(Rect<float>(50, 550, 64, 32), 0.2, "busterTiles.bmp", Rect<int>(0,0,64,32)),
		PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(0,32,32,64)),
		PhysicsMat(Rect<float>(50, 550, 32, 64), 0.2, "busterTiles.bmp", Rect<int>(32,32,32,64)),
		PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(256,0,32,45)),
		PhysicsMat(Rect<float>(50, 550, 32, 45), 0.2, "busterTiles.bmp", Rect<int>(288,0,32,45)),
		PhysicsMat(Rect<float>(50, 500, 48, 48), 0.2, "busterComplete.bmp", Rect<int>(0,0,48,48))
	};
};