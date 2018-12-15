#include "Scene.h"

Scene* Scene::curScene = 0;
void Scene::changeScene(Scene* scene, bool clean)
{
	curScene = scene;
	curScene->init();
}

Scene::Scene(void)
{
}

void Scene::init()
{
}

void Scene::update()
{
}

void Scene::draw()
{
}

Scene::~Scene(void)
{
}
