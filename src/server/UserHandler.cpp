/**
 * @author Boris Petrov
 */

#include "UserHandler.h"

#include "ServerUser.h"
#include "src/common/Exceptions.h"

#include <nlohmann/json.hpp> // TODO: maybe not the whole thing !?

#include <thread>

using json = nlohmann::json;

/**
 * UserHandler
 */

UserHandler::UserHandler(UserHub *userHub, Socket &&user)
    : RequestHandler {std::move(user)}
    , m_userHub {userHub}
{
}

void UserHandler::handleRequests()
{
    // TODO finish this
    while (!m_isFinished) {
        try {
            if (hasReadActivity(1)) {
                auto serRequest {receive()};

                // Do not continue if the thread was terminated during or after the receive
                if (m_isFinished)
                    break;

                auto request {json::parse(serRequest)};

                if (request["action"] == "Login" || request["action"] == "Register") {

                    auto serAnswer {m_authHandler.processRequest(serMessage)};
                    auto answer {json::parse(serAnswer)};

                    if (answer["status"] == "Success") {
                        m_serverUser.bindTo(request["username"]);
                        send(serAnswer);
                    }
                }

                /* if (request["Type"] == "LogIn") { */
                /*     std::cout << "Loggin in"; */

                /* } else if (request["Type"] == "Register") { */
                /*     std::cout << "Registring"; */
                /* } */
            } else if (m_isFinished) {
                break;
            }

            // Client was disconnected
        } catch (UnableToRead &) {
            m_isFinished = true;
        } catch (UnableToSend &) {
            m_isFinished = true;
        }
    }

    m_userHub->eraseFinished();
}

bool UserHandler::isFinished() const
{
    return m_isFinished;
}

std::string UserHandler::getUsername() const
{
    return m_userHandled->getUsername();
}

void UserHandler::terminate()
{
    m_isFinished = true; // TODO: use another variable, to be able to send message to client about the termination
}

void UserHandler::relayMessage(const std::string &serMessage)
{
    // TODO: verification for user updates on certain specific messages
    send(serMessage);
}

/**
 * UserHub
 */

UserHub::~UserHub()
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    for (auto &h : m_handlers)
        h->terminate();
}

void UserHub::eraseFinished()
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](const auto &h) { return h->isFinished(); }), m_handlers.end()); // <3 c++
}

void UserHub::add(Socket &&user)
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    // Start handling
    std::shared_ptr<UserHandler> userHandler {std::make_shared<UserHandler>(this, std::move(user))};
    userHandler->startHandling();

    m_handlers.push_back(std::move(userHandler));
}

void UserHub::relayMessageTo(const std::string &username, const std::string &message)
{
    // TODO: fix if user doesn't exist
    auto &receiver {*std::find_if(m_handlers.begin(), m_handlers.end(), [username](const auto &h) { return h->getUsername() == username; })};
    receiver->relayMessage(message);
}

int UserHub::connectedUsers() const noexcept
{
    // Do not give size if the size is in the process of changing (add for example)
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    return m_handlers.size();
}