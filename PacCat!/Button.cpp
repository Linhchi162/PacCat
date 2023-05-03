#include"Button.h"

Button::Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
    : m_renderer(renderer)
    , m_texture(texture)
    , m_rect(rect)
{
}

Button::~Button()
{
    SDL_DestroyTexture(m_texture);
}

void Button::Render()
{
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
}

bool Button::IsClicked()
{
    // Lấy input từ người chơi
    int x, y;
    Uint32 mouseState = SDL_GetMouseState(&x, &y);

    // Kiểm tra xem vị trí của chuột có nằm trong vùng của button không
    if (x >= m_rect.x && x < m_rect.x + m_rect.w
        && y >= m_rect.y && y < m_rect.y + m_rect.h
        && mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        return true;
    }

    return false;
}
void Button::SetTexture(SDL_Texture* texture) {
    m_texture = texture;
}