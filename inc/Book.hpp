#pragma once

#include "Types.hpp"

#include <string>
#include <fstream>

namespace Books {
    class Book {
    public:
        Book(std::string path);
        ~Book();
        
        u32 getPageNum();
        const std::fstream& getFile();
        
        void nextPage(u32 width, u32 height, std::string& text);
        void prevPage();

        void gotoPage(u32 page);

    private:
        std::string m_path;
        u32 m_pageNum;
        std::fstream m_file;
    };
}

