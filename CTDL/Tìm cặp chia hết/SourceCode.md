Dưới đây là cách viết lại chương trình C/C++ để tìm số cặp \( A[i] \) và \( A[j] \) (với \( i < j \)) có tổng chia hết cho \( K \). 

### **Bài toán:**

- **Đầu vào:**
  
  - Dòng đầu tiên chứa hai số nguyên \( n \) và \( K \), với \( n \) là số phần tử của mảng, và \( K \) là số chia.
    
  - Dòng thứ hai chứa \( n \) số nguyên, mỗi số cách nhau khoảng trắng.

- **Đầu ra:**
  
  - In ra một số nguyên duy nhất là số cặp thỏa mãn điều kiện.

### **Cách tiếp cận:**
Để tối ưu chương trình, ta có thể sử dụng kỹ thuật tính toán modulo. Ý tưởng là, với mỗi phần tử \( A[i] \), ta sẽ tính giá trị của \( A[i] \% K \), sau đó ta sử dụng một mảng đếm để lưu số lượng các phần tử có cùng phần dư khi chia cho \( K \). Sau đó, dựa vào các phần dư này, ta có thể tìm được các cặp \( A[i] \) và \( A[j] \) sao cho \( (A[i] + A[j]) \% K == 0 \).

Dưới đây là chương trình C++ để giải bài toán:

```cpp
#include <iostream>

#include <vector>

using namespace std;

int countDivisiblePairs(int n, int K, const vector<int>& A) {

    vector<int> remainderCount(K, 0);

    int count = 0;

    // Đếm số phần tử theo phần dư khi chia cho K

    for (int i = 0; i < n; i++) {

        int remainder = (A[i] % K + K) % K; // Đảm bảo phần dư luôn không âm

        remainderCount[remainder]++;
    }

    // Tính số cặp thỏa mãn điều kiện

    count += (remainderCount[0] * (remainderCount[0] - 1)) / 2; // Các cặp có phần dư = 0

    for (int i = 1; i <= K / 2; i++) {

        if (i == K - i) { // Trường hợp phần dư ở giữa (ví dụ K = 6, i = 3)

            count += (remainderCount[i] * (remainderCount[i] - 1)) / 2;

        } else {

            count += remainderCount[i] * remainderCount[K - i];
        }
    }

    return count;
}

int main() {

    int n, K;

    cin >> n >> K;

    vector<int> A(n);

    for (int i = 0; i < n; i++) {

        cin >> A[i];
    }

    cout << countDivisiblePairs(n, K, A) << endl;

    return 0;
}
```

### **Giải thích chương trình:**

1. **Phần dư**:
   
   - Sử dụng một mảng `remainderCount` để đếm số lượng phần tử trong mảng `A` có cùng phần dư khi chia cho `K`.

2. **Tính số cặp thỏa mãn điều kiện**:
   
   - Các cặp có tổng chia hết cho `K` sẽ thỏa mãn điều kiện: `(A[i] + A[j]) % K == 0`.
     
   - Điều này tương đương với `remainder[i] + remainder[j] == K` hoặc cả hai phần tử có phần dư là `0`.

3. **Công thức tính số cặp**:
   
   - Số cặp của các phần tử có phần dư `0`: `(n * (n - 1)) / 2`.
     
   - Số cặp giữa các phần dư `i` và `K-i`: `count[i] * count[K - i]`.

4. **Tối ưu hóa**:
   
   - Vì `n` có thể lên tới \(10^5\), thuật toán này có độ phức tạp \(O(n + K)\), đủ nhanh để xử lý dữ liệu lớn.

### **Ví dụ chạy thử**:

#### **Input**:
```
5 3
1 2 3 4 5
```
#### **Output**:
```
4
```

#### **Giải thích**:
Các cặp thỏa mãn:
- (1, 2): \(1 + 2 = 3\), chia hết cho \(3\).
- (1, 5): \(1 + 5 = 6\), chia hết cho \(3\).
- (2, 4): \(2 + 4 = 6\), chia hết cho \(3\).
- (3, 3): \(3 + 3 = 6\), chia hết cho \(3\).
