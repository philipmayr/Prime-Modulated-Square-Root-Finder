# Prime-Modulated-Square-Root-Finder

This program finds the roots of prime modulated squares, that is, it solves for r in the congruence r² ≡ n (mod p), where the modulus p is a prime number and where the residue n is a quadratic residue.

For example, given 23 for the modulus p and 9 for the residue n, there are two square roots: 3 and 20, for 3² is congruent to 9 modulated by 23, and 20² is congruent to 400 which is also congruent to 9 modulated by 23.

    r² ≡ n (mod p)
    3² ≡ 9 (mod 23)
    20² ≡ 400 ≡ 9 (mod 23)

Every prime modulated quadratic residue has two distinct roots. If the first root is r² ≡ n (mod p), then the second root is p - r. In the above example, the first root is 3, and the modulus is 23, so the second root must be 20, as 23 - 3 is equal to 20. Euler's criterion states that for every non-zero n modulated by prime p greater than 2, n is a quadratic residue, that is, it is a perfect square having square roots, if and only when the halved p less 1 power of n is congruent to 1 modulated by p:

![quadratic residue](assets/quadratic_residue.svg)

For quadratic non-residues, the following congruence holds:

![quadratic non-residue](assets/quadratic_nonresidue.svg)

So a residue of 1 comes up for squares and that of negative 1 for non-squares.

For every group modulated by a prime, the order, or number of elements, thereof is p - 1. Half of the residues of such prime modulated are quadratic residues, and half are not. So there are (p - 1) / 2 quadratic residues and (p - 1) / 2 quadratic non-residues. Given 23 for p, we have (23 - 1) / 2 or 11 quadratic residues, and (23 - 1) / 2 or 11 quadratic non-residues.

Descriptions of Helper Functions:

int find_greatest_common_divisor(int a, int b): Finds the greatest common divisor of two numbers using binary bit shifts, comparisons, and subtractions.

int exponentiate(int base, int index): Exponentiates the base to the power of the index by squaring and multiplying.

int exponentiate_modularly(int base, int index, int modulus): Exponentiates the base to the power of the index by squaring and multiplying, modulating by the modulus after each operation.

int find_multiplicative_order(int modulus, int base): Finds the multiplicative order of the base modulated by the modulus. The multiplicative order is the power to which the base must be raised so as to get a modulated residue of 1.
