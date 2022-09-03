//
// Created by Cathy Quan on 12/8/21.
//

#ifndef PROJECT3_NEW_BUTTON_H
#define PROJECT3_NEW_BUTTON_H

class Button {
    sf::Sprite sprite;
    sf::Vector2f position;
public:
    Button() {
        position.x = 0;
        position.y = 0;
    }
    void initialize(sf::Vector2f _position, sf::Sprite sprite) {
        position.x = _position.x;
        position.y = _position.y;
        this->sprite = sprite;
    }
    void setSprite(sf::Sprite _sprite) {
        sprite = _sprite;
    }
    sf::Sprite getSprite() {
        return sprite;
    }
    void Draw(sf::RenderWindow& window) {
        sprite.setPosition(position);
        window.draw(sprite);
    }
    sf::FloatRect GetBounds() {
        return sprite.getGlobalBounds();
    }
};

#endif //PROJECT3_NEW_BUTTON_H
