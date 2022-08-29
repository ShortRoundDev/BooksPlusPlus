#pragma once

#include "Types.hpp"

#include <string>
#include <fstream>
#include <map>

namespace Books {
    class Book {
    public:
        Book(std::string path);
        ~Book();
        
        Page getPageNum();
        std::fstream& getFile();
        
        void nextPage(u32 width, u32 height, std::string& text);

        void gotoPage(u32 width, u32 height, Page page, std::string& text);

    private:
        std::string m_path;
        Page m_pageNum;
        std::fstream m_file;
        std::map<Page, std::streampos> m_pageLookupBuffer;
        std::streampos m_nextPage;
        bool m_end;

        std::streampos readPage(u32 width, u32 height, std::streampos position, std::string& text, bool& end);
        std::streampos findPageOffset(u32 width, u32 height, Page absolutePage, std::string& text, Page& actualPage);
    };
}

