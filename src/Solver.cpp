//
// Created by Jan Orava on 30.04.2022.
//

#include <thread>
#include <algorithm>
#include <fstream>
#include "Solver.h"

void Solver::Solve(const std::string & fileName, std::ostream & out) {
    if(!LoadFromFile(fileName)) {
        out << "Error with file " << fileName << "\n";
        return;
    }

    std::thread t1(&Solver::SolveWorker, this, std::pair<int, int>{0, 0});
    std::thread t2(&Solver::SolveWorker, this, std::pair<int, int>{0, 1});
    std::thread t3(&Solver::SolveWorker, this, std::pair<int, int>{1, 1});

    t1.join();
    t2.join();
    t3.join();

    PrintSolution(out);
}

bool Solver::LoadFromFile(const std::string & filename) {
    std::ifstream file(filename);
    if(!file)
        return false;
    int id;
    char col1, col2;
    std::vector<std::pair<Color, Color>> colors;
    std::string validColors = "RGBY";

    for(int cardsCnt = 0; cardsCnt < 9; ++cardsCnt) {
        file >> id;
        if(id < 1 || id > 9)
            return false;

        colors.clear();
        for(int orientation = 0; orientation < 8; ++orientation) {
            file >> col1 >> col2;
            if (validColors.find(col1) == std::string::npos)
                return false;
            if (validColors.find(col2) == std::string::npos)
                return false;
            colors.emplace_back((Color)col1, (Color)col2);
        }

        m_cards.emplace_back(colors, id);
    }
    return true;
}

void Solver::SolveWorker(std::pair<int, int> startPosition) {
    std::vector<Card> availableCards(m_cards);
    std::array<std::array<Card, 3>, 3> solution;  // Local solution for current thread
    std::vector<std::pair<int, int>> availablePositions;
    solution[startPosition.first][startPosition.second] = availableCards.back();  // First card has fixed position
    availableCards.pop_back();
    availablePositions = MakeNeighbours(startPosition, availablePositions, solution);

    for(int orientation = 0; orientation < 8; ++orientation) {  // Tries all rotations of first card
        SolveRec(availableCards, availablePositions, solution);
        if(m_hasSolution)  // Ends if solution was found, even in other thread
            return;
        solution[startPosition.first][startPosition.second].rotate();
    }
}

void Solver::SolveRec(std::vector<Card> & availableCards,
                      std::vector<std::pair<int, int>> & availablePositions,
                      std::array<std::array<Card, 3>, 3> & solution) {
    if(availableCards.empty()) {  // End of recursion, all card are placed
        m_hasSolution = true;
        m_solution = solution;
        return;
    }

    std::pair<int, int> pos = availablePositions.back();
    availablePositions.pop_back();

    for(uint cardIndex = 0; cardIndex < availableCards.size(); ++cardIndex) {  // Try all cards
        Card card = availableCards[cardIndex];
        availableCards.erase(availableCards.begin() + cardIndex);

        for(int orientation = 0; orientation < 8; ++orientation) {  // Try all rotations
            if(CanBePlaced(card, solution, pos)) {
                solution[pos.first][pos.second] = card;
                auto neighbours = MakeNeighbours(pos, availablePositions, solution);
                SolveRec(availableCards, neighbours, solution);
                if(m_hasSolution)  // Ends if solution was found, even in other thread
                    return;
                solution[pos.first][pos.second] = Card();  // Card was placed wrong
            }
            card.rotate();
        }
        availableCards.insert(availableCards.begin() + cardIndex, card);  // Card can not be placed here
    }
    availablePositions.push_back(pos);  // On this position can not be placed any card, so this solution is wrong
}

std::vector<std::pair<int, int>> Solver::MakeNeighbours(const std::pair<int, int> & pos,
                                                        const std::vector<std::pair<int, int>> & availablePositions,
                                                        const std::array<std::array<Card, 3>, 3> & solution) {
    std::vector<std::pair<int, int>> res(availablePositions);  // Add free positions from previous step

    // Limit for vector boundaries
    int rowStart = std::max(pos.first - 1, 0);
    int rowEnd = std::min(pos.first + 1, 2);
    int colStart = std::max(pos.second - 1, 0);
    int colEnd = std::min(pos.second + 1, 2);

    for(int row = rowStart; row <= rowEnd; ++row)
        for(int col = colStart; col <= colEnd; ++col)
            // Get only position where is no card and is above, right, left or under given position
            if(solution[row][col].isEmpty() && (pos.first == row || pos.second == col))
                // Check if this position is not already in result from previous steps
                if(std::find(res.begin(), res.end(), std::pair<int, int>(row, col)) == res.end())
                    res.emplace_back(row, col);
    return res;
}

bool Solver::CanBePlaced(const Card & card,
                         std::array<std::array<Card, 3>, 3> & solution,
                         std::pair<int, int> position) {
    if(position.first > 0) {  // There is space above
        Card & above = solution[position.first - 1][position.second];
        if(!above.isEmpty())  // There is card above
            if(above.getSide(Orientation::DOWN).first != card.getSide(Orientation::TOP).second
            || above.getSide(Orientation::DOWN).second != card.getSide(Orientation::TOP).first)
                return false;  // Colors don't match, card can not be placed here
    }
    if(position.first < 2) {
        Card & under = solution[position.first + 1][position.second];
        if(!under.isEmpty())
            if(under.getSide(Orientation::TOP).first != card.getSide(Orientation::DOWN).second
            || under.getSide(Orientation::TOP).second != card.getSide(Orientation::DOWN).first)
                return false;
    }
    if(position.second > 0) {
        Card & left = solution[position.first][position.second - 1];
        if(!left.isEmpty())
            if(left.getSide(Orientation::RIGHT).first != card.getSide(Orientation::LEFT).second
            || left.getSide(Orientation::RIGHT).second != card.getSide(Orientation::LEFT).first)
                return false;
    }
    if(position.second < 2) {
        Card & right = solution[position.first][position.second + 1];
        if(!right.isEmpty())
            if(right.getSide(Orientation::LEFT).first != card.getSide(Orientation::RIGHT).second
            || right.getSide(Orientation::LEFT).second != card.getSide(Orientation::RIGHT).first)
                return false;
    }
    return true;
}

void Solver::PrintSolution(std::ostream & out) const {
    if(!m_hasSolution) {
        out << "Solution was not found!\n";
        return;
    }
    out << "Solution was found!\n\n";

    out << "IDs:\n";
    for(const auto & row : m_solution) {
        for(const auto & c : row) {
            out << c << " ";
        }
        out << "\n";
    }
    out << "\n";

    out << "Solution:\n";
    out << "----------------\n";
    for(const auto & row : m_solution) {
        out << "|";
        for(const auto & c : row) {
            out << " ";
            out << c.getSide(Orientation::TOP).first;
            out << c.getSide(Orientation::TOP).second;
            out << " |";
        }
        out << "\n|";
        for(const auto & c : row) {
            out << c.getSide(Orientation::LEFT).second;
            out << "  ";
            out << c.getSide(Orientation::RIGHT).first;
            out << "|";
        }
        out << "\n|";
        for(const auto & c : row) {
            out << c.getSide(Orientation::LEFT).first;
            out << "  ";
            out << c.getSide(Orientation::RIGHT).second;
            out << "|";
        }
        out << "\n|";
        for(const auto & c : row) {
            out << " ";
            out << c.getSide(Orientation::DOWN).second;
            out << c.getSide(Orientation::DOWN).first;
            out << " |";
        }
        out << "\n----------------\n";
    }
}
