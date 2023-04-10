#pragma once
#ifndef __STATE_H__
#define __STATE_H__

#include <map>
#include <string>
#include <iostream>

#include "Engine.h"
#include "StateManager.h"
#include "PlatformPlayer.h"

class StateManager; // Forward Declaration of StateManager

class State // Abstract Base Class
{ // No objects of State can be created
public:
	virtual void Enter() = 0; // Pure virtual function. No definition
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() {}; // Considered defined for all subclasses
protected: // Private but inherited
	State() = default;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:
	// Map for music track goes here
	SDL_Texture* m_background;
	SDL_FRect m_bg1 = { 0.0f, 0.0f, WIDTH, HEIGHT };
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

private:
	map <std::string, SDL_Texture*> textures; // Holding player, background, bullet, and enemy textures
	map<string, Mix_Chunk*> m_sfx; // Holding player shoot, enemy shoot, and collider sounds
	PlatformPlayer* m_pPlayer;
};

// Pause State
class PauseState : public State
{
public:
	PauseState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
};
// Make definition for end state
class EndState : public State
{
public:
	EndState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:

};


// This is essential for static properties. Declare them OUTSIDE their class but with class scope.

#endif // !__STATE_H__

