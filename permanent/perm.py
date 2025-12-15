import numpy as np
import numba as nm
from thewalrus import perm as perm_walrus

def haar_gen(n: int) -> np.ndarray:
    X = np.random.normal(size=(n, n)) + 1j * np.random.normal(size=(n, n))
    Q, R = np.linalg.qr(X)
    D = np.diag(R)
    L = np.diag(D / np.abs(D))
    return Q @ L

@nm.jit
def permanent(A: np.ndarray) -> float:
    n = A.shape[0]

    if n == 2:
        return A[0,0]*A[1,1] + A[0,1]*A[1,0]
    elif n == 3:
        return (A[0,0]*A[1,1]*A[2,2] + A[0,1]*A[1,2]*A[2,0] + A[0,2]*A[1,0]*A[2,1] +
                A[0,2]*A[1,1]*A[2,0] + A[0,0]*A[1,2]*A[2,1] + A[0,1]*A[1,0]*A[2,2])

    else:
        row_sum = np.sum(A, axis=0)

        perm = np.prod(row_sum)
        
        row_signs = np.ones(n, dtype=np.int64)
        
        sign_prod = 1

        limit = 1 << (n - 1)
        for i in range(1, limit):
            k = 0
            temp_i = i
            while (temp_i & 1) == 0:
                k += 1
                temp_i >>= 1
            
            row_idx = k + 1
            curr_sign = row_signs[row_idx]
            
            if curr_sign == 1:
                row_sum -= 2 * A[row_idx]
                row_signs[row_idx] = -1
            else:
                row_sum += 2 * A[row_idx]
                row_signs[row_idx] = 1

            sign_prod *= -1
            
            perm += sign_prod * np.prod(row_sum)
        return perm / limit


if __name__ == '__main__':
    np.random.seed(42)
    n = 2
    A = haar_gen(n)
    A = np.abs(A)**2
    perm_A = permanent(A)
    print(f"Permanent of the matrix:\n{A}\nis {perm_A:.6f}")