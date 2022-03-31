//
// Created by louis on 3/30/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QtVue.h" resolved

#include "QtVue.h"
#include "ui_QtVue.h"

DrawLabel::DrawLabel(QWidget *parent, QtVue *vue)
    : QLabel(parent)
    , vue(vue)
{
    this->setAttribute(Qt::WA_Hover, true);
}

void DrawLabel::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    vue->handleBoardPress(event->x(), event->y());
}

void DrawLabel::hoverMoveEvent(QHoverEvent *event)
{
    vue->handleBoardMove(event->pos().x(), event->pos().y());
}

bool DrawLabel::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::HoverMove: {
        hoverMoveEvent(dynamic_cast<QHoverEvent *>(e));
        return true;
    }
    default:
        break;
    }
    return QLabel::event(e);
}

QtVue::QtVue(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtVue)
{
    ui->setupUi(this);

    mainModel = mainController.getMainModel();
    gameModel = mainModel->getCurrentGame();
    serverController = new ServerController {&mainController};

    stackWidget = new QStackedWidget(this);
    stackWidget->setGeometry(0, 0, this->width(), this->height());

    loginTabBar = new QTabWidget(this);
    createLoginAndRegister();
    mainTabBar = new QTabWidget(this);
}

QtVue::~QtVue()
{
    delete ui;
}

void QtVue::handleLoginButtonClicked(const std::string &username, const std::string &password)
{
    if (!serverController->login(username, password)) {
        loginMessage->setText("Wrong username or password");
    } else {
        serverController->fetchData();
        loginMessage->setText("Successfully logged in");
        createMainPage();
        stackWidget->removeWidget(loginTabBar);
    }
}

void QtVue::handleRegisterButtonClicked(const std::string &username, const std::string &password, const std::string &repeatPassword)
{
    if (password == repeatPassword && !username.empty() && !password.empty()) {
        if (serverController->registerUser(username, password)) {
            registerMessage->setText("Successfully registered. You can now log in.");
        } else {
            registerMessage->setText("Error creating account. Username probably already exists");
        }
    } else {
        registerMessage->setText("Passwords don't match or username is empty");
    }
}

void QtVue::createLoginAndRegister()
{
    auto loginBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto registerBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto loginTextEntry = new QLineEdit(this);
    loginTextEntry->setPlaceholderText("Login");
    loginBoxLayout->addWidget(loginTextEntry);

    auto passwordTextEntry = new QLineEdit(this);
    passwordTextEntry->setPlaceholderText("Password");
    passwordTextEntry->setEchoMode(QLineEdit::Password);
    loginBoxLayout->addWidget(passwordTextEntry);

    loginMessage = new QLabel("");
    loginMessage->setAlignment(Qt::AlignTop);
    loginBoxLayout->addWidget(loginMessage);

    auto loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, [this, loginTextEntry, passwordTextEntry]() {
        handleLoginButtonClicked(loginTextEntry->text().toStdString(), passwordTextEntry->text().toStdString());
    });
    loginBoxLayout->addWidget(loginButton);

    auto registerUsernameTextEntry = new QLineEdit(this);
    registerUsernameTextEntry->setPlaceholderText("Login");
    registerBoxLayout->addWidget(registerUsernameTextEntry);

    auto registerPasswordTextEntry = new QLineEdit(this);
    registerPasswordTextEntry->setPlaceholderText("Password");
    registerPasswordTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordTextEntry);

    auto registerPasswordConfirmTextEntry = new QLineEdit(this);
    registerPasswordConfirmTextEntry->setPlaceholderText("Confirm password");
    registerPasswordConfirmTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordConfirmTextEntry);

    registerMessage = new QLabel("");
    registerMessage->setAlignment(Qt::AlignTop);
    registerBoxLayout->addWidget(registerMessage);

    auto registerButton = new QPushButton("Register", this);
    connect(registerButton, &QPushButton::clicked, this, [this, registerUsernameTextEntry, registerPasswordTextEntry, registerPasswordConfirmTextEntry]() {
        handleRegisterButtonClicked(registerUsernameTextEntry->text().toStdString(), registerPasswordTextEntry->text().toStdString(),
            registerPasswordConfirmTextEntry->text().toStdString());
    });
    registerBoxLayout->addWidget(registerButton);

    auto loginBox = new QWidget(this);
    loginBox->setLayout(loginBoxLayout);

    auto registerBox = new QWidget(this);
    registerBox->setLayout(registerBoxLayout);

    createTrainingPage();

    loginTabBar->addTab(loginBox, "Login");
    loginTabBar->addTab(registerBox, "Register");

    stackWidget->addWidget(loginTabBar);
}

