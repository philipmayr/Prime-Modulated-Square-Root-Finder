# Prime-Modulated-Square-Root-Finder

This program finds the roots of prime modulated squares, that is, it solves for r in the congruence r² ≡ n (mod p), where the modulus p is a prime number and where the residue n is a quadratic residue.

For example, given 23 for the modulus p and 9 for the residue n, there are two square roots: 3 and 20, for 3² is equal to 9 modulated by 23, and 20² is equal to 400 which is also equal to 9 modulated by 23.

    r² ≡ n (mod p)
    3² ≡ 9 (mod 23)
    20² ≡ 400 ≡ 9 (mod 23)

Every prime modulated quadratic residue has two distinct roots. If the first root is r² ≡ n (mod p), then the second root is p - r. In the above example, the first root is 3, and the modulus is 23, so the second root must be 20, as 23 - 3 is equal to 20. Euler's criterion states that for every non-zero n modulated by a greater than 2 prime p, n is a quadratic residue, that is, it is a perfect square having square roots, if and only when:

    ![congruence](https://github.com/user-attachments/assets/c53e34ef-fa1c-4cd9-8bf4-0a8afdc0c6ff)
