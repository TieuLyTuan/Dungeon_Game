# Dungeon_Game
 # ⚔️ Knight Game - Bài Tập Lớn Môn Lập Trình Trên Nền Tảng

Nguyễn Đức Mạnh - 24020218;

## 🎮 Giới thiệu trò chơi

**Knight Game** là một game hành động 2D nơi bạn điều khiển một hiệp sĩ đối đầu với kẻ thù, né tránh và chiến đấu để sống càng lâu càng tốt.  
Trò chơi không có màn chơi cụ thể – **mục tiêu là đạt được điểm số cao nhất có thể trước khi bạn bị hạ gục**.

Game được lập trình bằng **C++** sử dụng thư viện **SDL2**, và chạy trên **Code::Blocks**.

---

## 🧠 Tính năng nổi bật
- Gameplay liên tục: **chơi đến khi chết**
- Hệ thống **Best Score**: lưu lại điểm cao nhất
- Điều khiển mượt mà: di chuyển, chạy, nhảy, tấn công, phòng thủ
- Giao diện đơn giản, dễ mở rộng và nâng cấp

---

## 🎮 Điều khiển

| Phím | Chức năng        |
|------|------------------|
| `A`  | Di chuyển trái   |
| `D`  | Di chuyển phải   |
| `Space` | Nhảy         |
| `Shift` | Chạy nhanh    |
| `J`  | Đòn đánh 1       |
| `K`  | Đòn đánh 2       |
| `L`  | Đòn đánh 3       |
| `S`  | Phòng thủ        |

---

## ⚙️ Hướng dẫn cài đặt & chạy game

### 1. Cài đặt SDL2 (nếu chưa có)
> Tải tại: https://www.libsdl.org/download-2.0.php  
> Làm theo hướng dẫn cấu hình cho Code::Blocks tại:  
> [LazyFoo - SDL2 + CodeBlocks](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/codeblocks/index.php)

### 2. Mở game bằng Code::Blocks
- Mở file `KnightGameFinal.cbp`
- Nhấn `F9` để Build & Run

---


```bash
KnightGameFinal/
├── assets/              # Hình ảnh, âm thanh
├── src/                 # Mã nguồn chính
├── include/             # Header files
├── KnightGameFinal.cbp  # File project Code::Blocks
├── README.md
└── .gitignore

