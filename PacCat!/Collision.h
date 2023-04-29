#pragma once
#include<SDL.h>

	inline bool CollisionWith(const SDL_Rect& object, const SDL_Rect& r1, const SDL_Rect& r2)
    {
        if (SDL_HasIntersection(&r1, &object) || SDL_HasIntersection(&r2, &object))
        {
            return true;
        }

        return false;
    }
//Lý do là khi dùng inline, trình biên dịch sẽ không tạo 
//ra một địa chỉ riêng cho hàm này trong bộ nhớ, mà sẽ thay thế t
//rực tiếp mã máy của hàm này vào nơi gọi hàm. Do đó, không có sự trùng
//lặp về định nghĩa của hàm này trong các file khác nhau.