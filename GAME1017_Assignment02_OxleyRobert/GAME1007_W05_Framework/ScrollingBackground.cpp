#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Engine.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(8);
	// First background
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, {0.0f, 0.0f, WIDTH, HEIGHT }, 0.5f,
		"../Assets/img/background.png", "menuBG1"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 0.5f,
		"../Assets/img/background.png", "menuBG12"));


	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 2.0f,
		"../Assets/img/towers.png", "towersBG2"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 2.0f,
		"../Assets/img/towers.png", "towersBG22"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 2.5f,
		"../Assets/img/buildings.png", "buildingsBG3"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 2.5f,
		"../Assets/img/buildings.png", "buildingsBG32"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 3.0f,
		"../Assets/img/foreground.png", "foregroundBG4"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 3.0f,
		"../Assets/img/foreground.png", "foregroundBG42"));

	// Terrain

	for (int i = 0; i < 9; i++)
	{
		m_backgrounds.push_back(new Background({ 0, 0, 32, 32 }, { static_cast<float>(128 * i), 512 - 64, 128, 128 }, 3.0f,
			"../Assets/img/obstacles/Tilesets/terrain.png", "terrainSheet"));
	}
	

	
	
	
}

ScrollingBackground::~ScrollingBackground()
{
	for (auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;
	}
	
	m_backgrounds.clear();
	m_backgrounds.shrink_to_fit();
}

void ScrollingBackground::Update()
{
	for (const auto background : m_backgrounds)
	{
		background->Update();
		background->m_playerSpeed = playerSpeed;
	}
}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)
		background->Render();
}