# Save The World
## Giới thiệu bản thân:
- Họ và tên: Nguyễn Đức Huy
- Mã Sinh Viên: 24020162
- Lớp: IT9 - K69
- Mã học phần: INT2215-3
## Giới thiệu game
**Save The World** là 1 game thuộc thể loại hành động. Game sẽ cho người chơi điều khiển 1 chiếc máy bay chiến đấu để bắn hạ kẻ địch xuất hiện trên màn hình. Dòng game đòi hỏi có lối chơi nhanh, phản xạ tốt. Nếu người chơi chạm vào kẻ địch thì sẽ bị mất 1 sinh mạng. Nếu hết sinh mạng thì game sẽ kết thúc. Nếu bắn hết kẻ địch thì người chơi sẽ chiến thắng. Trong game còn có các chức năng tăng sinh mạng và nâng cấp đạn cho máy bay người chơi.  
### 1. Bắt đầu game
Ở màn hình Menu có 3 nút **"PLAY"**, **"GUIDE"**, **"QUIT"**
- Khi nhấn vào nút **"PLAY"** game sẽ bắt đầu
- Khi nhấn vào nút **"GUIDE"** sẽ hiện ra hướng dẫn chơi game cho người chơi
- Khi nhấn vào nút **"QUIT"** sẽ thoát chương trình game
![image](./readme/menu.jpg)
### 2. Các thành phần trong game
- **Plane (Người chơi):** ![image](./readme/planemain.png) là đối tượng chính của trò chơi
- **Background (Nền phía sau):** ![image](./readme/background_game.jpg)
là hình ảnh nền tạo nên 1 không gian thú vị cho người chơi
- **Máy bay kẻ địch:**  ![image](./readme/dich.png) được coi là chướng ngại vật, kẻ thù của máy bay do người chơi điều khiển
- **Đạn:** ![image](./readme/bulletMain.png) là một chức năng của máy bay chiến đấu dùng để bắn hạ kẻ địch
- **Đạn địch:** ![image](./readme/bulletEnemy.png) là một chức năng của máy bay địch để bắn
- **Sinh mệnh:** ![image](./readme/sinhmenh.png) là một chức năng giúp cho máy bay chiến đấu tăng sinh mệnh, tăng cơ hội sống xót
- **Đạn đôi:** ![image](./readme/dich.png) là một chức năng giúp cho máy bay tăng sức mạnh, bắn ra 2 viên đạn cùng 1 lúc
- **Điểm số:** ![image](./readme/point.png) hiển thị điểm số của người chơi khi bắn trúng kẻ địch. Bắn trúng mỗi kẻ địch sẽ được cộng 5 điểm  
### 3. Cách chơi
Người chơi sẽ sử dụng các phím mũi tên **Phải**, **Trái**, **Lên**, **Xuống** trên bàn phím để di chuyển máy bay chiến đấu. Sử dụng phím **SPACE** trên bàn phím để đạn được bắn ra. Nếu đạn được bắn trúng kẻ địch thì địch sẽ biến mất khỏi màn hình và số điểm của bạn sẽ được cộng thêm 5 điểm. Người chơi phải di chuyển và bắn đạn khéo léo sao cho máy bay người chơi không được chạm vào kẻ địch và tích được nhiều điểm số nhất có thể. Nếu chạm vào sẽ bị trừ 1 sinh mạng, có tối đa 5 sinh mạng, khi sinh mạng về 0 thì người chơi sẽ thua cuộc. Trong quá trình chơi còn có các bài chức năng tăng sinh mạng và nâng cấp đạn cho máy bay để game tăng phần kịch tính. Khi người chơi ăn được bài sinh mạng thì sinh mạng sẽ được tăng lên 1, khi người chơi ăn bài nâng cấp đạn thì máy bay sẽ bắn ra 2 viên đạn cùng 1 lúc. Đến cuối game người chơi vẫn còn sinh mạng thì người chơi sẽ chiến thắng và game kết thúc
## Cấu trúc game
- **CommonFunc:**
    - Chứa các định nghĩa chung như kích thước màn hình, hằng số, các biến toàn cục (window, renderer , event).
    - Khởi tạo SDL, SDL_image, SDL_ttf, SDL_mixer.
    - Chứa hiệu ứng âm thanh như g_sound_bullet, g_sound_explosion, g_sound_click.
