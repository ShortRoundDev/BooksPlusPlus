#pragma once

#include "Environment.hpp"
#include "BookViewModel.hpp"
#include "Book.hpp"

namespace Books {
    class MainWindowViewModel {
    public:
        MainWindowViewModel(Environment& environment, Book& book);
        ~MainWindowViewModel();
        
        void draw();

        BookViewModel& getBookViewModel();

    private:
        Environment& m_environment;
        BookViewModel m_bookViewModel;

    };
}
