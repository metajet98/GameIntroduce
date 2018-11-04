#pragma once
class Scene
{
public:
	static Scene* curScene;

	static void changeScene(Scene* scene, bool clean = true);
	virtual void init();
	virtual void update();
	virtual void draw();
	Scene();
	~Scene();
};

