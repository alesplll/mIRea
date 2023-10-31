#include <iostream>
#include <sstream>
#include <string>

int safeInputInt()
{
    int number;
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);
        std::stringstream ss(input);
        bool valid = true; // Флаг для проверки корректности ввода

        while (ss >> number) // Чтение чисел из строки
        {
            if (ss.peek() == ' ' || ss.peek() == '\t')
            {
                ss.ignore(); // Пропустить пробелы или табуляцию
            }
            else
            {
                valid = false; // Если не удалось прочитать число (например, символы или буквы)
                break;
            }
        }

        if (valid && ss.eof())
        {
            return number; // Возвращаем последнее успешно считанное число
        }
        else
        {
            std::cout << "Invalid input. Enter valid numbers separated by spaces. Try again: ";
            ss.clear();
        }
    }
}

int main()
{
    std::cout << "Enter numbers separated by spaces: ";
    int num = safeInputInt();
    std::cout << "You entered: " << num << std::endl;
    return 0;
}
