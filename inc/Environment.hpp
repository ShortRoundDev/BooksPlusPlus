#pragma once

#include "Types.hpp"

#include <ncurses.h>
#include <string>

namespace Books {
    class Environment {
    public:
        Environment(int argc, char** argv);
        ~Environment();

        u32 getWidth();
        u32 getHeight();

        WINDOW* getWin();

    private:
        std::string m_bookmarkPath;
        u32 m_width;
        u32 m_height;

        WINDOW* m_win;

        void initArgs(int argc, char** argv);
    };
}
