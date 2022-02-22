/**
 * @file ObjectExchangesSerializableMessageFactory.h
 * @brief MessageFactory for requests and answers exchanges between user and server
 * @author Francesco Nieri
 * @date 21/02/2022
 */

#pragma once

#include "MessageEnums/Actions/ObjectExchanges.h"
#include "MessageEnums/Status.h"

#include <nlohmann/json.hpp>

class ObjectExchangesSerializableMessageFactory
{
public:
    /**
     * @brief serialize a user request of data
     * @param dataType Type of data the user wants to requesto
     * @return json of the request as such
     * {
     * "action" : "object_request",
     * "data_type" : "leaderboard | friend_list ...",
     * }
     */
    nlohmann::json serializeRequestExchange(DataType dataType) const;
    /**
     * @brief serialize an answer from server to user
     * @param dataType type of data the user has asked
     * @return json of the request as such
     * {
     * "action" : "object_answer",
     * "data_type" : "leaderboard | friend_list",
     * "serialized_data" : "json_serialized_object"
     * }
     */
    nlohmann::json serializeAnswerExchange(Exchange answerExchange, DataType dataType, Serializable serializableData) const;

    /**
     * @brief Serialize wether a status transmission failed
     * @param requestStatus wether the request was successful or not
     * @return json of the request as such
     * {
     * "action" : "status_transmission",
     * "status" : "success | failure"
     * }
     */
    nlohmann::json serializeStatusTransmission(RequestStatus requestStatus) const;
}
