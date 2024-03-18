#include <iostream>
#include <sstream>
#include <cassert>

template <typename T>
class Deque
{
public:
    Deque(); 

    ~Deque(){};

    void pushFront(T data);

    void pushBack(T data);

    T popFront();

    T popBack();

    void resize();

    void display();

private:
    T * buffer;
    int head_index;
    int tail_index;
    int size;
    int capacity;
};

template <typename T>
Deque<T>::Deque() : head_index(1), tail_index(0), size(0), capacity(5)
{
    buffer = new T[capacity];
}

template <typename T>
void Deque<T>::pushBack(T data)
{
    if ( size == capacity )
        resize();

    head_index--;

    if (head_index == -1)
    {
        head_index = capacity - 1;
        // assert( tail_index != capacity - 1 );
    }

    buffer[head_index] = data;
    
    size++;
}

// refactor
template <typename T>
void Deque<T>::resize()
{
    capacity *= 2;
    T * new_buffer = new T[capacity];
    bool make_once = true;
    int loop_bound = size;
    int oredered_index = 0;

    for ( int i = head_index; i < loop_bound; ++i )
    {
        new_buffer[oredered_index] = buffer[i];
        oredered_index++;

        if ( i == size - 1 && make_once )
        {
            i = -1;
            loop_bound = tail_index + 1;
            make_once = false;
        }   
    }

    head_index = 0;
    tail_index = size - 1;

    delete[] buffer;
    buffer = new_buffer;
}

template <typename T>
void Deque<T>::pushFront(T data)
{
    if ( size == capacity )
        resize();

    tail_index++;

    if (tail_index == capacity)
    {
        tail_index = 0;
        // assert( head_index != 0 );
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

template <typename T>
void Deque<T>::display()
{
    std::cout << "\nBegin and end indexes: " << head_index << " " << tail_index << "\nArray is: ";
    for (int i = 0; i < capacity; ++i)
    {
        std::cout << buffer[i] << ' ';
    }
}

void run( std::istream& input, std::ostream& output )
{
    int command_count = 0, command_number = 0, data = 0;
    Deque<int> * my_deque = new Deque<int>();
    input >> command_count;
    bool result = true;

    while (command_count--)
    {
        input >> command_number >> data;
        int test = 0;
        switch( command_number )
        {
            case 1:
                my_deque->pushFront(data);
                break;
            case 2:
                result &= (my_deque->popFront() == data);
                break;
            case 3:
                my_deque->pushBack(data);
                break;
            case 4:
                result &= (my_deque->popBack() == data);
                break;
        }
    }

    output << (result ? "YES" : "NO");
}

void testDeque()
{
    {
        std::stringstream input;
        std::stringstream output;

        input << "3\n1 44\n3 50\n2 44";
        run( input, output );
        std::cout << output.str() << '\n';
        // assert( output.str() == "0 0 0 2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2\n2 -1\n1 10";
        run( input, output );
        std::cout << output.str() << '\n';
        // assert( output.str() == "0 0 0 2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2\n3 44\n4 66";
        run( input, output );
        std::cout << output.str() << '\n';
        // assert( output.str() == "0 0 0 2" );
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "12\n3 44\n3 66\n3 12\n3 21\n3 89\n3 43\n2 44\n2 66\n2 12\n2 21\n2 89\n2 43";
        run( input, output );
        std::cout << output.str() << '\n';
        // assert( output.str() == "0 0 0 2" );
    }
}

int main()
{
    // testDeque();
    run( std::cin, std::cout );

    // Deque<int> * my = new Deque<int>();
    // // 213456
    // my->pushBack(44);
    // my->display();
    // my->pushBack(66);
    // my->display();
    // my->pushBack(12);
    // my->display();
    // my->pushBack(21);
    // my->display();
    // my->pushBack(89);
    // my->display();
    // // 89 21 12 66 44
    // my->pushBack(43);
    // my->display();
    // std::cout << '\n' << my->popFront() << '\n';
    // my->display();
    // std::cout << '\n' << my->popFront() << '\n';
    // my->display();
    // std::cout << '\n' << my->popFront() << '\n';
    // my->display();
    // std::cout << '\n' << my->popFront() << '\n';
    // std::cout << '\n' << my->popFront() << '\n';
    // std::cout << '\n' << my->popFront() << '\n';

    return 0;
}