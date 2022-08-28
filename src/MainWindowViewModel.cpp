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
   m_bookViewModel.draw(); 
}

BookViewModel& MainWindowViewModel::getBookViewModel() {
    return m_bookViewModel;
}
