#include "scene_manager.h"



SceneManager::SceneManager()
{
	index = 0;
}


SceneManager::~SceneManager()
{
}


void SceneManager::render()
{
	if(index < scenes.size())
		scenes[index]->render();
}

void SceneManager::tick()
{
	if(index < scenes.size())
		scenes[index]->tick();
}

void SceneManager::discreteTick()
{
	if (index < scenes.size())
		scenes[index]->discreteTick();
}

Scene* SceneManager::current() const
{
	if (index < scenes.size())
		return scenes[index];
	else
		return NULL;
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
