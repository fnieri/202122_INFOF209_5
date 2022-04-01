//
// Created by louis on 3/30/22.
//

#pragma once
#include <atomic>
#include <iostream>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHoverEvent>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QTimer>
#include <QToolBox>
#include <QWidget>
#include <QHoverEvent>
#include <QRadioButton>
#include <QFrame>

#include "MainModel.h"
#include "ServerController.h"
#include "src/common/Message.h"
#include "src/common/Observer.h"
#include "src/common/Point.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class QtVue;
}
QT_END_NAMESPACE

class DrawLabel;

class QtVue : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit QtVue(QWidget *parent = nullptr);
    ~QtVue() override;
    void handleBoardPress(int x, int y);
    void handleBoardMove(int x, int y);

private slots:
    void handleLoginButtonClicked(const std::string &username, const std::string &password);
    void handleRegisterButtonClicked(const std::string &username, const std::string &password, const std::string &repeatPassword);
    void handlePawnButtonClicked();
    void handleWallButtonClicked();
    void handleHorizontalWallButtonClicked();
    void handleVerticalWallButtonClicked();

    void handleCreateGameButtonClicked();
    void handleJoinGameButtonClicked(const int &gameId);
    void handleQuitGameButtonClicked();
    void handleSurrenderButtonClicked();

private:
    Ui::QtVue *ui;
    QStackedWidget *stackWidget;

    MainController mainController;
    MainModel *mainModel;
    ServerController *serverController;
    GameModel *gameModel;

    // login tabs
    QTabWidget *loginTabBar;
    QLabel *loginMessage {};
    QLabel *registerMessage {};

    QTabWidget *mainTabBar {};

    // game tab
    QStackedWidget *gameStack {};
    QStackedWidget *gameIdsScroll {};
    QStackedWidget *createGameScroll {};
    QList<QCheckBox *> *pickFriendsList {};

    // leaderboard
    QLabel *userEloLabel {};
    QTableWidget *leaderboardLayout {};

    // game board
    int currentGameId = -1;
    int cellSize = 35;
    DrawLabel *drawLabel {};
    QPixmap *canvasPixmap {};
    QPainter *painter {};
    bool isTrainingGame = false;
    QPushButton *quitButton {};
    QPushButton *surrenderButton {};
    QPushButton *selectPawnMove{};
    QPushButton *selectWallMove{};
    QPushButton *selectHorizontalWall{};
    QPushButton *selectVerticalWall{};
    int moveType = 0; // 0 = pawn, 1 = wall
    int player = -1, correctMove = 10, incorrectMove = -10;
    WallOrientation wallOrientation = WallOrientation::Horizontal;
    const int *playerTurn;
    std::vector<std::vector<int>> boardIntMatrix;
    std::vector<std::vector<int>> boardMoveIntMatrix;

    // board update
    std::atomic<bool> eloUpdated {true};
    std::atomic<bool> leaderboardUpdated {false};
    std::atomic<bool> relationsUpdated {false};
    std::atomic<bool> chatsUpdated {false};
    std::atomic<bool> gameUpdated {false};
    std::atomic<bool> friendsUpdated {false};
    std::atomic<bool> gameIdsUpdated {false};
    std::atomic<bool> gameChatUpdated {false};

    // Friends
    QListWidget *friendListLW;
    QListWidget *chatHistLW;
    QListWidget *friendInvLW;
    QListWidget *friendSentLW;

    // Game chat
    QListWidget *gameChatHistLW;

    void createLoginAndRegister();
    void createMainPage();
    void createGamePage();
    void createFriendsPage();
    void createLeaderboardPage();
    void createBoard(QBoxLayout *layout);
    void createBoardChat(QBoxLayout *layout);
    void createTrainingPage();

    void drawBoard();
    Point getCellCoordinates(int x, int y) const;

    void updateValues();
    void update(QuoridorEvent) override;

    template <typename Callable>
    void updatePart(std::atomic<bool> &toBeUpdated, Callable updateFunc);

    void updateELO();
    void updateLeaderboard();
    void updateRelations();
    void updateChats();
    void updateGameChat();

    void updateNotifications();
    void updateFriends();
    void updateGameIds();
    void updateGame();
};

class DrawLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DrawLabel(QWidget *parent = nullptr, QtVue *vue = nullptr);

private:
    QtVue *vue;

    bool event(QEvent *e) override;

    void mousePressEvent(QMouseEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event);
};
