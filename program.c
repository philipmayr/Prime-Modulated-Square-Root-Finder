// Shanks' Algorithm

#include <stdio.h>

int find_greatest_common_divisor(int a, int b)
{
    int common_divisor = 1;
    
    while ((~a & 1) && (~b & 1))
    {
        a >>= 1;
        b >>= 1;
        
        common_divisor <<= 1;
    }
    
    while (a)
    {
        while (~a & 1) a >>= 1;
        while (~b & 1) b >>= 1;
        
        if (a >= b) a = (a - b) >> 1;
        else b = (b - a) >> 1;
    }

    int greatest_common_divisor = common_divisor * b;
    
    return greatest_common_divisor
}

int exponentiate_modularly(int base, int index, int modulus)
{
    if (base == 0) return 0;
    if (index == 0) return 1;

    if (base > modulus) base %= modulus;
    if (index == 1) return base;
    
    int residue = 1;
    
    while (index)
    {
        if (index & 1) residue = (residue * base) % modulus;
        
        base = (base * base) % modulus;
        index >>= 1;
    }
    
    return residue;    
}

int find_multiplicative_order(int modulus, int base)
{
    if (find_greatest_common_divisor(modulus, base) != 1) return -1;
    
    for (int order = 3; order < modulus; order++)
        if (exponentiate_modularly(base, order, modulus) == 1) return order;
}

int find_modular_square_root(int square, int prime_modulus)
{
    if (find_greatest_common_divisor(square, prime_modulus) != 1) return -1;
    
    int prime_modulus_less_one = prime_modulus - 1;
    
    if (exponentiate_modularly(square, prime_modulus_less_one >> 1, prime_modulus) == prime_modulus_less_one) return -1;
    
    // TODO
}

int main()
{
    int square = 25;
    int prime_modulus = 37;
    
    int find_modular_square_root = find_modular_square_root(square, prime_modulus);

    return 0;
}
