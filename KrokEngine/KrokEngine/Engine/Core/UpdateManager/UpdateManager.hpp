#include "../../Essentials/GameObject.hpp"
#include "../Graphics/Renderer.hpp"
#include "../../Core/SceneManager/Scene.hpp"

class UpdateManager
{
public:
	UpdateManager();
	~UpdateManager();

	void Update(Scene* scene);

private:
	void update(GameObject* toUpdate);
};

