#include <string>
#include <sstream>
#include "c_sdlhelper.h"

#undef main

namespace arguments {
    namespace pos {
        int output = -1,
                font = -1,
                fontsize = -1;
    }
    namespace available {
        bool output = false,
                font = false,
                fontsize = false;
    }
}

#define ADD_ARG(name, variable) \
    if (std::strcmp(argv[i], (name)) == 0) { \
        (variable) = i + 1; \
        continue; \
    } \
    if ((variable) != -1) { \
        if (i == (variable)) continue; \
    } \

#define CREATE_ARG_BOOL(name, value) (name) = ((value) != -1)


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: .exe (-o <output path>) (-f <font path>) (-fs <font size>) <text>\n");
        return -1;
    }
    c_sdlhelper sdl;
    std::stringstream text_list;

    {
        using namespace arguments;

        for (int i = 1; i < argc; i++) {
            ADD_ARG("-o", pos::output)
            ADD_ARG("-f", pos::font)
            ADD_ARG("-fs", pos::fontsize)
            text_list << argv[i] << " ";
        }

        CREATE_ARG_BOOL(available::output, pos::output);
        CREATE_ARG_BOOL(available::font, pos::font);
        CREATE_ARG_BOOL(available::fontsize, pos::fontsize);
    }

    std::string text = text_list.str();
    text = text.substr(0, text.size() - 1); // remove last char (space)

    std::string bmp_path = text + ".bmp";
    std::string font_path = "font.ttf";
    int font_size = 100;

    {
        if (arguments::available::output)
            bmp_path = argv[arguments::pos::output];

        if (arguments::available::font)
            font_path = argv[arguments::pos::font];

        if (arguments::available::fontsize)
            font_size = atoi(argv[arguments::pos::fontsize]);
    }

    sdl.load_font(font_path, font_size);
    sdl.write_text_to_bmp(text, bmp_path);

    return 0;
}