void QtVue::createGamePage()
{
    auto gamePickerLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto tLabel = new QLabel("Game page");
    gamePickerLayout->addWidget(tLabel);

    auto gamePage = new QWidget(this);
    gamePage->setLayout(gamePickerLayout);

    mainTabBar->addTab(gamePage, "Games");
}

void QtVue::createFriendsPage()
{
    auto friendsPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto tLabel = new QLabel("friends page");
    friendsPageLayout->addWidget(tLabel);

    auto friendsPage = new QWidget(this);
    friendsPage->setLayout(friendsPageLayout);

    mainTabBar->addTab(friendsPage, "Friends");
}

void QtVue::createLeaderboardPage()
{
    auto leaderboardPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    leaderboardLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto scrollArea = new QScrollArea(this);
    auto leaderboardScroll = new QWidget(this);
    leaderboardScroll->setLayout(leaderboardLayout);
    for (int i = 0; i < 100; i++) {
        auto tLabel = new QLabel("test");
        leaderboardLayout->addWidget(tLabel);
    }

    scrollArea->setWidget(leaderboardScroll);
    scrollArea->resize(100, 30);
    scrollArea->setWidgetResizable(false);
    leaderboardPageLayout->addWidget(scrollArea);

    userEloLabel = new QLabel("");
    leaderboardPageLayout->addWidget(userEloLabel);

    auto leaderboardPage = new QWidget(this);
    leaderboardPage->setLayout(leaderboardPageLayout);

    mainTabBar->addTab(leaderboardPage, "Leaderboard");
}

void QtVue::drawBoard()
{
    gameModel = mainModel->getCurrentGame();
    if (gameModel) {
        if (gameModel->hasWinner()) {
            painter->drawText(QRect(0, 0, 100, 100), "Player: " + QString::fromStdString(gameModel->getWinner()) + " has won!");
        } else {
            if (player == -1) {
                player = gameModel->getPlayerIdx(*mainModel->getUsername());
                playerTurn = gameModel->getCurrentPlayer();
            }
            gameModel->updateBoardIntMatrix(boardIntMatrix);
            if (boardMoveIntMatrix.empty()) {
                boardMoveIntMatrix = boardIntMatrix;
            }

            const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                      occupiedHorizontalQuoridor = 7;
            std::vector<Qt::GlobalColor> playerColors {Qt::red, Qt::green, Qt::blue, Qt::magenta};
            std::string remainingWallsText;
            auto remainingWallsMap = gameModel->getPlayersRemainingWalls();
            for (auto &[playerUsername, remainingWalls] : remainingWallsMap) {
                remainingWallsText += playerUsername + ": " + std::to_string(remainingWalls) + ", ";
            }

            canvasPixmap->fill(Qt::white);

            painter->drawText(QRect(0, 650, 200, 100), "You are player: " + QString::fromStdString(std::to_string(player)));
            painter->drawText(QRect(0, 670, 200, 100), "Player: " + QString::fromStdString(std::to_string(*playerTurn)));
            painter->drawText(QRect(0, 690, 500, 100),
                "Player: " + QString::fromStdString("Remaining walls: " + remainingWallsText.substr(0, remainingWallsText.size() - 2)));

            int dx = 10, dy = 10;
            Qt::GlobalColor cellColor;
            for (auto i = 0; i < boardIntMatrix.size(); i++) {
                for (auto j = 0; j < boardIntMatrix[i].size(); j++) {
                    int gridValue = boardIntMatrix[i][j];

                    switch (gridValue) {
                    case freeCell: {
                        // draw a free cell
                        cellColor = Qt::darkGray;
                        if (moveType == 0) {
                            if (boardMoveIntMatrix[i][j] == correctMove) {
                                cellColor = Qt::green;
                            } else if (boardMoveIntMatrix[i][j] == incorrectMove) {
                                cellColor = Qt::red;
                            }
                        }
                        painter->fillRect(dx, dy, cellSize, cellSize, cellColor);
                        break;
                    }

                    case emptyQuoridor: {
                        // don't draw anything otherwise
                        if (moveType == 1) {
                            if (boardMoveIntMatrix[i][j] == correctMove) {
                                cellColor = Qt::green;
                            } else if (boardMoveIntMatrix[i][j] == incorrectMove) {
                                cellColor = Qt::red;
                            } else {
                                cellColor = Qt::white;
                            }
                            if (wallOrientation == WallOrientation::Vertical && j % 2 == 1) {
                                painter->fillRect(dx + cellSize / 4, dy, cellSize / 2, cellSize, cellColor);
                            } else if (wallOrientation == WallOrientation::Horizontal && i % 2 == 1) {
                                painter->fillRect(dx, dy + cellSize / 4, cellSize, cellSize / 2, cellColor);
                            }
                        }
                        break;
                    }

                    case occupiedVerticalQuoridor: {
                        painter->fillRect(dx + cellSize / 4, dy, cellSize / 2, cellSize, cellColor);
                        break;
                    }
                    case occupiedHorizontalQuoridor: {
                        painter->fillRect(dx, dy + cellSize / 4, cellSize, cellSize / 2, cellColor);
                        break;
                    }

                    case playerOne:
                    case playerTwo:
                    case playerThree:
                    case playerFour:
                        // draw a player one cell
                        {
                            cellColor = playerColors[gridValue - 1];
                            painter->fillRect(dx, dy, cellSize, cellSize, cellColor);
                            break;
                        }

                    default:
                        break;
                    }

                    dx += cellSize;
                }
                dy += cellSize;
                dx = 10;
            }
            painter->setPen(QPen(Qt::black, 2));
            painter->drawRect(0, 0, cellSize * (int)boardIntMatrix.size() + 20, cellSize * (int)boardIntMatrix.size() + 20);
        }
    }
    drawLabel->setPixmap(*canvasPixmap);
}

