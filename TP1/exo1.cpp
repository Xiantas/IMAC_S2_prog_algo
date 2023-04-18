#include <iostream>

long power(long value, long n)
{
    if (n<0) return 0;

    long res = value;

    while (n > 1) {
        if (n % 2 == 1) {
            res *= value*res;
            n/=2;
        } else {
            res *= res;
            n/=2;
        }
    }

    return res;
}

long _hiddenRecursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(long value, long n, long acc) {
    if (n <= 1) return acc;

    if (n % 2 == 1) {
        return _hiddenRecursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(value, n/2, acc*acc*value);
    } else {
        return _hiddenRecursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(value, n/2, acc*acc);
    }
}

long recursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(long value, long n) {
    if (n == 0) return 1;

    if (n < 0) return 0;

    return _hiddenRecursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(value, n, value);
}

int main(int argc, char *argv[])
{
    long value, exponant;

    std::cout << "La valeur ? ";
    std::cin >> value;
    std::cout << "La puissance ? ";
    std::cin >> exponant;

    std::cout << "\n" << power(value, exponant) << "\n";
    std::cout << "\n" << recursivePowerThatYouShouldntUseBecauseItIsSuboptimalHenceTheLongNameAimingToDiscourageYou(value, exponant) << "\n";

    return 0;
}
