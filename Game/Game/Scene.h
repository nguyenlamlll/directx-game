#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	//Update Scene
	virtual void Update(float deltaTime) = 0;
	
	//Draw components in scene
	virtual void Draw() = 0;
	//Handle of key down event
	virtual void OnKeyDown(int keyCode) = 0;
	//Handle of key up event
	virtual void OnKeyUp(int keyCode) = 0;

	// Initialize method is called once the scene is loaded to the front.
	virtual void initialize() = 0;
	//Release memory
	virtual void ReleaseAll() = 0;
};

