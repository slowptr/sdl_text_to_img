#ifndef SDL_TEXT_TO_IMG_C_SDLHELPER_H
#define SDL_TEXT_TO_IMG_C_SDLHELPER_H

#include <SDL.h>
#include <SDL_ttf.h>

class c_sdlhelper {
public:
    c_sdlhelper() { _init(); };

    c_sdlhelper(const std::string &path, int size) {
        _init();
        load_font(path, size);
    }

    ~c_sdlhelper() {
        TTF_CloseFont(_cur_font);
    }

    void load_font(const std::string &path, int size) { _cur_font = TTF_OpenFont(path.c_str(), size); }

    void write_text_to_bmp(const std::string &text, const std::string &path, SDL_Color color) {
        SDL_Surface *surface = TTF_RenderText_Solid(_cur_font, text.c_str(), color);
        SDL_SaveBMP(surface, path.c_str());
        SDL_FreeSurface(surface);
    }

    void write_text_to_bmp(const std::string &text, const std::string &path) {
        SDL_Color black = {0, 0, 0};
        write_text_to_bmp(text, path, black);
    }

private:
    TTF_Font *_cur_font{};

    static void _init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
    }
};

#endif //SDL_TEXT_TO_IMG_C_SDLHELPER_H
