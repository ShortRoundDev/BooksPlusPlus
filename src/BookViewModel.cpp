#include "BookViewModel.hpp"

using namespace Books;

BookViewModel::BookViewModel(Book& book, Environment& environment):
    m_book(book),
    m_environment(environment)
{
    int buffSize = m_environment.getWidth() & m_environment.getHeight();
    m_buffer.reserve(buffSize);
    nextPage();
}

BookViewModel::~BookViewModel() {

}

void BookViewModel::gotoPage(u32 page) {
    for(u32 i = 0; i < page; i++) {
        nextPage();
    }
}

void BookViewModel::nextPage() {
    m_book.nextPage(m_environment.getWidth(), m_environment.getHeight(), m_buffer);
}

void BookViewModel::draw(){
    drawPage();
    drawText();
}

void BookViewModel::drawPage() {
    int w = 0, h = 0;
    getmaxyx(m_environment.getWin(), w, h);

    const int
        pageW = m_environment.getWidth(),
        pageH = m_environment.getHeight();

    const int startX = w / 2 - pageW / 2 - 1;
    const int startY = h / 2 - pageH / 2 - 2;

    mvaddch(startY, startX, '*');
    for(int i = startX + 1; i < startX + pageW + 3; i++){
        mvaddch(startY, i, '-');
    }
    mvaddch(startY, startX + pageW + 3, '*');
    
    for(int i = startY; i < startY + pageH + 4; i++) {
        mvaddch(i, startX, '|');
    }
}

void BookViewModel::drawText() {

    int w = 0, h = 0;
    getmaxyx(m_environment.getWin(), w, h);

    const int
        pageW = m_environment.getWidth(),
        pageH = m_environment.getHeight();

    const int startX = w / 2 - pageW / 2;
    const int startY = h / 2 - pageH / 2;

    int x = startX;
    int y = startY;

    const char* cStr = m_buffer.c_str();

    char c = cStr[0];
    for(int i = 0; c != '\0'; i++, c = cStr[i]){
        if(c == '\n'){
            y++;
            x = startX;
            continue;
        } else {
            x++;
            mvaddch(y, x, cStr[i]);
        }
    }
}
