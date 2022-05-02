//
// Created by Jan Orava on 30.04.2022.
//

#include "Card.h"

Card::Card(const std::vector<std::pair<Color, Color>> & colors, int id) : m_colors(colors), m_id(id) {}

const std::pair<Color, Color> & Card::getSide(Orientation orientation) const {
    int back = m_isFlipped ? 4 : 0;  // Backside colors are behind frontside colors
    return m_colors[((int)m_orientation + (int)orientation) % 4 + back];
}

void Card::rotate() {
    int o = (int)m_orientation;
    o += 1;
    if(o >= 4) {
        o = 0;
        m_isFlipped = !m_isFlipped;
    }
    m_orientation = (Orientation)o;

}

bool Card::isEmpty() const {
    return m_colors.empty();
}

std::ostream & operator<<(std::ostream & out, const Card & card) {
    return out << card.m_id;
}

std::ostream & operator<<(std::ostream & out, const Color & color) {
    switch(color) {
        case Color::RED:
            out << "\u001b[1m\u001b[31mR\u001b[0m";
            break;
        case Color::GREEN:
            out << "\u001b[1m\u001b[32mG\u001b[0m";
            break;
        case Color::BLUE:
            out << "\u001b[1m\u001b[34mB\u001b[0m";
            break;
        case Color::YELLOW:
            out << "\u001b[1m\u001b[33mY\u001b[0m";
            break;
    }
    return out;
}
