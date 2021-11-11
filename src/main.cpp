#include <string>
#include <sstream>
#include "c_sdlhelper.h"

#undef main // some stupid sdl2 shit

namespace arguments {
    namespace pos {
        int output = -1,
                font = -1,
                font_size = -1;
    }
    namespace available {
        bool output = false,
                font = false,
                font_size = false;
    }
}

#define ADD_ARG(ns, name, var) \
    if (std::strcmp(argv[i], (name)) == 0) { \
        (ns::pos::var) = i + 1; \
        continue; \
    } \
    if ((ns::pos::var) != -1) { \
        if (i == (ns::pos::var)) continue; \
    } \

#define CREATE_ARG_BOOL(ns, name) (ns::available::name) = ((ns::pos::name) != -1)

// just because i now decided that i enjoy the abusement of defines in cpp
#define SET_AFTER_ARG_STR(ns, name, var) \
    if (ns::available::name)                \
        var = argv[ns::pos::name]; \

#define SET_AFTER_ARG_INT(ns, name, var) \
    if (ns::available::name)                \
        var = atoi(argv[ns::pos::name]); \


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: .exe (-o <output path>) (-f <font path>) (-fs <font size>) <text>\n");
        return -1;
    }
    c_sdlhelper sdl;
    std::stringstream text_list;

    {
        for (int i = 1; i < argc; i++) {
            ADD_ARG(arguments, "-o", output)
            ADD_ARG(arguments, "-f", font)
            ADD_ARG(arguments, "-fs", font_size)
            text_list << argv[i] << " ";
        }

        CREATE_ARG_BOOL(arguments, output);
        CREATE_ARG_BOOL(arguments, font);
        CREATE_ARG_BOOL(arguments, font_size);
    }

    std::string text = text_list.str();
    text = text.substr(0, text.size() - 1); // remove last char (space)

    std::string bmp_path = text + ".bmp";
    std::string font_path = "font.ttf";
    int font_size = 100;

    {
        SET_AFTER_ARG_STR(arguments, output, bmp_path)
        SET_AFTER_ARG_STR(arguments, font, font_path)
        SET_AFTER_ARG_INT(arguments, font_size, font_size)
    }
    
    sdl.load_font(font_path, font_size);
    sdl.write_text_to_bmp(text, bmp_path);

    return 0;
}