//
// Created by Jan Orava on 30.04.2022.
//

#pragma once

#include <vector>
#include <array>
#include "Card.h"

class Solver
{
public:
    explicit Solver(const std::vector<Card> & cards);

    /**
     * Solves Rubik's tangle puzzle
     * Creates 3 threads, 1. tries start from top-left
     *                    2. tries start from first row, second column
     *                    3. tries start from mid
     * First card must be in one option, other solutions are just solution board rotations
     *
     * @return true if solution was found
     */
    bool Solve();
    /**
     * Prints solution in human readable text
     */
    void PrintSolution(std::ostream & out) const;
private:
    std::vector<Card> m_cards;
    std::array<std::array<Card, 3>, 3> m_solution;  // There will be solution
    bool m_hasSolution = false;

    /**
     * Thread function, initializes all variables and call SolveRec
     *
     * @param startPosition position for the first card
     */
    void SolveWorker(std::pair<int, int> startPosition);
    /**
     * Recursively solves puzzle
     *
     * @param availableCards Card that can be placed to solution
     * @param availablePositions Positions on solution board where is no card and is next to some already placed card
     * @param solution Solution board
     */
    void SolveRec(std::vector<Card> & availableCards,
                  std::vector<std::pair<int, int>> & availablePositions,
                  std::array<std::array<Card, 3>, 3> & solution);

    /**
     * Finds new free spots in solution board next to given position
     * Returns all available positions which are next to some already placed card
     *
     * @param pos Position where new card was placed
     * @param availablePositions All available positions in previous step
     * @param solution Solution board
     * @return availablePositions merged with new free spots
     */
    static std::vector<std::pair<int, int>> MakeNeighbours(const std::pair<int, int> & pos,
                                                    const std::vector<std::pair<int, int>> & availablePositions,
                                                    const std::array<std::array<Card, 3>, 3> & solution);
    /**
     * Decides if card can be placed in board on given position
     * Colors on neighboring sides must match
     *  card1 card2
     *    RR   BB
     *   B  R R  Y
     *   Y  Y Y  Y
     *    GB   RB
     *
     * @param card New card
     * @param solution Solution board
     * @param position Position of new card
     * @return true if card can be correctly placed in board
     */
    static bool CanBePlaced(const Card & card,
                            std::array<std::array<Card, 3>, 3> & solution,
                            std::pair<int, int> position);
};
