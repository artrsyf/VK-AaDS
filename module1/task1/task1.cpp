#include <iostream>
#include <cinttypes>
#include <sstream>
#include <cassert>

/*
* 1.1 Подсчитать кол-во единичных бит в входном числе ,
* стоящих на четных позициях. Позиции битов нумеруются с 0.
* in  25
* out 2
*/

int countOneBits( uint32_t number )
{
    int count = 0;
    while ( number != 0 )
    {
        // Проверяем младший разряд
        count += number & 1;

        // Создаем маску и с ее помощью обнуляем 2 младших разряда
        uint32_t mask = ~3;
        number &= mask;

        // Делаем сдвиг на две позиции для поиска четных
        number >>= 2;
    }

    return count;
}

void run( std::istream & input, std::ostream & output )
{
    uint32_t number = 0;
    input >> number;
    output << countOneBits( number );
}

void testCountOneBits()
{
    {
        std::stringstream input;
        std::stringstream output;

        input << "25";
        run( input, output );
        assert( output.str() == "2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "16327";
        run( input, output );
        assert( output.str() == "6" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "1024";
        run( input, output );
        assert( output.str() == "1" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "0";
        run( input, output );
        assert( output.str() == "0" );
    }

    std::cout << "Success" << '\n';
}

int main()
{
    // testCountOneBits();

    run( std::cin, std::cout );

    return 0;
}   