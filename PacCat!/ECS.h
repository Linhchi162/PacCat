#pragma once
# include <iostream>
# include <vector>
#include <memory>
#include <algorithm>
#include<bitset>
#include<array>
//??nh ngh?a các thành ph?n c?a m?t ??i t??ng trong game
class Component;
//?? ??nh ngh?a m?t ??i t??ng trong game
class Entity;

using ComponentID = std::size_t;
inline ComponentID getComponentTypeID()//l?y ID c?a t?ng thành ph?n trong game
{
	static ComponentID lastID = 0;
	return lastID++;
}
template <typename T> inline ComponentID getComponentTypeID() noexcept//l?y ID c?a m?t ki?u d? li?u c? th?.
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;//gi?i h?n s? l??ng thành ph?n t?i ?a trong game


using ComponentBitSet = std::bitset<maxComponents>;//là m?t bitset ?? xác ??nh xem ??i t??ng có ch?a thành ph?n nào hay không.


using ComponentArray = std::array<Component*, maxComponents>;//là m?t m?ng ch?a các con tr? unique_ptr tr? t?i các thành ph?n c?a ??i t??ng


class Component
{
public:
	Entity* entity;

	virtual void init(){}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>>components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:

	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() { return active;  }
	void destroy() { active = false; }


	//ki?m tra xem m?t ??i t??ng có ch?a m?t ki?u d? li?u c? th? hay không.
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward < TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}
	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};

