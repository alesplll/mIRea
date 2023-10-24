#include <iostream>
#include <sstream>

const std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
typedef unsigned int UI;

void Reverse(std::string &str)
{
    UI i = -1, j = str.length();
    while (++i < --j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
bool ValidNumber(std::string &num, int base)
{
    if (base < 2 || base > 36)
        return false;

    UI i = -1;
    while (++i < num.length())
        if (alphabet.find(num[i]) >= base)
            return false;
    return true;
}
bool DecimalToBase(UI num, int dest_base, std::string &dest)
{
    if (dest_base < 2 || dest_base > 36)
        return false;

    while (num)
    {
        dest += alphabet[num % dest_base];
        num /= dest_base;
    }
    Reverse(dest);
    return true;
}

bool BaseToDecimal(std::string &source, int source_base, UI &num)
{
    if (source_base < 2 || source_base > 36)
        return false;

    if (!ValidNumber(source, source_base))
        return false;

    Reverse(source);
    UI i = -1, shift = 1;
    while (++i < source.length())
    {
        num += alphabet.find(source[i]) * shift;
        shift *= source_base;
    }
    return true;
}

bool BaseToBase(int source_base, std::string &source, int dest_base, std::string &dest)
{
    if (source_base < 2 || source_base > 36 || dest_base < 2 || dest_base > 36)
        return false;

    if (!ValidNumber(source, source_base))
        return false;

    UI temp = 0;
    if (source_base != 10)
        BaseToDecimal(source, source_base, temp);

    DecimalToBase(temp, dest_base, dest);
    return true;
}

int main()
{
    // перевод из любой в любую
    std::string source = "111";
    std::string dest = "\0";
    BaseToBase(2, source, 10, dest);
    std::cout << dest;

    std::cin.get();
    return 0;
}