# 🎓 Student Management System in Pure C

> **Chương trình quản lý hồ sơ sinh viên giao diện dòng lệnh (CLI) bằng ngôn ngữ C, hỗ trợ lưu trữ dữ liệu vào file.**

## ✨ Các chức năng chính (CRUD)
- **Create**: Thêm mới hồ sơ sinh viên (Mã SV, Họ tên, Ngày sinh, Điểm số,...).
- **Read**: Xem danh sách toàn bộ sinh viên, tìm kiếm theo tên hoặc mã sinh viên.
- **Update**: Cập nhật và chỉnh sửa thông tin sinh viên đã có.
- **Delete**: Xoá sinh viên khỏi danh sách.
- **File Persistence**: Tự động đọc và lưu trữ dữ liệu vào file `students.txt` sau mỗi thao tác.

## 🛠️ Cách biên dịch và Chạy
```bash
gcc -std=c99 main.c -o student_manager
./student_manager
```
Hoặc mở trực tiếp file `CRUD_STUDENT.dev` bằng **Dev-C++**.
