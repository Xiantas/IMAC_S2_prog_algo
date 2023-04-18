#include <iostream>

int fibonacci(int value)
{
    if (value <= 1) return value;

    int u(0), v(1);
    for (int i(1); i < value; i++) {
        int temp = v;

        v += u;
        u = temp;
    }

    return v;
}

int recursiveFibonacci(int value)
{
    if (value <= 1) return value;

    return recursiveFibonacci(value-1) + recursiveFibonacci(value-2);
}

int main(int argc, char *argv[])
{
    int x;
    std::cout << "Numbre de fibonacci n° ? ";
    std::cin >> x;

    std::cout << "\n" << fibonacci(x) << '\n' << recursiveFibonacci(x) << '\n';
    
    return 0;
}
