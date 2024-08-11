#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer {
public:
    TextRenderer(SDL_Renderer* renderer);
    ~TextRenderer();

    bool loadFont(const std::string& fontPath, int fontSize);
    void renderText(const std::string& message, int x, int y, SDL_Color color);
    void setFontSize(int fontSize);
    TTF_Font* getFont() const;
    int getFontSize() const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int fontSize;
};

#endif
