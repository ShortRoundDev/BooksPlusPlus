#include "Book.hpp"

#include <iostream>

#include <ncurses.h>

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
    m_pageNum++;
    m_pageLookupBuffer[m_pageNum] = m_file.tellg();
    std::cerr << "Page " << m_pageNum << " at " << (u64)m_file.tellg() << std::endl;
}

std::streampos Book::findPageOffset(u32 width, u32 height, u32 absolutePage, std::string& text) {
    //page already cached, return it
    if(m_pageLookupBuffer.find(absolutePage) != m_pageLookupBuffer.end()){
        std::cerr << "Found exact location! " << absolutePage << std::endl;
        m_pageNum = absolutePage;
        auto exactPos = m_pageLookupBuffer[absolutePage];

        m_file.seekg(exactPos);
        return exactPos;
    }

    auto pos = m_pageLookupBuffer.lower_bound(absolutePage);
    if(pos == m_pageLookupBuffer.end()) {
        //cache is probably empty
    }
    u32 start = pos->first;
    u32 offset = absolutePage - start;

    m_file.seekg(pos->second);
    m_pageNum = start;

    for(u32 i = 0; i < offset; i++){
        nextPage(width, height, text);
    }

    return m_file.tellg();
}

void Book::gotoPage(u32 width, u32 height, u32 page, std::string& text) {
    if(page < 1) {
        return;
    }
    findPageOffset(width, height, page, text);
}
