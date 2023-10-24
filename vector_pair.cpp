#include <iostream>
#include <vector>
#include <algorithm>

template <typename T1, typename T2>
struct PairContainer
{
    std::vector<std::pair<T1, T2>> pairs;

    // Метод для добавления пары
    void addPair(const T1 &first, const T2 &second)
    {
        pairs.emplace_back(first, second);
    }

    // Метод для удаления пары по индексу
    void removePair(int index)
    {
        if (index >= 0 && index < pairs.size())
        {
            pairs.erase(pairs.begin() + index);
        }
    }

    // Метод для сортировки по первым элементам пар
    void sortByFirst()
    {
        std::sort(pairs.begin(), pairs.end(), [](const auto &left, const auto &right)
                  { return left.first < right.first; });
    }

    // Метод для сортировки по вторым элементам пар
    void sortBySecond()
    {
        std::sort(pairs.begin(), pairs.end(), [](const auto &left, const auto &right)
                  { return left.second < right.second; });
    }
};

int main()
{
    PairContainer<int, std::string> container;

    container.addPair(1, "one");
    container.addPair(3, "three");
    container.addPair(2, "two");

    // Вывод пар до сортировки
    std::cout << "Pairs before sorting:" << std::endl;
    for (const auto &pair : container.pairs)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Сортировка по первым элементам пар
    container.sortByFirst();
    std::cout << "Pairs sorted by first element:" << std::endl;
    for (const auto &pair : container.pairs)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Сортировка по вторым элементам пар
    container.sortBySecond();
    std::cout << "Pairs sorted by second element:" << std::endl;
    for (const auto &pair : container.pairs)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Удаление первой пары
    container.removePair(0);
    std::cout << "Pairs after removing first pair:" << std::endl;
    for (const auto &pair : container.pairs)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
