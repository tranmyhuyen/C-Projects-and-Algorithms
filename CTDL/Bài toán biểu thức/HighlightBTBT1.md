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
