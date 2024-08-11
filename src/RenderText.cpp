#include "RenderText.hpp"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
    : renderer(renderer), font(nullptr), fontSize(28) {}

TextRenderer::~TextRenderer() {
    if (font) {
        TTF_CloseFont(font);
    }
}

bool TextRenderer::loadFont(const std::string& fontPath, int fontSize) {
    this->fontSize = fontSize;
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void TextRenderer::renderText(const std::string& message, int x, int y, SDL_Color color) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect messageRect = { x, y, surfaceMessage->w, surfaceMessage->h };
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(messageTexture);
}

void TextRenderer::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

TTF_Font* TextRenderer::getFont() const {  // Add this method
    return font;
}

int TextRenderer::getFontSize() const {
    return fontSize;
}


