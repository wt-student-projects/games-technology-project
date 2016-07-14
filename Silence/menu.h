
/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __DEMO__H_
#define __DEMO__H_

#include "System.h"
#include "HLGI.h"
#include "Media.h"

// A scene class for our menu
class Menu : public Scene 
{
private:
	// Our local asset manager for the scene
	LocalAssetManager * package;
	// Our renderer which will render each object
	Renderer2D renderer2D;
	//
	SceneManager * scenes;
	//

	Background background;
	Headers headers;
	Buttons buttons;
	
	Music menuMusic;
	Music roar;
public:
	// Constructor & Deconstructor
	Menu(OperatingSystem * os);
	~Menu();

	// Handles when a SDL_Event is called
	void onGameEvent(SDL_Event& e);
	// Handles when the scene is to be created
	void onCreate();
	// The update function
	void onUpdate();
	// The render function
	void onRender();
	//
	void onGamepadButton(int k, int s);
	//
	void onEnter(int);
private:
	bool entered;
	bool exited;
	float alpha;
};

#endif