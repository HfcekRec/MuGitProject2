#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9; // Размер поля 9x9

// Функция для вывода игрового поля
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                cout << ". ";
            else
                cout << grid[row][col] << " ";
            if ((col + 1) % 3 == 0 && col != N - 1)
                cout << "| ";
        }
        cout << endl;
        if ((row + 1) % 3 == 0 && row != N - 1)
            cout << "------+-------+------" << endl;
    }
}

// Проверка, можно ли разместить число в указанной клетке
bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {
    // Проверка строки и столбца
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Проверка квадрата 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Генерация случайного поля 9x9
void generateGrid(vector<vector<int>>& grid) {
    // Заполняем поле нулями
    grid.assign(N, vector<int>(N, 0));

    // Заполняем диагональные квадраты 3x3 случайными числами
    for (int i = 0; i < N; i += 3) {
        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        random_shuffle(numbers.begin(), numbers.end());
        int index = 0;
        for (int row = i; row < i + 3; row++) {
            for (int col = i; col < i + 3; col++) {
                grid[row][col] = numbers[index++];
            }
        }
    }

    // Удаляем некоторые числа, чтобы создать пустые клетки
    srand(time(0));
    for (int i = 0; i < N * N / 2; i++) {
        int row = rand() % N;
        int col = rand() % N;
        grid[row][col] = 0;
    }
}

// Проверка, заполнено ли поле полностью
bool isGridComplete(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return false;
        }
    }
    return true;
}

// Функция для проверки корректности ввода
bool isValidInput(int row, int col, int num) {
    return (row >= 0 && row <= N && col >= 0 && col <= N && num >= 0 && num <= N);
}

// Основная функция игры
void playSudoku() {
    vector<vector<int>> grid;
    generateGrid(grid); // Генерация случайного поля

    while (true) {
        printGrid(grid);

        // Проверка, заполнено ли поле
        if (isGridComplete(grid)) {
            cout << "Поздравляем! Вы заполнили все ячейки правильно!" << endl;
            cout << "Начинаем новую игру..." << endl;
            generateGrid(grid); // Генерация нового поля
            continue;
        }

        int row, col, num;

        // Запрос ввода с проверкой
        while (true) {
            cout << "Введите строку (1-9), столбец (1-9) и число (1-9) через пробел (или 0 0 0 для выхода): ";
            cin >> row >> col >> num;

            if (row == 0 && col == 0 && num == 0) {
                cout << "Игра завершена." << endl;
                return;
            }

            if (isValidInput(row, col, num)) {
                break; // Ввод корректен, выходим из цикла
            } else {
                cout << "Некорректный ввод. Пожалуйста, введите числа от 1 до 9 (или 0 0 0 для выхода)." << endl;
                cin.clear(); // Очистка флагов ошибок
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            }
        }

        // Корректировка индексов (пользователь вводит 1-9, а не 0-8)
        row--;
        col--;

        if (grid[row][col] != 0) {
            cout << "Эта клетка уже заполнена. Попробуйте другую." << endl;
            continue;
        }

        if (!isValid(grid, row, col, num)) {
            cout << "Число " << num << " нельзя разместить здесь. Попробуйте другое число." << endl;
            continue;
        }

        grid[row][col] = num;
        cout << "Число " << num << " успешно размещено в клетке (" << row + 1 << ", " << col + 1 << ")." << endl;
    }
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    cout << "Добро пожаловать в игру Судоку 9x9!" << endl;
    playSudoku();
    return 0;
}
