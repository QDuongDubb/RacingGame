# MAD RACER - DƯƠNG K66 CA-CLC2

Demo game và cấu trúc của code:

# Giới thiệu game

Mad Racer là một trò chơi đua xe vượt chướng ngại vật do mình tự phát triển. Trong trò chơi này, bạn điều khiển một quái xế trên đường đua. Nhiệm vụ của bạn là tránh va chạm với các xe đua khác, ăn những vật phẩm tăng điểm và sống sớt càng lâu càng tốt !

## 0. Cách tải game
   - **Cách 1:** Không bao gồm code.
   - **Cách 2:** Bao gồm code và có thể biên dịch.

## 1. Cơ chế Game
   
   Đây là màn hình chính lúc bắt đầu bật game: Chọn Enter để vào màn chơi chính
   ![START](https://github.com/user-attachments/assets/0a9ad573-19dc-4d4a-92bd-48b8a315c0c5)

   Đây là màn hình khi bắt đầu màn chơi. Tại màn hình này bạn có thể di chuyển xe để vượt các xe đi ngược chiều mình, khi bạn né xe đối phương thành công bạn sẽ được cộng một điểm. Ngoài ra bạn còn có thể ăn vật phẩm POWERUP để được cộng thêm 10 điểm
   ![Screenshot 2024-08-18 170115](https://github.com/user-attachments/assets/f96c72fa-7288-4b76-8008-264fa0c3ac63)

   Trò chơi sẽ kéo dài liên tục cho đến khi người chơi va chạm với xe đối diện. Nếu va chạm, người chơi sẽ bị trừ đi một mạng. Mất ba mạng và trò chơi sẽ kết thúc.

   -Màn hình hiện ra khi người chơi va chạm với xe đối phương và bị trừ đi một mạng:
   ![Screenshot 2024-08-18 170921](https://github.com/user-attachments/assets/0976cf07-69d7-4b20-b02a-df52071bd7f1)

   -Màn hình hiện ra khi người chơi va chạm với xe khác ba lần:
   ![image](https://github.com/user-attachments/assets/26780c7c-4ba2-41e5-ba4e-a36eb6a76831)

   Khi màn hình này hiện ra tức là bạn đã thua cuộc mất rồi ! Bấm phím Enter sẽ đưa bạn trở lại màn hình chính khi mới mở trò chơi. Lúc này bạn có thể bấm phím Enter để bắt đầu lại.


## 2. Các thành phần trong game:
   ### Cơ chế tính điểm:
   ![image](https://github.com/user-attachments/assets/b3c51f14-e803-4703-89ca-95964f430ffd)
   - Điểm của người chơi được tính bằng cách với mỗi xe đối phương đi qua người chơi mà không va chạm, khi xe đối phương đó thoát khỏi màn hình người chơi sẽ được cộng 1 điểm.
   - Ngoài ra, trong quá trình chơi người chơi có thể cố tính va chạm với PowerUp để cộng thêm điểm. Cụ thể va chạm với PowerUp 10 sẽ cộng thêm cho người chơi 10 điểm vào điểm sẵn có.
     
   PowerUp 10 điểm: ![image](https://github.com/user-attachments/assets/abad1127-aa48-43d7-894a-3ed5c6a9a267)

   ### Cơ chế tính mạng:
   ![image](https://github.com/user-attachments/assets/8c705260-57ac-42d9-af69-1d5f52d40003)
   - Mỗi khi bắt đầu màn chơi, người chơi sẽ có ba mạng được cho. Với mỗi lần va chạm với xe đối phương, người chơi sẽ mất một mạng. Khi số mạng này tiến về 0, trò chơi sẽ kết thúc.


   


## 4. Giải thích các phím trong Game:
  
### Các Trạng Thái Của Trò Chơi

1. **BẮT ĐẦU**: Trò chơi bắt đầu ở trạng thái này. Người chơi có thể nhấn `ENTER` để bắt đầu trò chơi.

2. **CHẠY**: Ở trạng thái này, trò chơi đang hoạt động. Người chơi có thể điều khiển xe, tăng tốc, và giảm tốc. Nhấn `ESC` sẽ thoát trò chơi, nhấn `ENTER` sẽ tạm dừng trò chơi, và nhấn `SPACE` sẽ kích hoạt tăng tốc.

3. **TẠM DỪNG**: Trò chơi vào trạng thái này khi người chơi tạm dừng trò chơi trong lúc đang chơi bằng cách nhấn `ENTER`. Nhấn `ENTER` lần nữa sẽ tiếp tục trò chơi.

4. **PHẠM LỖI**: Trạng thái này được kích hoạt bởi các điều kiện trong trò chơi (không được chi tiết trong đoạn mã này). Nhấn `SPACE` sẽ đưa trò chơi về trạng thái CHẠY.

5. **KẾT THÚC**: Khi trò chơi kết thúc, nó sẽ vào trạng thái này. Người chơi có thể khởi động lại trò chơi bằng cách nhấn `ENTER`, điều này sẽ đặt lại điểm số về 0 và đưa trò chơi về trạng thái BẮT ĐẦU.

### Điều Khiển Của Người Chơi

- **Phím Mũi Tên**: 
  - `UP`: Di chuyển xe của người chơi lên trên, với giới hạn ở đỉnh màn hình.
  - `DOWN`: Di chuyển xe của người chơi xuống dưới, với giới hạn ở đáy màn hình.
  - `LEFT`: Di chuyển xe của người chơi sang trái, với giới hạn ở cạnh trái màn hình.
  - `RIGHT`: Di chuyển xe của người chơi sang phải, với giới hạn ở cạnh phải màn hình.

- **Phím Cách (`SPACE`)**: 
  - Ở trạng thái CHẠY, nhấn `SPACE` sẽ tăng tốc xe. Tốc độ của xe tăng thêm 0.55 đơn vị, tối đa đến giá trị tốc độ tối đa đã định (`MaxSpeed`).
  - Ở trạng thái PHẠM LỖI, nhấn `SPACE` sẽ tiếp tục trò chơi.

- **Phím `b`**: 
  - Nhấn `b` khi ở trạng thái CHẠY sẽ làm xe giảm tốc độ thêm 0.55 đơn vị. Tốc độ sẽ giảm miễn là còn trên 0.00 đơn vị.

- **Phím Enter (`ENTER`)**: 
  - Bắt đầu trò chơi từ trạng thái BẮT ĐẦU.
  - Tạm dừng trò chơi từ trạng thái CHẠY hoặc tiếp tục trò chơi từ trạng thái TẠM DỪNG.
  - Khởi động lại trò chơi từ trạng thái KẾT THÚC.

- **Phím Escape (`ESC`)**: 
  - Thoát trò chơi ngay lập tức từ bất kỳ trạng thái nào.

### Cơ Chế Tốc Độ Trò Chơi

- Tốc độ của trò chơi được quản lý bởi biến `gameSpeed`, bị ảnh hưởng bởi hành động của người chơi:
  - Tăng tốc bằng phím `SPACE` sẽ làm tăng tốc độ, trong khi giảm tốc bằng phím `b` sẽ làm giảm tốc độ.
  - Tốc độ có một giá trị tối đa được định trước (`MaxSpeed`).

### Vị Trí Của Người Chơi

- Vị trí của xe người chơi được cập nhật dựa trên các phím mũi tên. Xe có thể di chuyển trong các giới hạn trên màn hình theo cả chiều ngang và chiều dọc, đảm bảo nó luôn nằm trong khu vực hiển thị của màn hình trò chơi.


## Cấu trúc mã nguồn
### Tài nguyên Game:
- **build/res** : Chứa tài nguyên ảnh dành cho Game.
- **build/audio**: Chứa tài nguyên âm thanh dành cho Game.
- **build/fonts** : Chứa tài nguyên phông chữ dành cho Game.
### Code của Game:
- **src/AudioManage**:AudioManager là một lớp được thiết kế để quản lý âm thanh trong trò chơi, sử dụng thư viện SDL_mixer. Lớp này chịu trách nhiệm khởi tạo hệ thống âm thanh, tải các hiệu ứng âm thanh và nhạc nền từ tệp, phát âm thanh trong trò chơi, cũng như dọn dẹp tài nguyên khi không còn cần thiết.
- **src/EventManager**: Đoạn mã này là phần triển khai của lớp EventManager, chịu trách nhiệm quản lý và xử lý các sự kiện trong trò chơi, chẳng hạn như các sự kiện bàn phím và sự kiện thoát chương trình. Lớp này giúp duy trì sự tương tác giữa người chơi và trò chơi, đảm bảo rằng các hành động của người chơi được phản ánh một cách chính xác trong trò chơi.
- **src/main**: Đoạn mã này là phần chính của trò chơi đua xe được triển khai bằng SDL, SDL_image, SDL_mixer, và SDL_ttf. Đây là chương trình chính của trò chơi, xử lý toàn bộ vòng lặp trò chơi, bao gồm khởi tạo, tải tài nguyên, xử lý sự kiện, cập nhật trạng thái trò chơi và hiển thị các đối tượng trên màn hình.
- **src/player**: Lớp Player này cung cấp các phương thức để quản lý các thông tin quan trọng của người chơi như điểm số, mạng sống, vị trí, kết cấu và trạng thái của xe. Điều này cho phép các phần khác của trò chơi dễ dàng tương tác với các thuộc tính của người chơi và điều chỉnh chúng khi cần thiết trong quá trình chơi.
- **src/RenderWindow**: Lớp RenderWindow cung cấp các phương tiện cần thiết để quản lý cửa sổ và quá trình vẽ đồ họa trong một trò chơi SDL. Nó cho phép tải và hiển thị hình ảnh, quản lý cửa sổ và bộ hiển thị, và đảm bảo rằng tất cả các tài nguyên được giải phóng đúng cách khi trò chơi kết thúc.


## 6. Về đồ họa của Game
   - Các loại xe được lấy từ nhà sáng tạo ChiffaProdaction ([@ChiffaProdaction](https://twitter.com/ChiffaProdaction)). Được cho phép tải xuống miễn phí bởi nhà sáng tạo trên trang [https://chiffaprodaction.itch.io/pixel-cars](https://chiffaprodaction.itch.io/pixel-cars)
     
     ![wFwxsL](https://github.com/user-attachments/assets/faa1c64d-8efd-4412-805c-e7faa807722e)

   - Điểm PowerUp là ảnh "Stock Photos" được lấy miễn phí trên trang [https://www.shutterstock.com](https://www.shutterstock.com)
     
     ![image](https://github.com/user-attachments/assets/abad1127-aa48-43d7-894a-3ed5c6a9a267)

   - Ảnh cây là ảnh "Stock Photos" được lấy miễn phí trên trang [https://www.pngitem.com](https://www.pngitem.com)
     
     ![tree](https://github.com/user-attachments/assets/1996aaa0-3a98-4d83-b60e-c4f979fc51b6)
   - Ảnh đá là ảnh "Stock Photos" được lấy miễn phí trên trang [https://www.pngkit.com](https://www.pngkit.com/)

     ![rock](https://github.com/user-attachments/assets/e4c59bb0-def3-4500-a097-78fcf6df0b48)

   - Ảnh background được tạo thủ công trên phần mềm Paint
      ![background](https://github.com/user-attachments/assets/61a1736e-e2de-4ae6-8513-125985a6e934)

## 7. Về source code Game
   - Thông tin về mã nguồn, cách truy cập và sử dụng.
     
