#pragma once
#ifndef _COLLISION_HEADER_INCLUDED_
#define _COLLISION_HEADER_INCLUDED_
#include<SDL.h>

	inline bool CollisionWith(const SDL_Rect& object, const SDL_Rect& r1, const SDL_Rect& r2)
    {
        if (SDL_HasIntersection(&r1, &object) || SDL_HasIntersection(&r2, &object))
        {
            return true;
        }

        return false;
    }
    struct Transform
    {
        int xPos;
        int yPos;
        float width;
        float height;
        //int scale;
    };

    struct TextureRenderer // basic SpriteRenderer
    {
        SDL_Texture* defaultTexture;
    };
#endif
//Lý do là khi dùng inline, trình biên dịch sẽ không tạo 
//ra một địa chỉ riêng cho hàm này trong bộ nhớ, mà sẽ thay thế t
//rực tiếp mã máy của hàm này vào nơi gọi hàm. Do đó, không có sự trùng
//lặp về định nghĩa của hàm này trong các file khác nhau.