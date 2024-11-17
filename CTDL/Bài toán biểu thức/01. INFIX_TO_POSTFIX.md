Hàm `infix_to_postfix` chuyển đổi một biểu thức từ dạng trung tố (infix) sang dạng hậu tố (postfix) bằng cách sử dụng **thuật toán shunting-yard** của Edsger Dijkstra. Đây là một trong những cách hiệu quả để chuyển đổi biểu thức toán học để dễ dàng đánh giá bằng các cấu trúc dữ liệu như ngăn xếp (stack). Hãy cùng phân tích nguyên tắc hoạt động và thuật toán chi tiết:

### 1. Biểu thức trung tố (Infix) và hậu tố (Postfix)

- **Infix** là biểu thức mà các toán tử nằm giữa các toán hạng. Ví dụ: `A + B * C`.
  
- **Postfix** là biểu thức mà các toán tử nằm sau các toán hạng. Ví dụ: `A B C * +`.

### 2. Nguyên lý hoạt động của thuật toán:

- Dùng một ngăn xếp (stack) để lưu trữ các toán tử và dấu ngoặc.
  
- Lần lượt đọc từng ký tự trong biểu thức infix.
  
- Chuyển đổi dựa vào các quy tắc để xác định thứ tự xuất hiện và ưu tiên của các toán tử.

### 3. Thuật toán hoạt động như sau:

- **Duyệt từng ký tự trong biểu thức:**
- 
  1. **Nếu là toán hạng (chữ số hoặc chữ cái):**
     
     - Thêm trực tiếp vào chuỗi kết quả (postfix).

   3. **Nếu là toán tử (`+`, `-`, `*`, v.v.):**
      
     - Trong khi ngăn xếp không rỗng và toán tử ở đỉnh ngăn xếp có độ ưu tiên lớn hơn hoặc bằng toán tử hiện tại, lấy toán tử đó ra khỏi ngăn xếp và thêm vào chuỗi kết quả.
       
     - Đưa toán tử hiện tại vào ngăn xếp.
  
  3. **Nếu là dấu ngoặc mở `(`:**
     
     - Đưa vào ngăn xếp.

  5. **Nếu là dấu ngoặc đóng `)`:**
     
     - Lấy các toán tử từ ngăn xếp ra và thêm vào chuỗi kết quả cho đến khi gặp dấu ngoặc mở `(`. Bỏ dấu ngoặc mở khỏi ngăn xếp (nhưng không thêm vào chuỗi kết quả).
       
- **Sau khi duyệt hết biểu thức:**
  
  - Lấy tất cả các toán tử còn lại trong ngăn xếp và thêm vào chuỗi kết quả.

### 4. Cách hoạt động trong mã:
Dưới đây là hàm `infix_to_postfix` từ mã của chúng ta và giải thích:

```c
void infix_to_postfix(const char* infix, char* postfix) {

    Stack s;

    init_stack(&s);

    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {

        char c = infix[i];

        if (isalnum(c)) {

            postfix[j++] = c; // Nếu là toán hạng (chữ cái hoặc chữ số), thêm vào chuỗi kết quả

        } else if (c == '(') {

            push(&s, (void*)(long)c); // Đưa dấu ngoặc mở vào ngăn xếp

        } else if (c == ')') {

            // Lấy ra các toán tử từ ngăn xếp cho đến khi gặp dấu ngoặc mở

            while (!is_empty(&s) && (char)(long)peek(&s) != '(') {

                postfix[j++] = (char)(long)pop(&s);

            }

            pop(&s); // Loại bỏ dấu ngoặc mở khỏi ngăn xếp

        } else if (is_operator(c)) {

            // Xử lý độ ưu tiên của toán tử

            while (!is_empty(&s) && precedence((char)(long)peek(&s)) >= precedence(c)) {

                postfix[j++] = (char)(long)pop(&s);

            }

            push(&s, (void*)(long)c); // Đưa toán tử hiện tại vào ngăn xếp

        }

    }

    // Lấy tất cả các toán tử còn lại trong ngăn xếp

    while (!is_empty(&s)) {

        postfix[j++] = (char)(long)pop(&s);

    }

    postfix[j] = '\0'; // Kết thúc chuỗi hậu tố

}
```

### 5. Giải thích mã:

