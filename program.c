// Tonelli-Shanks' Algorithm

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
    
    return greatest_common_divisor;
}

int exponentiate(int base, int index)
{
    if (base == 0) return 0;
    if (index == 0) return 1;
    if (index == 1) return base;
    if (index == 2) return base * base;
    
    int power = 1;
    
    while (index)
    {
        power *= power * exponentiate(base, index & 1);
        index >>= 1;
    }
    
    return power;
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

int find_modular_square_root(int residue, int prime_modulus)
{
    // if (find_greatest_common_divisor(residue, prime_modulus) != 1)
    //     return -1;
    
    int prime_modulus_less_one = prime_modulus - 1;
    
    // Euler's criterion
    if (exponentiate_modularly(residue, prime_modulus_less_one >> 1, prime_modulus) != 1)
        return -1;

    // write prime modulus less one in terms of an odd multiple of a binary power
    
    int odd_multiplier = prime_modulus_less_one;
    int exponent_index = 0;
    
    while (!(odd_multiplier & 1))
    {
        odd_multiplier >>= 1;
        exponent_index++;
    }
    
    int quadratic_non_residue = 2;
    
    while (exponentiate_modularly(quadratic_non_residue, prime_modulus_less_one >> 1, prime_modulus) != prime_modulus_less_one)
        quadratic_non_residue++;
    
    // printf("%d * 2^%d", odd_multiplier, exponent_index);
    
    int M = exponent_index;
    int c = exponentiate_modularly(quadratic_non_residue, odd_multiplier, prime_modulus);
    int t = exponentiate_modularly(residue, odd_multiplier, prime_modulus);
    int R = exponentiate_modularly(residue, (odd_multiplier + 1) >> 1, prime_modulus);
    
    for (;;)
    {
        if (t == 0) return 0;
        if (t == 1) return R;
        
        int i = 1;
        
        while (i < M)
        {
            int index = exponentiate(2, i);
            int residue = exponentiate_modularly(t, index, prime_modulus);
            if (residue == 1) break;
            i++;
        }

        int index = exponentiate(2, M - i - 1);

        int b = exponentiate_modularly(c, index, prime_modulus);
        
        M = i;
        c = (b * b) % prime_modulus;
        t = (t * c) % prime_modulus;
        R = (R * b) % prime_modulus;
    }
}

int main()
{
    int perfect_square = 5;
    int prime_modulus = 41;
    
    int modular_square_root = find_modular_square_root(perfect_square, prime_modulus);
    
    printf("%i", modular_square_root);
    
    return 0;
}
