#pragma once

#include <list>
#include <vector>
#include <queue>

#include "ground.h"
#include "camera.h"
#include "skybox.h"

enum ComponentState {
	S_RENDERABLE = 0x01,
	S_TICKABLE = 0x02,
	S_DISCRETE_TICKABLE = 0x04
};

class Scene
{
private:
	Skybox* skybox;
	//This queue contains all objects in the scene that need to be removed
	std::queue<Entity*> remover;
	// This list contains all objects in the scene that need to be rendered
	std::list<Renderable*> renderableList;
	// This list contains all objects in the scene that need to be updated
	std::list<Mob*> tickableList;
	// This list contains all object in the scene that need to be discretly updated
	std::list<Mob*> discreteTickableList;

	int index;
	std::vector<Camera*> cameras;
public:
	Scene(Skybox* skybox, Camera* defaultCamera);
	~Scene();
	void render();
	void discreteTick();
	void tick();
	long addRenderable(Renderable* renderable);
	long addTickable(Mob* mob);

	Camera* currentCamera() const;
	Camera* nextCamera();
	Camera* previousCamera();
};

