### Ý chính yêu cầu của bài toán:

1. **Đọc và xử lý biểu thức toán học dạng chuỗi**:
   - Biểu thức có thể chứa các số đơn (0-9), biến đơn ký tự (ví dụ: `x`, `y`), các phép toán (`+`, `-`, `*`), và dấu ngoặc `()`.
   
2. **Xử lý các lệnh liên quan đến biến**:
   - **SET v x**: Đặt giá trị của biến `x` bằng `v` hoặc cập nhật nếu biến đã tồn tại.
   - **PRINT**: Đánh giá và in kết quả của biểu thức đã được định nghĩa ban đầu. Nếu có biến chưa được định nghĩa, giá trị của biến đó mặc định là 0.
   - **DONE**: Kết thúc chương trình.

3. **Yêu cầu xử lý biểu thức**:
   - Sử dụng thuật toán Shunting-yard để chuyển đổi biểu thức trung tố (infix) thành biểu thức hậu tố (postfix).
   - Xây dựng cây biểu thức từ biểu thức hậu tố để hỗ trợ việc tính toán.
   - Sử dụng bảng băm (map) để lưu trữ và cập nhật giá trị các biến.

4. **Đánh giá biểu thức**:
   - Sử dụng cây biểu thức để đánh giá kết quả khi gặp lệnh `PRINT`.

Bài toán yêu cầu thiết kế chương trình linh hoạt để xử lý biến, tính toán biểu thức phức tạp và quản lý dữ liệu biến hiệu quả.

### Cách 1
#### 1. Stack (Ngăn xếp):

Dùng để chuyển đổi biểu thức từ dạng trung tố (infix) sang dạng hậu tố (postfix) theo thuật toán Shunting-yard.
Hỗ trợ trong quá trình xây dựng cây biểu thức từ biểu thức hậu tố bằng cách lưu trữ các nút khi gặp toán tử.
#### 2.Tree (Cây biểu thức):

Cấu trúc cây biểu thức giúp biểu diễn và đánh giá biểu thức toán học. Cây giúp xác định thứ tự thực hiện các phép toán và cho phép đánh giá biểu thức một cách tự nhiên theo cấu trúc cây.
Khi cây đã được tạo, việc tính toán giá trị của biểu thức trở nên dễ dàng thông qua duyệt cây (theo thứ tự hậu tự).
#### 3. Hash Table (Bảng băm):

Dùng để lưu trữ và quản lý giá trị của các biến trong biểu thức.
Khi gặp lệnh SET, bảng băm sẽ cập nhật hoặc thêm giá trị cho biến tương ứng.
Khi đánh giá biểu thức, nếu gặp biến, chương trình sẽ tra cứu giá trị biến trong bảng băm.

### Tổng kết
Stack giúp xử lý toán tử/toán hạng và chuyển đổi biểu thức.
Tree giúp đánh giá biểu thức một cách có cấu trúc.
Hash Table giúp lưu trữ và quản lý giá trị các biến.
Sự kết hợp của ba cấu trúc này đảm bảo chương trình xử lý linh hoạt và chính xác các biểu thức phức tạp và các lệnh cập nhật giá trị biến.