/*using ComponentID = std::size_t; : Định nghĩa một kiểu dữ liệu mới có tên là ComponentID, là một biến số nguyên không dấu có kích thước tùy thuộc vào nền tảng2.
inline ComponentID getComponentTypeID()//l?y ID c?a t?ng thành ph?n trong game : Định nghĩa một hàm nội tuyến trả về một ComponentID duy nhất cho mỗi lần gọi hàm. Hàm này sử dụng một biến tĩnh lastID để lưu trữ ID cuối cùng được trả về và tăng nó lên mỗi khi hàm được gọi2.
template <typename T> inline ComponentID getComponentTypeID() noexcept//l?y ID c?a m?t ki?u d? li?u c? th?. : Định nghĩa một hàm nội tuyến khác nhận một kiểu dữ liệu T bất kỳ làm tham số kiểu và trả về một ComponentID duy nhất cho mỗi kiểu T. Hàm này sử dụng hàm getComponentTypeID() ở trên để lấy ID cho kiểu T và lưu trữ nó trong một biến tĩnh typeID. Hàm này cũng có từ khóa noexcept để chỉ ra rằng nó không ném ra bất kỳ ngoại lệ nào2.
constexpr std::size_t maxComponents = 32;//gi?i h?n s? l??ng thành ph?n t?i ?a trong game : Định nghĩa một hằng số biên dịch có tên là maxComponents, có giá trị là 32. Đây là số lượng thành phần tối đa mà một đối tượng trong game có thể có2.
using ComponentBitSet = std::bitset<maxComponents>;//là m?t bitset ?? xác ??nh xem ??i t??ng có ch?a thành ph?n nào hay không. : Định nghĩa một kiểu dữ liệu mới có tên là ComponentBitSet, là một bitset có kích thước bằng maxComponents. Một bitset là một loại dữ liệu biểu diễn một chuỗi các bit có thể được thiết lập hoặc xóa riêng lẻ. Một ComponentBitSet sẽ được sử dụng để xác định xem một đối tượng có chứa thành phần nào hay không bằng cách thiết lập bit tương ứng với ID của thành phần đó2.*/
/*class Component : Định nghĩa một lớp cơ sở trừu tượng cho các thành phần của đối tượng trong game. Một thành phần là một đối tượng có chứa một số dữ liệu và hành vi liên quan đến một khía cạnh cụ thể của đối tượng, ví dụ như vị trí, hình dạng, chuyển động, va chạm, âm thanh, v.v. Lớp Component có một con trỏ tên là entity để trỏ đến đối tượng mà nó thuộc về. Nó cũng có bốn phương thức ảo là init(), update(), draw() và hàm hủy ảo. Các lớp dẫn xuất từ Component sẽ cài đặt các phương thức này để thực hiện các chức năng cụ thể.
class Entity : Định nghĩa một lớp biểu diễn một đối tượng trong game. Một đối tượng là một đối tượng có thể có nhiều thành phần khác nhau để tạo ra các tính năng và hành vi phong phú. Lớp Entity có một biến bool tên là active để xác định xem đối tượng có hoạt động hay không. Nó cũng có một vector của các con trỏ unique_ptr trỏ đến các thành phần của nó. Một unique_ptr là một loại con trỏ thông minh giúp quản lý bộ nhớ và ngăn chặn rò rỉ bộ nhớ. Ngoài ra, lớp Entity còn có một ComponentArray và một ComponentBitSet để lưu trữ và truy xuất các thành phần của nó một cách hiệu quả.
Lớp Entity cung cấp các phương thức sau:
void update() : Cập nhật và vẽ các thành phần của đối tượng.
void draw() : Không làm gì cả.
bool isActive() : Trả về giá trị của biến active.
void destroy() : Đặt biến active thành false.
template <typename T> bool hasComponent() const : Kiểm tra xem đối tượng có chứa thành phần kiểu T hay không bằng cách kiểm tra bit tương ứng trong componentBitSet.
template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) : Thêm một thành phần kiểu T vào đối tượng bằng cách sử dụng các tham số được chuyển tiếp để khởi tạo nó. Phương thức này sẽ thiết lập con trỏ entity của thành phần mới, thêm nó vào vector components, gán nó vào componentArray theo ID của kiểu T, thiết lập bit trong componentBitSet theo ID của kiểu T và gọi phương thức init() của thành phần mới. Phương thức này sẽ trả về một tham chiếu đến thành phần mới.
template<typename T> T& getComponent() const : Trả về một tham chiếu đến thành phần kiểu T của đối tượng bằng cách lấy con trỏ từ componentArray theo ID của kiểu T và ép kiểu nó về kiểu T.*/
/*class Manager : Định nghĩa một lớp có tên là Manager, có nhiệm vụ quản lý các đối tượng Entity trong game.
private: std::vector<std::unique_ptr<Entity>> entities; : Khai báo một biến thành viên riêng tên là entities, là một vector của các con trỏ unique_ptr trỏ đến các đối tượng Entity. Một vector là một loại dữ liệu biểu diễn một mảng động có thể thay đổi kích thước. Một unique_ptr là một loại con trỏ thông minh giúp quản lý bộ nhớ và ngăn chặn rò rỉ bộ nhớ.
public: void update() : Định nghĩa một phương thức công khai trả về kiểu void, có tên là update. Phương thức này được gọi để cập nhật các đối tượng Entity trong vector entities bằng cách gọi phương thức update() của từng đối tượng.
void draw() : Định nghĩa một phương thức công khai trả về kiểu void, có tên là draw. Phương thức này được gọi để vẽ các đối tượng Entity trong vector entities bằng cách gọi phương thức draw() của từng đối tượng.
void refresh() : Định nghĩa một phương thức công khai trả về kiểu void, có tên là refresh. Phương thức này được gọi để loại bỏ các đối tượng Entity không hoạt động khỏi vector entities bằng cách sử dụng hàm erase() và remove_if() của vector. Hàm erase() xóa các phần tử trong một khoảng xác định của vector. Hàm remove_if() di chuyển các phần tử thoả mãn một điều kiện cho trước về cuối vector và trả về một iterator chỉ đến phần tử đầu tiên của phần bị di chuyển. Điều kiện cho trước được xác định bởi một hàm lambda, là một hàm vô danh được định nghĩa ngay tại chỗ. Hàm lambda này nhận một tham số là một con trỏ unique_ptr trỏ đến một đối tượng Entity và trả về true nếu đối tượng đó không hoạt động (isActive() trả về false).
Entity& addEntity() : Định nghĩa một phương thức công khai trả về một tham chiếu đến kiểu Entity, có tên là addEntity. Phương thức này được gọi để thêm một đối tượng Entity mới vào vector entities bằng cách sử dụng hàm new để cấp phát bộ nhớ cho nó, sau đó gán nó cho một con trỏ unique_ptr và sử dụng hàm emplace_back() của vector để chèn nó vào cuối vector. Hàm emplace_back() là một phiên bản hiệu quả hơn của hàm push_back(), vì nó không cần sao chép hay di chuyển dữ liệu, mà chỉ cần xây dựng dữ liệu ngay tại chỗ. Phương thức này sẽ trả về một tham chiếu đến đối tượng Entity mới được thêm vào.*/