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

    Book book(path);
    Environment environment(argc, argv);

    MainWindowViewModel mainWindow(environment, book);

    mainWindow.draw();
    while(true) {
        char c = getch();

        if(c == 'n') {
            mainWindow.getBookViewModel().nextPage();
        }
        if(c == 'b') {
            mainWindow.getBookViewModel().prevPage();
            std::cerr << "B!" << std::endl;
        }

        std::cerr << "redrawing..." << std::endl;

        mainWindow.draw();
    }
}
