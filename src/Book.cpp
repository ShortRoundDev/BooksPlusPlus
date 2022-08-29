#include "Book.hpp"

#include <iostream>

#include <ncurses.h>

using namespace Books;

Book::Book(std::string path) :
    m_path(path),
    m_pageNum(-1),
    m_file(std::fstream(path)),
    m_pageLookupBuffer(),
    m_nextPage()
{
    m_pageLookupBuffer[0] = m_file.tellg();
    m_nextPage = m_file.tellg();
}

Book::~Book() {

}

std::fstream& Book::getFile() {
    return m_file;
}

Page Book::getPageNum() {
    return m_pageNum;
}

void Book::nextPage(u32 width, u32 height, std::string& text) {
    if(m_end){
        std::cerr << "Reached end of book!" << std::endl;
        return;
    }

    m_pageNum++;
    m_nextPage = readPage(width, height, m_nextPage, text, m_end);
    m_pageLookupBuffer[m_pageNum + 1] = m_nextPage;
    std::cerr << "----" <<std::endl;
    std::cerr << "PageNum: " << m_pageNum << std::endl;
    std::cerr << "NextPage: " << (u64)m_nextPage << std::endl;
    std::cerr << "Ended: " << m_end << std::endl;
    std::cerr << "----" <<std::endl;
}

std::streampos Book::readPage(u32 width, u32 height, std::streampos position, std::string& text, bool& ended) {
    text.clear();
    m_file.clear();
    m_file.seekg(position);
    
    u32 cursor = 0;
    u32 lineCursor = 0;

    ended = false;
   
    while(cursor < width * height) {
        char c = m_file.get();
        if(c == '\n'){
            text += "\n";
            cursor += (width - lineCursor);
            lineCursor = 0;
        } else if(c == EOF){
            std::cerr << "Reached end of file. breaking." << std::endl;
            ended = true;
            break;
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

    auto nextPage = m_file.tellg();
    m_file.seekg(position);

    return nextPage;
}

std::streampos Book::findPageOffset(
    u32 width,
    u32 height,
    Page absolutePage,
    std::string& text,
    Page& actualPage
) {
    //page already cached, return it
    auto currentPos = m_file.tellg();
    auto found = m_pageLookupBuffer.find(absolutePage);
    if(found != m_pageLookupBuffer.end()){
        actualPage = found->first;
        std::cerr << "found! pos is " << (Page)found->second << std::endl;
        return found->second;
    }

    auto pos = m_pageLookupBuffer.lower_bound(absolutePage);
    if(pos != m_pageLookupBuffer.begin() && pos->first > absolutePage) {
        pos--;
    }
    Page start = pos->first;
    Page offset = absolutePage - start;

    std::cerr << "Searching for page " << absolutePage << ". offset is " << offset << std::endl;

    m_file.seekg(pos->second);

    auto posIter = m_file.tellg();
    Page iOff = 0;
    for(; iOff < offset; iOff++){
        bool ended = false;
        posIter = readPage(width, height, posIter, text, ended);
        if(ended) {
            break;
        }
    }

    actualPage = start + iOff;

    m_file.seekg(currentPos);

    return posIter;
}

void Book::gotoPage(u32 width, u32 height, Page page, std::string& text) {
    if(page < 0) {
        std::cerr << "At beginning. cannot continue." << std::endl;
        return;
    }
    auto pos = findPageOffset(width, height, page, text, m_pageNum);
    std::cerr << "pagenum is now: " << m_pageNum << std::endl;
    m_nextPage = readPage(width, height, pos, text, m_end);
    std::cerr << "-=-=-=-=-=-=-=-=-" << std::endl;
    std::cerr << text << std::endl;
}

