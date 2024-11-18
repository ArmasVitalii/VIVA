export module Game_UI;

import <SDL.h>;

export class __declspec(dllexport) Game_UI
{
public:
	Game_UI();
	~Game_UI();
	void initUI(const char* title, int x_poz, int y_poz, int width, int height, bool fullscreen);
	
	void handleEvents();
	
	void update();
	void render();
	void clean();

	bool running();
private:

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};