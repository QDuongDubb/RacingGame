#include <SDL.h>
#include <SDL_image.h>

class RenderWindow 
{
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);

        SDL_Texture* renderText(const char* message, const char* fontFlie, SDL_Color color, int fontSize);
        void cleanUp();
        SDL_Renderer* getRenderer() const;
        void clear();
        void render(SDL_Texture* p_tex);
        void renderWithScale(SDL_Texture* p_tex, int x, int y, int width, int height);
        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};