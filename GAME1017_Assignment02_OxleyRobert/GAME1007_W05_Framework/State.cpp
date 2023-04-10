#include "State.h"
#include "StateManager.h"
#include <iostream>

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}


void TitleState::Enter()
{
	std::cout << "Entering TitleState!" << std::endl;

	Mix_VolumeMusic(50);

	Mix_PlayMusic(Engine::backgroundMusic["titleMusic"], -1);
	CButton::SetPosition(512, 128);
	CButton::SetEnabled(true);

	m_background = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/img/menuBackground.jpg");
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		std::cout << "Changing to GameState!" << std::endl;
		STMA::ChangeState(new GameState()); // Transitioning to new GameState
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_background, NULL, &m_bg1);

}

void TitleState::Exit()
{
	std::cout << "exiting TitleState" << std::endl;
	// Make sure to invoke mix_freemusic
}


GameState::GameState() = default;

void GameState::Enter() // Initializing everything
{
	SDL_Renderer* engine_renderer = Engine::Instance().GetRenderer(); // Making it easier instead of multiple callbacks to Engine
	std::cout << "Entering GameState!" << std::endl;

	// Error checking the textures
	for (std::pair<string, SDL_Texture*> texture : textures)
	{
		if (texture.second == nullptr)
		{
			std::cout << SDL_GetError() << std::endl;
		}
	}

	// Putting the sounds into the map
	//m_sfx.emplace("collision", Mix_LoadWAV("../Assets/mus/collisionSound.wav"));

	// Error checking sounds...... (maybe no errors?)
	for (std::pair<string, Mix_Chunk*> soundFX : m_sfx) 
	{
		if (soundFX.second == nullptr)
		{
			cout << Mix_GetError() << endl;
		}
	}


	//Mix_VolumeMusic(16);

	//Mix_PlayMusic(Engine::backgroundMusic["playMusic"], -1);
}

void GameState::Update()
{
	// Probably can put this in HandleEvents, will do that later
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState" << std::endl;
		Mix_PauseMusic(); // Pauses all sounds, head empty.
		STMA::PushState(new PauseState()); // Pause time!
	}

	// When X is pressed go to EndState
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		std::cout << "Changing to EndState" << std::endl;
		STMA::ChangeState(new EndState());
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_Renderer* engine_renderer = Engine::Instance().GetRenderer(); // Making it easier instead of multiple callbacks to Engine
	// Any unique rendering in TitleState goes here ...
	SDL_SetRenderDrawColor(engine_renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine_renderer);

	// Rendering the background
}

void GameState::Exit()
{
	std::cout << "Exiting GameState!" << std::endl;

	// Deallocating all texture pointers :D
	for (pair<string, SDL_Texture*> texture : textures)
	{
		SDL_DestroyTexture(texture.second);
	}
	textures.clear(); // Finally, clearing out the map.

	// Deallocating all sound pointers :)
	for (pair<string, Mix_Chunk*> soundFX : m_sfx) 
	{
		Mix_FreeChunk(soundFX.second);
	}
	m_sfx.clear(); // Finally, clearing out the map
	Mix_HaltMusic();
}

void GameState::Resume()
{
	std::cout << "resuming gameState" << std::endl;
	Mix_ResumeMusic();
}

PauseState::PauseState() {}

void PauseState::Enter()
{
	std::cout << "Entering PauseState" << std::endl;
	CButton::SetPosition(615, 500);
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		STMA::PopState();
		CButton::SetEnabled(false);
	} else
	{
		CButton::SetEnabled(true);
	}
}

void PauseState::Render()
{
	STMA::GetStates().front()->Render(); // Basically, renders the GameState as well that has not been booted out yet of the vector
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 128); // Making window transparent
	SDL_Rect pause_rect = { 512, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &pause_rect);
}

void PauseState::Exit()
{
}

EndState::EndState() {}

void EndState::Enter()
{
	CButton::ChangeButton(END);
	CButton::SetPosition(500, 500);
	CButton::SetEnabled(true);
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
}

void EndState::Exit()
{
	std::cout << "Now exiting ExitState" << std::endl;
}


