#include "scene_manager.h"



SceneManager::SceneManager(Scene* scene)
{
	scenes.push_back(scene);
	index = 0;
}


SceneManager::~SceneManager()
{
}


void SceneManager::render()
{
	scenes[index]->render();
}

void SceneManager::tick()
{
	scenes[index]->tick();
}

void SceneManager::discreteTick()
{
	scenes[index]->discreteTick();
}

Scene* SceneManager::current() const
{
	return scenes[index];
}

Scene* SceneManager::next()
{
	if (index != scenes.size() - 1)
		++index;
	else
		index = 0;
	
	return scenes[index];
}

Scene* SceneManager::previous()
{
	if (index != 0)
		--index;
	else
		index = scenes.size() - 1;
	
	return scenes[index];

}

void SceneManager::addScene(Scene* scene)
{
	scenes.push_back(scene);
}
