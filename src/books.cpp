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

    while(true) {
        mainWindow.draw();
        char c = getch();

        if(c == 'n') {
            mainWindow.getBookViewModel().nextPage();
        }

    }
}
