# Prime-Modulated-Square-Root-Finder

This program finds the roots of prime modulated squares, that is, it solves for r in the congruence r² ≡ n (mod p), where the modulus p is a prime number and where the residue n is a quadratic residue.

For example, given 23 for the modulus p and 9 for the residue n, there are two square roots: 3 and 20, for 3² is congruent to 9 modulated by 23, and 20² is congruent to 400 which is also congruent to 9 modulated by 23.

    r² ≡ n (mod p)
    3² ≡ 9 (mod 23)
    20² ≡ 400 ≡ 9 (mod 23)

Every prime modulated quadratic residue has two distinct roots. If the first root is r² ≡ n (mod p), then the second root is p - r. In the above example, the first root is 3, and the modulus is 23, so the second root must be 20, as 23 - 3 is equal to 20. Euler's criterion states that for every non-zero n modulated by prime p greater than 2, n is a quadratic residue, that is, it is a perfect square having square roots, if and only when the halved p less 1 power of n is congruent to 1 modulated by p:

![congruence](https://github.com/user-attachments/assets/c53e34ef-fa1c-4cd9-8bf4-0a8afdc0c6ff)

For quadratic non-residues, the following congruence holds:

![congruence](https://github.com/user-attachments/assets/c53e34ef-fa1c-4cd9-8bf4-0a8afdc0c6ff)

So we get a residue of 1 for squares, and that of negative 1 for non-squares.

For every group modulated by a prime, the order, or number of elements, thereof is p - 1. Half of the residues of such prime modulated are quadratic residues, and half are not. So there are (p - 1) / 2 quadratic residues and (p - 1) / 2 quadratic non-residues. Given 23 for p, we have (23 - 1) / 2 or 11 quadratic residues, and (23 - 1) / 2 or 11 quadratic non-residues.
