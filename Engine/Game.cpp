/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	Ground(Rect<float>(0, 550, 400, 50), 0.2, Colors::Green),
	ch(2,{100,100},48,48,0.1,10),
	level(std::move(ch),std::move(Ground),10)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	int input = 0;
	if (wnd.kbd.KeyIsPressed(VK_LEFT)&& wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		input = 0;
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		input = -1;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		input = 1;
	}
	level.Input(input, false);
	level.Update();
	
}

void Game::ComposeFrame()
{
	level.Draw(gfx);
}
