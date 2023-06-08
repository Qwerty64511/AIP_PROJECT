#include <iostream>
#include <string>
using namespace std;

// Функция для создания игрового поля заданного размера
char** createBoard(int rows, int cols)
{

  // Создаем двумерный динамический массив размера rows x cols
  char** board = new char*[rows];
  for (int i = 0; i < rows; ++i) {
    board[i] = new char[cols];
  }

  // Инициализируем массив пробелами
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      board[i][j] = ' ';
    }
  }

  // Возвращаем указатель на созданный массив
  return board;
}

// Функция для освобождения памяти, занятой игровым полем
void deleteBoard(char** board, int rows)
{
  for (int i = 0; i < rows; ++i) {
    delete[] board[i];
  }
  delete[] board;
}

// Функция для вывода игрового поля в консоль
void printBoard(char** board, int rows, int cols)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << board[i][j];
      if (j < cols - 1) {
        cout << " | ";
      }
    }
    cout << endl;
    if (i < rows - 1) {
      for (int k = 0; k < cols; ++k) {
        cout << "--";
        if (k < cols - 1) {
          cout << "-";
        }
      }
      cout << endl;
    }
  }
}

// Функция для проверки, есть ли на поле выигрышная комбинация
bool checkWin(char** board, int rows, int cols, char player)
{
  // Проверка горизонталей
  for (int i = 0; i < rows; i++) {
    bool win = true;
    for (int j = 0; j < cols; j++) {
      if (board[i][j] != player) {
        win = false;
        break;
      }
    }
    if (win) {
      return true;
    }
  }

  // Проверка вертикалей
  for (int j = 0; j < cols; j++) {
    bool win = true;
    for (int i = 0; i < rows; i++) {
      if (board[i][j] != player) {
        win = false;
        break;
      }
    }
    if (win) {
      return true;
    }
  }

  // Проверка диагоналей
  bool win = true;
  for (int i = 0; i < rows; i++) {
    if (board[i][i] != player) {
      win = false;
      break;
    }
  }
  if (win) {
    return true;
  }

  win = true;
  for (int i = 0; i < rows; i++) {
    if (board[i][cols-i-1] != player) {
      win = false;
      break;
    }
  }
  if (win) {
    return true;
  }

  // Нет выигрышных комбинаций
  return false;
}

// Функция для хода игрока
void makeMove(char** board, int rows, int cols, char player)
{
  int row, col;
  cout << player << "'s move: " << endl;
  
  // Убедимся, что игрок ввел корректные координаты
  do {
    cout << "Row (1-" << rows << "): ";
    cin >> row;
    if (row < 1 || row > rows) {
      cout << "Invalid row." << endl;
    }
  } while (row < 1 || row > rows);

  do {
    cout << "Column (1-" << cols << "): ";
    cin >> col;
    if (col < 1 || col > cols) {
      cout << "Invalid column." << endl;
    }
  } while (col < 1 || col > cols);

  // Помещаем символ игрока на поле (если клетка свободна)
  if (board[row-1][col-1] == ' ') {
    board[row-1][col-1] = player;
  } else {
    cout << "That spot is already taken." << endl;
    makeMove(board, rows, cols, player);
  }
}

int main() 
{
  int rows, cols;
  
  // Начало игры
  cout << "Welcome to Tic Tac Toe!" << endl;

  // Спросить размер поля у пользователя
  do {
    cout << "Enter the number of rows (>=3): ";
    cin >> rows;
    if (rows < 3) {
      cout << "Invalid number of rows." << endl;
    }
  } while (rows < 3);

  do {
    cout << "Enter the number of columns (>=3): ";
    cin >> cols;
    if (cols < 3) {
      cout << "Invalid number of columns." << endl;
    }
  } while (cols < 3);

  // Создаем игровое поле заданного размера
  char** board = createBoard(rows, cols);

  bool gameOver = false;
  char currentPlayer = 'X';

  // Игровой цикл
  while (!gameOver) {
  printBoard(board, rows, cols);
  makeMove(board, cols, rows, currentPlayer);
  // Проверяем, есть ли победитель или ничья
  if (checkWin(board, rows, cols, currentPlayer)) {
    gameOver = true;
    cout << currentPlayer << " wins!" << endl;
  } else if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' && board[1][0] != ' ' 
            && board[1][1] != ' ' && board[1][2] != ' ' && board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ' ) {
    gameOver = true;
    cout << "It's a tie!" << endl;
  }
  // Смена игрока
  if (currentPlayer == 'X') {
    currentPlayer = 'O';
  } else {
    currentPlayer = 'X';
  }
}
// Окончание игры
printBoard(board, rows, cols);
return 0;
}
