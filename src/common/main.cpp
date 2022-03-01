#include "GameSetupSerializableMessageFactory.h"
#include "iostream"
#include "SerializableMessageFactory.h"
using json = nlohmann::json;

int main() {
    std::vector<std::string> b = {"a", "b", "c"};
    json a = SerializableMessageFactory::serializeGameSetup(GameMode::FOG_OF_WAR, b, 1, 2);
    std::cout << a.dump(4) << std::endl;
}