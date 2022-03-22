/**
 * @file GameModel.cpp
 * @author Louis Vanstappen
 * @author Boris Petrov
 * @brief Game Model
 * @date 02/25/22
 */

#pragma once

#include "Board.h"
#include "BoardComponent.h"
#include "src/common/Point.h"
#include "src/common/Message.h"

#include <map>
#include <memory>
#include <vector>

using json = nlohmann::json;

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;

class WallAction;
class PlayerAction;

/**
 * @param gameID the identifier of the game
 * @param players players in the game
 * @param boardConfiguration initial positions of walls and players
 */
class GameModel
{
private:
    int m_gameId {-1};

    std::shared_ptr<Board> m_board;
    std::vector<std::shared_ptr<Player>> m_players;

    std::string m_winner {""};

    int m_currentPlayerIdx {0};

    auto addPlayer(PawnColors, const Point &, int, FinishLine, const std::string &) -> void;

    auto getWallActionFromSer(const std::string &) -> WallAction;
    auto getPlayerActionFromSer(const std::string &) -> PlayerAction;

    /* std::map<std::string, SPtrToVec<Message>> m_gameChats; */

public:
    /**
     * @brief New game, with default config
     * @param players vector of their usernames
     */
    GameModel(const std::vector<std::string> &);
    /**
     * @brief Existing game, from an existent conf
     * @param players vector of their usernames
     */
    GameModel(const std::string &);

    /**
     * @note Winner can be established.
     */
    auto processAction(const std::string &) -> void;

    auto getCurrentPlayer() noexcept -> const int *;

    /* auto isMoveValid(const Point &) const noexcept -> bool; */
    /* auto isWallValid(const Point &, WallOrientation) const noexcept -> bool; */

    auto getPlayerAction(const Point &) const noexcept -> PlayerAction;
    auto getWallAction(const Point &, WallOrientation) const noexcept -> WallAction;

    auto hasWinner() const -> bool;
    auto getWinner() const -> std::string;

    /**
     * @note Winner can be established.
     */
    auto playerSurrendered(const std::string &) -> void;

    /* auto getBoardAsIntMatrix() -> std::vector<std::vector<int>>; */
    /* auto updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix) -> void; */
    /* auto addGameMessage(const std::string &, const Message &) -> void; */
};