- **Duyệt qua từng ký tự `infix[i]`:**
  
  - **Nếu là toán hạng (`isalnum(c)`)**: Thêm trực tiếp vào chuỗi `postfix`.
    
  - **Nếu là dấu ngoặc `(`**: Đưa vào ngăn xếp.
    
  - **Nếu là dấu ngoặc `)`**: Lấy các phần tử từ ngăn xếp ra cho đến khi gặp dấu `(` và thêm vào chuỗi `postfix`.
    
  - **Nếu là toán tử (`+`, `-`, `*`, ...)**: Lấy các toán tử từ ngăn xếp có độ ưu tiên lớn hơn hoặc bằng toán tử hiện tại và thêm vào chuỗi `postfix`. Sau đó, đưa toán tử hiện tại vào ngăn xếp.
    
- **Sau khi kết thúc vòng lặp**: Lấy tất cả các toán tử còn lại trong ngăn xếp và thêm vào `postfix`.

### 6. Ví dụ minh họa:

- **Input**: `(A+B)*C`
  
  - Duyệt `(`: Đưa vào ngăn xếp.
    
  - Duyệt `A`: Thêm vào `postfix` → `postfix = "A"`.
    
  - Duyệt `+`: Đưa vào ngăn xếp.
    
  - Duyệt `B`: Thêm vào `postfix` → `postfix = "AB"`.
    
  - Duyệt `)`: Lấy các toán tử ra khỏi ngăn xếp đến khi gặp `(` → `postfix = "AB+"`.
    
  - Duyệt `*`: Đưa vào ngăn xếp.
    
  - Duyệt `C`: Thêm vào `postfix` → `postfix = "AB+C"`.

### 7. `(char)(long)peek(&s)` 

Là một cách chuyển đổi dữ liệu trong trường hợp con trỏ `void*` trong C. Đây là một kỹ thuật để lấy dữ liệu từ ngăn xếp khi bạn lưu trữ các giá trị kiểu `void*`.

### Giải thích chuyển đổi:

- `void*` là một con trỏ có thể trỏ đến bất kỳ loại dữ liệu nào. Trong trường hợp này, khi sử dụng ngăn xếp với kiểu dữ liệu `void*`, mọi dữ liệu được lưu trữ sẽ được "đóng gói" thành `void*` trước khi lưu trữ.
  
- Khi lưu trữ một ký tự (`char`), bạn phải chuyển đổi nó thành kiểu con trỏ `void*`. Một cách để làm điều này là thông qua việc ép kiểu và sử dụng một "trung gian" là `long` để tránh lỗi mất dữ liệu.
  
  - Ví dụ: `(void*)(long)c` trong quá trình push.

Khi bạn muốn lấy dữ liệu từ ngăn xếp và chuyển nó về kiểu dữ liệu ban đầu, bạn phải làm điều ngược lại, tức là:

1. Chuyển đổi giá trị từ `void*` sang `long`.
  
2. Chuyển đổi tiếp từ `long` sang `char`.

### Tại sao sử dụng `(long)` làm trung gian:

- Sử dụng `long` làm trung gian là để đảm bảo kích thước dữ liệu đủ lớn cho việc chuyển đổi giữa `void*` và `char`. Nếu bạn chuyển đổi trực tiếp giữa `void*` và `char`, có thể dẫn đến việc mất dữ liệu hoặc không đảm bảo đúng kích thước dữ liệu, đặc biệt là trên các hệ thống 64-bit.

### Ví dụ minh họa:

Giả sử bạn lưu trữ một ký tự `char c = '+';` vào ngăn xếp:

```c

push(&s, (void*)(long)c);

```

Khi bạn lấy giá trị từ ngăn xếp:

```c

char top_operator = (char)(long)peek(&s);

```

Quá trình này:

1. Chuyển `void*` thành `long`.
   
2. Chuyển `long` thành `char`.

### Tóm lại:

- `peek(&s)` trả về `void*`.
  
- `(long)peek(&s)` chuyển đổi từ `void*` sang `long`.
  
- `(char)(long)peek(&s)` chuyển đổi tiếp từ `long` sang `char`, giúp bạn lấy lại giá trị ban đầu mà không mất dữ liệu.

Cách tiếp cận này đảm bảo rằng dữ liệu được lưu trữ và trích xuất an toàn từ ngăn xếp khi bạn làm việc với `void*`.
    
  - Lấy các toán tử còn lại trong ngăn xếp → `postfix = "AB+C*"`.
    

**Kết quả**: `AB+C*`.
