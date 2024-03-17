#include <iostream>
#include <sstream>
#include <cassert>

/*
*2_4. Дан отсортированный массив различных целых чисел A[0..n-1] 
* и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] 
* найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
* Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). 
* Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для 
* бинарного поиска размером порядка k с помощью экспоненциального поиска, 
* а потом уже в нем делать бинарный поиск.
*/

int binarySearch( int target_element, int* sorted_array, int left_bound, int right_bound )
{
    // Алгоритм остановится на том моменте, когда будет найдено два кандидата
    while ( left_bound < right_bound - 1 )
    {
        int middle_index = ( left_bound + right_bound ) / 2;
        if ( sorted_array[middle_index] < target_element )
        {
            left_bound = middle_index;
        }
        else
        {
            right_bound = middle_index;
        }
    }

    if ( abs(target_element - sorted_array[left_bound]) <= 
         abs(target_element - sorted_array[right_bound]) )
    {
        return left_bound;
    }
    else
    {
        return right_bound;
    }
}

int exponentialSearch( int target_element, int* sorted_array, int sorted_array_length )
{
    int right_bound = 1;
    while ( right_bound < sorted_array_length && sorted_array[right_bound] < target_element )
    {
        right_bound *= 2;
    }

    if ( right_bound >= sorted_array_length )
    {
        right_bound = sorted_array_length - 1;
    }

    return binarySearch( target_element, sorted_array, right_bound / 2, right_bound );
}

// Данный метод читает строчку из заданного потока и создает из нее массив
int * readLineAsArray( int array_length, std::istream& input )
{
    int * new_array = new int[array_length];
    for ( size_t i = 0; i < array_length; ++i )
    {
        input >> new_array[i];
    }

    return new_array;
}

// Описание функции решения задачи
int ( * findTwins )( int target_element, int* sorted_array, int sorted_array_length ) { exponentialSearch };

void run( std::istream& input, std::ostream& output )
{
    int sorted_array_length = 0;
    int targets_array_length = 0;
    std::size_t i = 0;

    input >> sorted_array_length;
    int * sorted_array = readLineAsArray( sorted_array_length, input );

    input >> targets_array_length;
    int * targets_array = readLineAsArray( targets_array_length, input );

    for ( i = 0; i < targets_array_length; ++i )
    {
        int currenttarget_element = targets_array[i];

        output << findTwins( currenttarget_element, sorted_array, sorted_array_length );

        if ( i != targets_array_length - 1 )
        {
            output << " ";
        }
    }

    // Освобождение памяти
    delete[] sorted_array;
    delete[] targets_array;
}

void testFindTwins()
{
    {
        std::stringstream input;
        std::stringstream output;

        input << "3\n10 20 30\n3\n9 15 35";
        run( input, output );
        assert( output.str() == "0 0 2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "3\n10 20 30\n4\n8 9 10 32";
        run( input, output );
        assert( output.str() == "0 0 0 2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "1\n10\n3\n9 15 35";
        run( input, output );
        assert( output.str() == "0 0 0" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "4\n10 20 30 40\n1\n35";
        run( input, output );
        assert( output.str() == "2" );
    }

    std::cout << "Success" << '\n';
}

int main()
{
    // testFindTwins();

    run( std::cin, std::cout );
}