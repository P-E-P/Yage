#pragma once

#include <vector>

#include "scene.h"

class SceneManager
{
private:
	int index;
	std::vector<Scene*> scenes;
public:
	SceneManager();
	~SceneManager();
	Scene* current() const;
	Scene* next();
	Scene* previous();

	void addScene(Scene* scene);

	void render();
	void tick();
	void discreteTick();
};

