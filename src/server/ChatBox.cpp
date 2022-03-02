/**
 * @file ChatBox.cpp
 * @author Boris Petrov
 * @brief Handler of chat requests
 * @date 02/25/22
 */

#include "ChatBox.h"

#include "Database.h"
#include "UserHandler.h"
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ChatBox::ChatBox(UserHub &userHub)
    : m_userHub {userHub}
{
}

void ChatBox::processRequest(const std::string &serMessage)
{
    recordMessage(serMessage);
    relayMessage(serMessage);
}

void ChatBox::recordMessage(const std::string &serRequest)
{
    auto request(json::parse(serRequest));

    // TODO see with database
    /* if (request["action"] == toJsonString(ChatInteraction::FRIEND_MESSAGE)) { */
    /*     DatabaseHandler::recordMessage(request["sender"], request["receiver"], request["message"]); */

    /* } else if (request["action"] == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) { */
    /*     DatabaseHandler::recordMessage(request["sender"], request["message"], request["game_id"]); */
    /* } */
}

void ChatBox::relayMessage(const std::string &serRequest)
{
    auto request(json::parse(serRequest));

    // Works only for one to one conversations
    m_userHub.relayMessageTo(request["receiver"], serRequest);
}
