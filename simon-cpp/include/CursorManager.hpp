#pragma once
#include <SFML/Window.hpp>

class CursorManager {
public:
    enum class Type { Arrow, Hand };

    CursorManager() = default;

    void attach(sf::Window& win) {
        window = &win;
        arrow.loadFromSystem(sf::Cursor::Arrow);
        hand.loadFromSystem(sf::Cursor::Hand);
        current = Type::Arrow;
        if (window) window->setMouseCursor(arrow);
    }

    void setArrow() {
        if (window)
            window->setMouseCursor(arrow);
    }

    void setHand() {
        if (window)
            window->setMouseCursor(hand);
    }

private:
    sf::Cursor arrow;
    sf::Cursor hand;
    sf::WindowBase* window = nullptr;
    Type current = Type::Arrow;

    void setIfChanged(Type t) {
        if (current == t || !window) return;
        current = t;
        if (t == Type::Arrow) window->setMouseCursor(arrow);
        else window->setMouseCursor(hand);
    }
};