void QtVue::createTrainingPage()
{
    auto trainingPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto tLabel = new QLabel("Training page");
    tLabel->setAlignment(Qt::AlignTop);
    trainingPageLayout->addWidget(tLabel);

    // this is board
    canvasPixmap = new QPixmap(QSize(620, 740));
    painter = new QPainter(canvasPixmap);
    drawLabel = new DrawLabel(this, this);
    trainingPageLayout->addWidget(drawLabel);

    selectPawnMove = new QPushButton("Pawn");
    selectWallMove = new QPushButton("Wall");
    selectHorizontalWall = new QPushButton("Horizontal");
    selectVerticalWall = new QPushButton("Vertical");
    connect(selectPawnMove, SIGNAL(clicked()), this, SLOT(handlePawnButtonClicked()));
    connect(selectWallMove, SIGNAL(clicked()), this, SLOT(handleWallButtonClicked()));
    connect(selectHorizontalWall, SIGNAL(clicked()), this, SLOT(handleHorizontalWallButtonClicked()));
    connect(selectVerticalWall, SIGNAL(clicked()), this, SLOT(handleVerticalWallButtonClicked()));
    selectPawnMove->setCheckable(true);
    selectWallMove->setCheckable(true);
    selectHorizontalWall->setCheckable(true);
    selectVerticalWall->setCheckable(true);
    selectPawnMove->setChecked(true);
    selectHorizontalWall->setChecked(true);
    selectPawnMove->setVisible(false);
    selectWallMove->setVisible(false);
    selectHorizontalWall->setVisible(false);
    selectVerticalWall->setVisible(false);

    auto selectWallOrientationLayout = new QHBoxLayout;
    selectWallOrientationLayout->addWidget(selectHorizontalWall);
    selectWallOrientationLayout->addWidget(selectVerticalWall);
    trainingPageLayout->addLayout(selectWallOrientationLayout);

    auto selectPawnWallLayout = new QHBoxLayout;
    selectPawnWallLayout->addWidget(selectPawnMove);
    selectPawnWallLayout->addWidget(selectWallMove);
    trainingPageLayout->addLayout(selectPawnWallLayout);

    auto trainingStartButton = new QPushButton("Start training", this);
    connect(trainingStartButton, &QPushButton::clicked, this, [this, trainingStartButton]() {
        mainModel->createAiGame();
        selectPawnMove->setVisible(true);
        selectWallMove->setVisible(true);
        trainingStartButton->setText("Restart");
        drawBoard();
    });

    // JUST FOR TESTING
    mainModel->createAiGame();
    selectPawnMove->setVisible(true);
    selectWallMove->setVisible(true);
    trainingStartButton->setText("Restart");
    drawBoard();

    trainingPageLayout->addWidget(trainingStartButton);

    auto trainingPage = new QWidget(this);
    trainingPage->setLayout(trainingPageLayout);

    loginTabBar->addTab(trainingPage, "Training");
}

