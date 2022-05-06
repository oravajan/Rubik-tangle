//
// Created by Jan Orava on 30.04.2022.
//

#pragma once

#include <iostream>
#include <vector>

enum class Orientation{TOP = 0, RIGHT, DOWN, LEFT};

enum class Color : char {RED = 'R', GREEN = 'G', BLUE = 'B', YELLOW = 'Y'};
/**
 * Puts string representation to ostream
 * It uses escape codes to print colored text in terminal
 * https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
 */
std::ostream & operator<<(std::ostream & out, const Color & color);

class Card
{
public:
    Card() = default;
    /**
     * Creates new card
     * Enter colors in clockwise order, first frontside and then backside
     * Put together 2 colors from each side
     * [(1, 2), (3, 4), (5, 6), (7, 8), (9, 10)...]
     *  front      back
     *    12       9 10
     *   8  3    16    11
     *   7  4    15    12
     *    65      14 13
     *
     * @param colors Colors of ropes on card
     * @param id ID of card, used for printing solution
     */
    Card(const std::vector<std::pair<Color, Color>> & colors,
         int id);

    /**
     * Returns pair of Colors on given side, based on current card's orientation
     *
     * @param orientation Side of the card
     * @return pair of Colors on given side
     */
    const std::pair<Color, Color> & getSide(Orientation orientation) const;
    /**
     * Rotates card, just changes card's orientation, m_colors not changing whole time
     */
    void rotate();
    /**
     * Returns true if the card is not empty, empty card represents empty spot in solution board
     */
    bool isEmpty() const;

    friend std::ostream & operator<<(std::ostream & out,
                                     const Card & card);
private:
    std::vector<std::pair<Color, Color>> m_colors;
    int m_id = 0;
    Orientation m_orientation = Orientation::TOP;
    bool m_isFlipped = false;
};
