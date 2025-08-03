// Prime Modulated Square Root Finder

#include <stdio.h>

int count_trailing_zeroes(int number)
{
    int trailing_zero_count = 1;
  
    // 0b1111111111111111, or 2^16 - 1
    if ((number & 0x0000FFFF) == 0)
    {
        trailing_zero_count += 16;
        number >>= 16;
    }
  
    // 0b11111111, or 2^8 - 1
    if ((number & 0x000000FF) == 0)
    {
      trailing_zero_count += 8;
      number >>= 8;
    }
    
    // 0b1111, or 2^4 - 1
    if ((number & 0x0000000F) == 0)
    {
      trailing_zero_count += 4;
      number >>= 4;
    }
    
    // 0b11, or 2^2 - 1
    if ((number & 0x00000003) == 0)
    {
      trailing_zero_count += 2;
      number >>= 2;
    }
  
    return trailing_zero_count - (number & 1);
}

int find_lesser_of_twain(int first_number, int second_number)
{
    return (first_number < second_number) ? first_number : second_number;
}

int get_distance_from_zero(int number)
{
    return (number < 0) ? -number : number;
}

int find_greatest_common_divisor(int first_number, int second_number)
{
    if (first_number == 0) return second_number;
    if (second_number == 0) return first_number;
        
    int trailing_zero_count_of_first_number = count_trailing_zeroes(first_number);
    int trailing_zero_count_of_second_number = count_trailing_zeroes(second_number);
    
    first_number >>= trailing_zero_count_of_first_number;
    second_number >>= trailing_zero_count_of_second_number;
    
    int common_binary_divisor = find_lesser_of_twain(trailing_zero_count_of_first_number, trailing_zero_count_of_second_number);
    
    while (first_number)
    {
        int difference_between_numbers = first_number - second_number;
        
        second_number = find_lesser_of_twain(first_number, second_number);
        first_number = get_distance_from_zero(difference_between_numbers);
        first_number >>= count_trailing_zeroes(first_number);
    }
    
    int greatest_common_divisor = second_number << common_binary_divisor;
    
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

int find_prime_modulated_square_root(int residue, int prime_modulus)
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
    
    int odd_multiplier_exponentiated_quadratic_nonresidue = exponentiate_modularly(quadratic_non_residue, odd_multiplier, prime_modulus);
    int odd_multiplier_exponentiated_quadratic_residue = exponentiate_modularly(residue, odd_multiplier, prime_modulus);
    int odd_multiplier_plus_one_halved_exponentiated_quadratic_residue = exponentiate_modularly(residue, (odd_multiplier + 1) >> 1, prime_modulus);
    
    for (;;)
    {
        if (odd_multiplier_exponentiated_quadratic_residue == 0) return 0;
        if (odd_multiplier_exponentiated_quadratic_residue == 1) return odd_multiplier_plus_one_halved_exponentiated_quadratic_residue;
        
        int i = 1;
        
        while (i < exponent_index)
        {
            int index = exponentiate(2, i);
            int residue = exponentiate_modularly(odd_multiplier_exponentiated_quadratic_residue, index, prime_modulus);
            if (residue == 1) break;
            i++;
        }

        int index = exponentiate(2, exponent_index - i - 1);

        int binary_power_of_odd_multiplier_exponentiated_quadratic_nonresidue = exponentiate_modularly(odd_multiplier_exponentiated_quadratic_nonresidue, index, prime_modulus);
        
        exponent_index = i;
        odd_multiplier_exponentiated_quadratic_nonresidue = (binary_power_of_odd_multiplier_exponentiated_quadratic_nonresidue * binary_power_of_odd_multiplier_exponentiated_quadratic_nonresidue) % prime_modulus;
        odd_multiplier_exponentiated_quadratic_residue = (odd_multiplier_exponentiated_quadratic_residue * odd_multiplier_exponentiated_quadratic_nonresidue) % prime_modulus;
        odd_multiplier_plus_one_halved_exponentiated_quadratic_residue = (odd_multiplier_plus_one_halved_exponentiated_quadratic_residue * binary_power_of_odd_multiplier_exponentiated_quadratic_nonresidue) % prime_modulus;
    }
}

int main()
{
    for (;;)
    {
        printf("Enter a prime modulus: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, buffer;
        
        status = scanf("%d", & input);
        
        while (status != 1)
        {
            while ((buffer = getchar()) != EOF && buffer != '\n');
            
            printf("Invalid input.");
            printf("\n\n");
            printf("Enter a prime modulus: ");
            
            status = scanf("%d", & input);
        }
        
        int prime_modulus = input;
        
        printf("Enter a quadratic residue modulo %i: ", prime_modulus);
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        status = scanf("%d", & input);
        
        while (status != 1)
        {
            while ((buffer = getchar()) != EOF && buffer != '\n');
            
            printf("Invalid input.");
            printf("\n\n");
            printf("Enter a quadratic residue modulo %i: ", prime_modulus);
            
            status = scanf("%d", & input);
        }
        
        int quadratic_residue_candidate = input;
        
        printf("\n");
        
        int modular_square_root_candidate = find_prime_modulated_square_root(quadratic_residue_candidate, prime_modulus);
        
        if (modular_square_root_candidate == -1)
        {
            printf("%i is not a quadratic residue modulo %i.", quadratic_residue_candidate, prime_modulus);
        }
        else
        {
            int first_modular_square_root = modular_square_root_candidate;
            int second_modular_square_root = prime_modulus - first_modular_square_root;
            
            printf("The square roots of %i modulated by %i are %i and %i.", quadratic_residue_candidate, prime_modulus, first_modular_square_root, second_modular_square_root);
        }
        
        printf("\n\n");
    }
    
    return 0;
}