void QtVue::updateValues()
{
    auto userElo = mainModel->getELO();
    userEloLabel->setText(QString::fromStdString(std::to_string(*userElo)));
}

void QtVue::createMainPage()
{
    createLeaderboardPage();
    createGamePage();
    createFriendsPage();

    stackWidget->addWidget(mainTabBar);
    stackWidget->setCurrentWidget(mainTabBar);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QtVue::updateValues);
    timer->start(1000);
}

Point QtVue::getCellCoordinates(int x, int y) const
{
    int i = (y - 10) / cellSize;
    int j = (x - 10) / cellSize;
    return {j, i};
}

void QtVue::handleBoardPress(int x, int y)
{
    if (gameModel) {
        auto cellCoordinates = getCellCoordinates(x, y);
        if (moveType == 0) {
            if (gameModel->isMoveValid(cellCoordinates)) {
                auto playerAction = gameModel->getPlayerAction(cellCoordinates);
                gameModel->processAction(playerAction.serialized().dump());
            }
        } else if (moveType == 1) {
            if (gameModel->isWallValid(cellCoordinates / 2, wallOrientation)) {
                auto wallAction = gameModel->getWallAction(cellCoordinates / 2, wallOrientation);
                gameModel->processAction(wallAction.serialized().dump());
            }
        }
        drawBoard();
    }
}

void QtVue::handleBoardMove(int x, int y)
{
    if (gameModel) {
        auto cellCoordinates = getCellCoordinates(x, y);
        boardMoveIntMatrix = boardIntMatrix;
        try {
            if (moveType == 0) {
                if (gameModel->isMoveValid(cellCoordinates)) {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = correctMove;
                } else {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = incorrectMove;
                }
            } else if (moveType == 1) {
                // TODO handle orientation
                if (gameModel->isWallValid(cellCoordinates / 2, wallOrientation)) {
                    int dx = wallOrientation == WallOrientation::Horizontal ? 1 : 0;
                    int dy = wallOrientation == WallOrientation::Vertical ? 1 : 0;
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = correctMove;
                    boardMoveIntMatrix.at(cellCoordinates.y() + dy).at(cellCoordinates.x() + dx) = correctMove;
                    boardMoveIntMatrix.at(cellCoordinates.y() + dy * 2).at(cellCoordinates.x() + dx * 2) = correctMove;

                } else {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = incorrectMove;
                }
            }
            drawBoard();
        } catch (std::out_of_range &e) {
        }
    }
}

void QtVue::handlePawnButtonClicked()
{
    if (!selectPawnMove->isChecked()) {
        selectPawnMove->setChecked(true);
    }
    moveType = 0;
    selectHorizontalWall->setVisible(false);
    selectVerticalWall->setVisible(false);
    selectWallMove->setChecked(false);
}

void QtVue::handleWallButtonClicked()
{
    if (!selectWallMove->isChecked()) {
        selectWallMove->setChecked(true);
    }
    moveType = 1;
    selectHorizontalWall->setVisible(true);
    selectVerticalWall->setVisible(true);
    selectPawnMove->setChecked(false);
}

void QtVue::handleHorizontalWallButtonClicked()
{
    if (!selectHorizontalWall->isChecked()) {
        selectHorizontalWall->setChecked(true);
    }
    wallOrientation = WallOrientation::Horizontal;
    selectVerticalWall->setChecked(false);
}

void QtVue::handleVerticalWallButtonClicked()
{
    if (!selectVerticalWall->isChecked()) {
        selectVerticalWall->setChecked(true);
    }
    wallOrientation = WallOrientation::Vertical;
    selectHorizontalWall->setChecked(false);
}
