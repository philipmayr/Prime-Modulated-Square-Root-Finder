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
    if (find_greatest_common_divisor(modulus, base) != 1)
        return -1;
    
    for (int order = 3; order < modulus; order++)
        if (exponentiate_modularly(base, order, modulus) == 1)
            return order;
}

int find_modular_square_root(int perfect_square, int prime_modulus)
{
    if (find_greatest_common_divisor(perfect_square, prime_modulus) != 1)
        return -1;
    
    int prime_modulus_less_one = prime_modulus - 1;
    
    if (exponentiate_modularly(perfect_square, prime_modulus_less_one >> 1, prime_modulus) == prime_modulus_less_one)
        return -1;

    // write prime modulus less one in terms of an odd multiple of a binary power
    
    // TODO
}

int main()
{
    int perfect_square = 25;
    int prime_modulus = 37;
    
    int find_modular_square_root = find_modular_square_root(perfect_square, prime_modulus);
    
    return 0;
}
