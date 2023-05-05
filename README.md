
SDL2-PacCatGame-UET

1. Hướng dẫn cài đặt
Để khởi động trò chơi, click main.exe.


2. Mô tả chung

Giới thiệu
Tetris hay Xếp Hình (1984), trò chơi có 7 loại Khối Hình (Tetromino) I (thẳng đứng), J, L, O (vuông), S, T, Z ứng với 7 màu khác nhau.

Về Game Mechanics
Cấu tạo: Mỗi Khối Hình được cấu tạo từ 4 khối gạch vuông (Block). Các Khối Hình có thể xoay được các góc 90, 180, 270 độ.
Mục tiêu: Di chuyển các khối gạch đang rơi từ từ xuống trong kích thước hình chữ nhật 20 hàng x 10 cột (trên màn hình).
Chỗ nào có gạch rồi thì không di chuyển được tới vị trí đó.
Người chơi xếp những khối hình sao cho khối hình lấp đầy 1 hàng ngang để ghi điểm và hàng ngang ấy sẽ biến mất và người chơi sẽ ghi điểm.
Người chơi thua cuộc khi Khối Hình tràn ra trên 2 dòng khỏi Grid (Lưới).
3. Các chức năng
Để thoát game, nhấn ESC.

1. Chức năng Play Single
Chức năng cơ bản nhất của game. Chơi như trên mô tả, cách chơi cụ thể ở hình minh họa dưới mục "Chức năng Help" ^^.
image

Hold : Ấn để giữ lại khối hình hiện tại, khối hình hiện tại được thay thế bằng khối hình tiếp theo.
Bảng thông số: Lần lượt là Line (lưu trữ số dòng đã hoàn thành), Score (điểm hiện tại), Level (đại lượng tượng trưng cho speed).
Next Tetrads: Thông tin về các khối hình sinh kế tiếp.
Khi người chơi thua sẽ xuất hiện 1 bảng tổng sắp cho biết điểm số của người chơi và các kỷ lục trước
imageNgười chơi có thể bấm nút Replay để chơi lại hoặc Return để quay lại màn hình chính.

2. Chức năng Battle
Cũng là chơi nhưng mà chơi hai người. Mỗi bên điều khiển một phía của bàn phím.
image

Khi một trong hai người chơi thua cuộc, người còn lại sẽ chiến thắng.
Nếu cả hai đều thua cuộc sẽ dựa trên điểm số quyết định người chiến thắng.

image

3. Chức năng Setting
Cho phép thiết lập các thông số của trò chơi bằng chuột, bao gồm:

bật tắt Ghost Tetromino
image
bật tắt Sound Efects
điều chỉnh Music Volume
thiết lập Level.
Ngoài ra còn reset Ranking Score và reset Settings.
image

4. Chức năng Help
Chứa thông tin cụ thể về trò chơi:

Cách chơi (Helps)
Thông tin chi tiết (About)
Bản quyền (copyright)
5. Một số chức năng khác
Đang chơi có thể bấm P để dừng hoặc chơi tiếp.
Độ khó trò chơi dựa vào điểm người chơi (hoặc thiết lập độ khó trong Settings).
Dữ liệu Ranking Score và User Settings được lưu trữ tại file Binary trong thư mục "settings"
4. Kỹ thuật lập trình
Xây dựng trên nền tảng C++ và SDL2 bao gồm:
SDL_Mixer: Hỗ trợ xử lý âm thanh.
SDL_Ttf: Hỗ trợ xử lý fonts chữ.
Các thư viện mở rộng C++.
IDE Visual Code.
Các kỹ thuật lập trình
Gồm tất cả các kỹ thuật cơ bản:
Biến (static, extern), vòng lặp, cấu trúc rẽ nhánh, mảng, chuỗi.
Con trỏ, set, map, vector
Class: Tạo, hủy, member function.
Đọc viết file binary.
Multithreading: Xử lý chức năng Battle.
Tách file giấu code.
Kỹ thuật duyệt mảng, sinh số ngẫu nhiên.
Kỹ năng refac code.
Các kỹ thuật, syntax của SDL.
Kỹ thuật giải phóng bộ nhớ động.
Ứng dụng
Thuật toán sinh Khối Hình ngẫu nhiên giảm tỷ lệ sinh 2 khối giống nhau liên tiếp.

Mỗi chức năng của game (Play Single, Battle, Setting, Helps), mỗi Khối hình (Tetrads) được xác định bằng 1 đối tượng (class) riêng biệt.

Ứng dụng đa nhiệm xử lý Battle khi có 2 người chơi cùng thao tác trên một bàn phím cùng 1 lúc.

5. Các hướng đi trong tương lai
Kết nối hóa trò chơi: Royal Battle: Nâng cấp chức năng Battle trở thành Royal Battle:
Sử dụng kết nối mạng máy tính (LAN, Router,... ) kết nối người chơi với nhau.
Sẽ thiết lập một trường cơ sở dữ liệu (database) lưu trữ trên máy chủ (server) lưu trữ thông tin người chơi.
Một Đấu Trường bao gồm khoảng 10-50-100 người chơi.
Khi một người chơi bất kỳ ăn hàng, hàng đó sẽ không biến mất mà trở thành Garbage Tetrads xuất hiện tại màn hình của người chơi khác bất kỳ (random).
Người chơi cuối cùng nằm xuống là người chiến thắng.
Xã hội hóa: Ứng dụng trí tuệ nhân tạo viết bot Deep Green chơi với người tự kỷ, người cô đơn,...
Thêm chức năng chơi với máy (Play With Deep Green).
Công việc của Deep Green:
  - Nhận diện grid, nhận diện Khối Hình hiện tại và các khối tiếp theo
  - Xử lý dữ liệu bằng thuật toán.
  - Đưa ra vị trí và góc quay tối ưu nhất để bạn không bao giờ thắng được máy =))).
Tư bản hóa trò chơi: Hệ thống nạp tiền Pay to Play:
Người chơi sẽ nạp tiền vào game, số tiền sẽ chuyển vào tài khoản nhà phát hành.
Tiền nạp sẽ chuyển hóa thành Coin với tỷ lệ tương ứng.
Có thể dùng Coin để đổi các vật phẩm sau:
  - Skin cho Khối Hình theo cơ chế gacha (quay ngẫu nhiên từ một tập có sẵn)
  - Theme UI game mới
  - Theme Music game mới
  - Tốn Coin để giảm độ khôn của Deep Green, giúp chiến thắng bot một cách dễ dàng, giảm đi áp lực cuộc sống.

.
