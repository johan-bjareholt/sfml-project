#include "scene.h"

Scene* currentScene = NULL;
Scene* previousScene = NULL;

void switchScene(Scene* newScene){
	if (newScene != currentScene){
		Scene* oldscene = currentScene;
		currentScene = newScene;
	}
}

Scene* getScene(){
	if (currentScene != previousScene){
		delete previousScene;
		previousScene = currentScene;
	}
	return currentScene;
}