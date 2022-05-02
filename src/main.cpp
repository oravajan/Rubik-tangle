#include <iostream>
#include <array>
#include "Card.h"
#include "Solver.h"

using namespace std;

vector<Card> createCards() {
    vector<Card> cards;
    // 1. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
        pair<Color, Color>{Color::RED, Color::BLUE},
        pair<Color, Color>{Color::GREEN, Color::BLUE},
        pair<Color, Color>{Color::YELLOW, Color::RED},
        pair<Color, Color>{Color::GREEN, Color::YELLOW},
        pair<Color, Color>{Color::RED, Color::GREEN},
        pair<Color, Color>{Color::BLUE, Color::GREEN},
        pair<Color, Color>{Color::YELLOW, Color::RED},
        pair<Color, Color>{Color::BLUE, Color::YELLOW},
    }, 1));
    // 2. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::BLUE, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::RED},
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
            pair<Color, Color>{Color::RED, Color::GREEN},
            pair<Color, Color>{Color::YELLOW, Color::RED},
            pair<Color, Color>{Color::GREEN, Color::BLUE},
    }, 2));
    // 3. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::BLUE, Color::YELLOW},
            pair<Color, Color>{Color::RED, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::BLUE},
            pair<Color, Color>{Color::RED, Color::GREEN},
            pair<Color, Color>{Color::BLUE, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::GREEN},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
            pair<Color, Color>{Color::RED, Color::YELLOW},
    }, 3));
    // 4. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::GREEN, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
            pair<Color, Color>{Color::GREEN, Color::YELLOW},
            pair<Color, Color>{Color::BLUE, Color::GREEN},
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::BLUE},
            pair<Color, Color>{Color::YELLOW, Color::RED},
    }, 4));
    // 5. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
            pair<Color, Color>{Color::RED, Color::GREEN},
            pair<Color, Color>{Color::BLUE, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::YELLOW},
            pair<Color, Color>{Color::BLUE, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::RED},
    }, 5));
    // 6. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::GREEN, Color::YELLOW},
            pair<Color, Color>{Color::RED, Color::YELLOW},
            pair<Color, Color>{Color::BLUE, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::BLUE},
            pair<Color, Color>{Color::GREEN, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::RED},
            pair<Color, Color>{Color::BLUE, Color::GREEN},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
    }, 6));
    // 7. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::GREEN, Color::YELLOW},
            pair<Color, Color>{Color::BLUE, Color::YELLOW},
            pair<Color, Color>{Color::RED, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::BLUE},
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::BLUE},
    }, 7));
    // 8. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::RED},
            pair<Color, Color>{Color::GREEN, Color::BLUE},
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::BLUE, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::YELLOW},
            pair<Color, Color>{Color::RED, Color::BLUE},
            pair<Color, Color>{Color::GREEN, Color::RED},
    }, 8));
    // 9. CARD
    cards.push_back(Card(vector<pair<Color, Color>>{
            pair<Color, Color>{Color::GREEN, Color::RED},
            pair<Color, Color>{Color::YELLOW, Color::GREEN},
            pair<Color, Color>{Color::RED, Color::BLUE},
            pair<Color, Color>{Color::YELLOW, Color::BLUE},
            pair<Color, Color>{Color::BLUE, Color::RED},
            pair<Color, Color>{Color::GREEN, Color::BLUE},
            pair<Color, Color>{Color::RED, Color::YELLOW},
            pair<Color, Color>{Color::GREEN, Color::YELLOW},
    }, 9));

    return cards;
}

int main() {
    Solver solver(createCards());
    if(solver.Solve())
        solver.PrintSolution(std::cout);
    else
        std::cout << "Solution was not found!" << std::endl;
    return 0;
}
