#include "MainWindowViewModel.hpp"


using namespace Books;

MainWindowViewModel::MainWindowViewModel(Environment& environment, Book& book):
    m_environment(environment),
    m_bookViewModel(book, environment)
{

}

MainWindowViewModel::~MainWindowViewModel() {

}

void MainWindowViewModel::draw() {
    int w, h;
    getmaxyx(m_environment.getWin(), h, w);
    for(int i = 0; i < h; i++) {
        wmove(m_environment.getWin(), i, 0);
        wclrtoeol(m_environment.getWin());
    }
    m_bookViewModel.draw(); 
}

BookViewModel& MainWindowViewModel::getBookViewModel() {
    return m_bookViewModel;
}
