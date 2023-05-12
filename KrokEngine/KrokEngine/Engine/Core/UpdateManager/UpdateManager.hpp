class Renderer;
class GameObject;
class GmObjctPtr;

class UpdateManager
{
public:
	UpdateManager();
	~UpdateManager();

	void Update(GameObject* game);
	void SetRenderer(Renderer& renderer);

private:
	Renderer* _renderer = nullptr;
	void update(GameObject* toUpdate);
};

