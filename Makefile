CC=clang++
CONFIG=.clang
OBJ=./obj
BIN=./bin
SRC=./src
CFG=--config ./.clang

all: Book.o books.o Environment.o BookViewModel.o MainWindowViewModel.o
	$(CC) $(OBJ)/*.o -o $(BIN)/books -lncurses

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/books

books.o:
	$(CC) $(SRC)/books.cpp -c -o $(OBJ)/books.o $(CFG)

Book.o:
	$(CC) $(SRC)/Book.cpp -c -o $(OBJ)/Book.o $(CFG)

Environment.o:
	$(CC) $(SRC)/Environment.cpp -c -o $(OBJ)/Environment.o $(CFG)

BookViewModel.o:
	$(CC) $(SRC)/BookViewModel.cpp -c -o $(OBJ)/BookViewModel.o $(CFG)

MainWindowViewModel.o:
	$(CC) $(SRC)/MainWindowViewModel.cpp -c -o $(OBJ)/MainWindowViewModel.o $(CFG)

