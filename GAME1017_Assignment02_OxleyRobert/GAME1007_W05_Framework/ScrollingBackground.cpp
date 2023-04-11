#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Engine.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(8);
	// First background
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, {0.0f, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/background.png", "menuBG1"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/towers.png", "towersBG2"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/buildings.png", "buildingsBG3"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/foreground.png", "foregroundBG4"));

	// Second background
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/background.png", "menuBG1"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/towers.png", "towersBG2"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/buildings.png", "buildingsBG3"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 1.0f,
		"../Assets/img/foreground.png", "foregroundBG4"));
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
		background->Update();
}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)
		background->Render();
}
