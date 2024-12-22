export module Game_UI;

import <iostream>;
import <SDL.h>;
import <SDL_image.h>;

export class __declspec(dllexport) Game_UI
{
public:
	Game_UI();
	~Game_UI();
	void				InitUI(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	
	void				HandleEvents();
	
	void				Update();
	void				Render();
	void				Clean();

	bool				Running();
private:

	bool				m_isRunning;
	SDL_Window*			m_window;
	SDL_Renderer*		m_renderer;
};
