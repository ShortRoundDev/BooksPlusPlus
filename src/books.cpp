#include "books.hpp"

#include "Book.hpp"
#include "Environment.hpp"
#include "BookViewModel.hpp"
#include "MainWindowViewModel.hpp"

#include <curses.h>

#include <iostream>

using namespace Books;

int main(int argc, char** argv) {
    std::string path = std::string(argv[1]);

    Environment environment(argc, argv);
    
    Book book(path);
    MainWindowViewModel mainWindow(environment, book);

    mainWindow.draw();
    while(true) {
        char c = getch();

        if(c == 'n') {
            mainWindow.getBookViewModel().nextPage();
        }
        if(c == 'b') {
            mainWindow.getBookViewModel().prevPage();
        }

        mainWindow.draw();
    }
}
