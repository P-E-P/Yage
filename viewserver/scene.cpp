#include "scene.h"


Scene::Scene(Skybox* skybox, Camera* defaultCamera)
{
	this->skybox = skybox;
	index = 0;
	cameras.push_back(defaultCamera);

	currentCamera()->tick();
	skybox->tick();

	for (auto tickable : tickableList) {
		tickable->tick();
	}


}


Scene::~Scene()
{
	// TODO: remove all objects from the scene and free the memory
}

void Scene::render()
{
	skybox->render(currentCamera()->getView(), currentCamera()->getProjection());

	for (auto renderable : renderableList) {
		renderable->render(currentCamera()->getView(), currentCamera()->getProjection());
	}
}

long Scene::addRenderable(Renderable* renderable)
{
	renderableList.push_back(renderable);
	return renderableList.size() - 1;
}

long Scene::addTickable(Mob* mob)
{
	mob->tick();
	tickableList.push_back(mob);
	return renderableList.size() - 1;
}
void Scene::tick()
{
	/* Remove unused entities */
	if (!remover.empty()) {
		Entity* entity = remover.front();

		// TODO: remove the entity from all list

		remover.pop();
		delete entity;
	}
	/* Tick all components in the scene*/

	currentCamera()->tick();
	skybox->tick();

	for (auto tickable : tickableList) {
		tickable->tick();
	}
	
}

void Scene::discreteTick()
{
	for (auto tickable : discreteTickableList) {
		tickable->tick();
	}
}


Camera* Scene::currentCamera() const
{
	return cameras[index];
}

Camera* Scene::nextCamera()
{
	if (index != cameras.size() - 1)
		++index;
	else
		index = 0;

	return cameras[index];
}

Camera* Scene::previousCamera()
{
	if (index != 0)
		--index;
	else
		index = cameras.size() - 1;

	return cameras[index];
}
