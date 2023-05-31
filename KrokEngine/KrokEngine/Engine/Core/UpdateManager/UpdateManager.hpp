#include "../../Essentials/GameObject.hpp"
#include "../Graphics/Renderer.hpp"
#include "../../Core/SceneManager/Scene.hpp"

class UpdateManager
{
public:
	UpdateManager();
	~UpdateManager();

	void Update(Scene* scene);
	void SetRenderer(Renderer& renderer);

private:
	Renderer* _renderer = nullptr;
	void update(borrow_ptr<GameObject>  toUpdate);
};

