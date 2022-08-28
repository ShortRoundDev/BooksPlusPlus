#include "Book.hpp"

#include <iostream>

using namespace Books;

Book::Book(std::string path) {
    m_file = std::fstream(path);
}

Book::~Book() {

}

const std::fstream& Book::getFile() {
    return m_file;
}

u32 Book::getPageNum() {
    return m_pageNum;
}

void Book::nextPage(u32 width, u32 height, std::string& text) {
    text.clear();
    u32 cursor = 0;
    u32 lineCursor = 0;

    while(cursor < width * height) {
        char c;
        m_file.get(c);
        if(c == '\n'){
            text += "\n";
            cursor += (width - lineCursor);
            lineCursor = 0;
        } else {
            if(lineCursor >= width){
                lineCursor = 0;
                text += "\n";
            }
            text += c;
            cursor++;
            lineCursor++;
        }

    }
}
