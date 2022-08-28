#pragma once

#include "Types.hpp"

#include "Book.hpp"
#include "Environment.hpp"

namespace Books {
    class BookViewModel {
    public:
        BookViewModel(Book& book, Environment& environment);
        ~BookViewModel();

        void gotoPage(u32 page);
        void nextPage();

        void draw();

    private:
        Book& m_book;
        Environment& m_environment;
        std::string m_buffer;

        void drawPage();
        void drawText();
    };
}

