#include "Environment.hpp"

#include <cstring>

#include <iostream>

using namespace Books;

Environment::Environment(int argc, char** argv) :
    m_width(22),
    m_height(45),
    m_win(NULL)
{
    initArgs(argc, argv);
    m_win = initscr();
}

Environment::~Environment() {
    endwin();
}

void Environment::initArgs(int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "-b")) {
            m_bookmarkPath = std::string(argv[i + 1]);
            i++;
        } else if(!strcmp(argv[i], "-w")){
            m_width = atoi(argv[i + 1]);
            i++;
        } else if(!strcmp(argv[i], "-h")){
            m_height = atoi(argv[i + 1]);
            i++;
        }        
    }
}

u32 Environment::getWidth() {
    return m_width;
}

u32 Environment::getHeight() {
    return m_height;
}

WINDOW* Environment::getWin() {
    return m_win;
}

