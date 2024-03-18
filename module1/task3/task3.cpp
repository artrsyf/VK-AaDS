#include <iostream>
#include <sstream>
#include <cassert>

/*
* 3_2. Реализовать дек с динамическим зацикленным буфером (на основе динамического массива).
* Требования: Дек должен быть реализован в виде класса.
*
* in              out
* -------------------
* 3               YES
* 1 44
* 3 50
* 2 44
* -------------------
* 2               YES
* 2 -1
* 1 10
* -------------------
* 2               NO
* 3 44
* 4 66
*/

template <typename T>
class Deque
{
public:
    Deque();

    Deque( const Deque & deque );

    Deque & operator=( const Deque & deque );

    ~Deque();

    void pushFront( T data );

    void pushBack( T data );

    T popFront();

    T popBack();

    int getSize () const;

    void display( std::ostream& output ) const;

private:
    T * buffer;
    int head_index;
    int tail_index;
    int size;
    int capacity;

    void resize();
};

template <typename T>
Deque<T>::Deque() : head_index( 1 ), tail_index( 0 ), size( 0 ), capacity( 5 )
{
    buffer = new T[capacity];
}

template <typename T>
Deque<T>::Deque( const Deque<T> & deque )
{
    this->capacity = deque.capacity;
    this->size = deque.size;
    this->head_index = deque.head_index;
    this->tail_index = deque.tail_index;

    this->buffer = new T[this->capacity];

    for ( size_t i = 0; i < this->capacity; ++i )
    {
        this->buffer[i] = deque.buffer[i];
    }
}

template <typename T>
Deque<T> & Deque<T>::operator=( const Deque<T> & deque )
{
    if ( this != &deque )
    {
        delete[] this->buffer;

        this->capacity = deque.capacity;
        this->size = deque.size;
        this->head_index = deque.head_index;
        this->tail_index = deque.tail_index;

        this->buffer = new T[this->capacity];

        for ( size_t i = 0; i < this->capacity; ++i )
        {
            this->buffer[i] = deque.buffer[i];
        }
    }

    return *this;
}

// Освобождение памяти
template <typename T>
Deque<T>::~Deque()
{
    delete[] buffer;
}

template <typename T>
void Deque<T>::pushBack( T data )
{
    if ( size == capacity )
        resize();

    head_index--;

    if ( head_index == -1 )
    {
        head_index = capacity - 1;
    }

    buffer[head_index] = data;
    size++;
}

// Метод для динамического увеличения размера буффера
template <typename T>
void Deque<T>::resize()
{
    capacity *= 2;
    T * new_buffer = new T[capacity];

    bool make_once = true;
    int loop_bound = size;

    // ordered_index используем, чтобы не было зацикленности
    // в новом буффере (т.к. у него объем больше в 2 раза)
    int oredered_index = 0;

    // Проходим по буфферу от индекса первого элемента
    // до границы (в начале она равна размеру массива),
    // как только head_index дошел до конца буффера,
    // перемещаем его на 0 индекс и устанавливаем границу,
    // равную tail_index. Это нужно для прохождения
    // зацикленного буффера
    for ( int i = head_index; i < loop_bound; ++i )
    {
        new_buffer[oredered_index] = buffer[i];
        oredered_index++;

        // Случай, когда head_index дошел до конца буффера.
        // Очевидно, что для обхода буффера, нужно переместить head_index
        // только один раз (реализует флаг make_once).
        // i устанавливаем как -1, чтобы на следующей итерации
        // иметь индекс 0
        if ( i == size - 1 && make_once )
        {
            i = -1;
            loop_bound = tail_index + 1;
            make_once = false;
        }   
    }

    head_index = 0;
    tail_index = size - 1;

    // Освобождение памяти после переноса старого буффера
    delete[] buffer;
    buffer = new_buffer;
}

template <typename T>
void Deque<T>::pushFront( T data )
{
    if ( size == capacity )
        resize();

    tail_index++;

    if ( tail_index == capacity )
    {
        tail_index = 0;
    }
    
    buffer[tail_index] = data;
    size++;
}

template <typename T>
T Deque<T>::popBack()
{
    if ( size == 0 )
        return -1;

    T pop_element = buffer[head_index];
    if ( head_index == capacity - 1 )
    {
        head_index = 0;
    }
    else
    {
        head_index++;
    }

    size--;

    return pop_element;
}

template <typename T>
T Deque<T>::popFront()
{
    if ( size == 0 )
        return -1;

    T pop_element = buffer[tail_index];
    if ( tail_index == 0 )
    {
        tail_index = capacity - 1;
    }
    else
    {
        tail_index--;
    }
    
    size--;

    return pop_element;
}

// Для дебага, выводит непрерывно элементы так,
// как они находятся в памяти
template <typename T>
void Deque<T>::display( std::ostream& output ) const
{
    output << "\nBegin and end indexes: " << head_index << " " << tail_index << "\nArray is: ";

    for ( size_t i = 0; i < capacity; ++i )
    {
        output << buffer[i] << "[address: " << buffer + i << ']' << ' ';
    }
}

void run( std::istream& input, std::ostream& output )
{
    int command_count = 0, command_number = 0, data = 0;
    Deque<int> * my_deque = new Deque<int>();
    input >> command_count;
    bool result = true;

    while ( command_count-- )
    {
        input >> command_number >> data;
        switch( command_number )
        {
            case 1:
                my_deque->pushFront( data );
                break;
            case 2:
                result &= ( my_deque->popFront() == data );
                break;
            case 3:
                my_deque->pushBack( data );
                break;
            case 4:
                result &= ( my_deque->popBack() == data );
                break;
        }
    }

    output << ( result ? "YES" : "NO" );
}

template <typename T>
int Deque<T>::getSize () const
{
    return this->size();
}

void testDeque()
{
    {
        std::stringstream input;
        std::stringstream output;

        input << "3\n1 44\n3 50\n2 44";
        run( input, output );
        assert( output.str() == "YES" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2\n2 -1\n1 10";
        run( input, output );
        assert( output.str() == "YES" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2\n3 44\n4 66";
        run( input, output );
        assert( output.str() == "NO" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "12\n3 44\n3 66\n3 12\n3 21\n3 89\n3 43\n2 44\n2 66\n2 12\n2 21\n2 89\n2 43";
        run( input, output );
        assert( output.str() == "YES" );
    }
    {
        Deque<int> * first_deque = new Deque<int>();
        first_deque->pushBack( 1 );
        first_deque->pushBack( 22 );

        Deque<int> * second_deque = new Deque<int>( * first_deque );

        std::cout << "Copy constructor test: " << '\n';
        first_deque->display(std::cout);
        second_deque->display(std::cout);
    }
    {
        Deque<int> * first_deque = new Deque<int>();
        first_deque->pushBack( 1 );
        first_deque->pushBack( 22 );

        Deque<int> * second_deque = new Deque<int>();
        second_deque->pushBack( 333 );
        second_deque->pushBack( 4444 );

        *second_deque = *first_deque;

        std::cout << "\nOperator= test: " << '\n';
        first_deque->display( std::cout );
        second_deque->display( std::cout );
    }
}

int main()
{
    // testDeque();

    run( std::cin, std::cout );

    return 0;
}