- **BaseObject:**
    - Lớp cơ sở cho tất cả các đối tượng đồ họa, chức năng chính load ảnh (loadImg), render ảnh, giải phóng tài nguyên.
    - Có các hàm setter và getter cho đối tượng SDL_Rect (lưu vị trí và kích thước) và SDL_Texture.
    - Làm nền tảng cho các lớp kế thừa như Bullet, MenuItem, RenderTile, PlaneMain,...
- **Bullet:**
    - Kế thừa từ BaseObject, lớp Bullet đại diện cho các viên đạn được bắn ra trong game.
    - Cung cấp các hàm để đặt và lấy ra giá trị vị trí của viên đạn (x_val , y_val)
    - Quản lý trạng thái di chuyển của đạn thông qua biến is_move_
    - Hàm handleMove cập nhật vị trí của đạn và đánh dấu đạn ngừng di chuyển khi ra khỏi màn hình
- **MapGame:**
    - Quản lý dữ liệu bản đồ (tile map) của game
    - Struct infor_tile: lưu thông tin về map bao gồm vị trí bắt đầu hiển thị (x_start, y_start), kích thước (max_x, max_y), ma trận các tile (mỗi tile có một kiểu số nguyên biểu diễn loại) và tên file dữ liệu.
    - Lớp RenderTile: kế thừa từ BaseObject, dùng để render từng tile
    - Lớp SetMap: dùng để load 	dữ liệu map từ file, load hình ảnh cho các tile và render map lên màn hình. Cung cấp các hàm setter, getter cho vị trí của map và kích thước map.
- **PlaneMain:**
    - Đại diện cho máy bay chính của game, kế thừa từ BaseObject sử dụng các hàm cơ sở load ảnh, render
    - PlaneMain có một vector chứa các viên đạn (Bullet) của máy bay, cùng các biến điều kiển tốc độ, thời gian bắn trạng thái bắn liên tục,...
- **Menu:**
    - Quản lý giao diện menu của game.
    - Định nghĩa enum MenuState với các trạng thái như: MENU_STATE_MAIN, MENU_STATE_PLAY, MENU_STATE_GUIDE, MENU_STATE_QUIT.
    - Các hàm thành viên bao gồm: loadMenu (load tài nguyên menu), render (vẽ menu), các hàm xử lý sự kiện cho từng nút, và renderGuide (hiển thị màn hình hướng dẫn).
- **MenuItem:**
    - Định nghĩa lớp MenuItem kế thừa từ BaseObject.
    - Chức năng chính là quản lý hình ảnh nút (Button) trong Menu
    - Cung cấp các hàm như setPosition để đặt vị trí nút trên màn hình, isClick để kiểm tra xem nút có được click không, loadImg và render để load hình và vẽ nút lên màn hình
- **TextObject:**
    - Quản lý và hiển thị văn bản trong game
    - TextObject được dùng để hiển thị điểm số, hướng dẫn và thông báo trong game  

## Đánh giá
### Ưu điểm
- Di chuyển khá mượt mà, các hiệu ứng trong game được xử lý hiệu quả, trong game có các chức năng và phương thức cộng điểm để không gây nhàm chán cho người chơi
### Nhược điểm
- Trò chơi còn khá đơn điệu
- Các chức năng trong game còn khá sơ sài
- Chưa có nhiều map
- Các vị trí của kẻ địch trên map chỉ là vị trí cụ thể được cài đặt sẵn 
### Phát triển
- Load thêm nhiều map để tạo nhiều màn cho trò chơi
- Thêm nhiều chức năng để tạo sự thú vị cho trò chơi
- Tạo thêm BOSS vào cuối game tạo sự kịch tính cho trò chơi
- Nâng cấp các kẻ địch để có thế di chuyển đa hướng thay vì di chuyển thẳng
