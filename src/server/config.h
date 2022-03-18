/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of user and server config
 * @date 2022-03-18
 */

#include <iostream>
#include <map> 
#include <fstream> // to open and read in a given file


class ConfigHandler
{
public:
    ConfigHandler();
    /**
     * @brief Get the Server Config map
     * 
     * @return map< string,  string> 
     */
    static  std::map< std::string,  std::string> getServerConfig();

    /**
     * @brief Get the User Config map
     * 
     * @return map< string,  string> 
     */
    static  std::map< std::string,  std::string> getUserConfig();

private:
    
    /**
     * @brief Get the Map object of a config file
     * 
     * @param filename
     * @return map<string,  string> 
     */
    static  std::map< std::string,  std::string> getMapFromConfigFile(std::string filename);

    /**
     * @brief Get the Key Value object
     * [@details Gets the key value from separating each side of a line from an equal symbal "=";
     * Is called within the getMapFromConfigFile(string) method]
     * @param line
     * @return pair< string,  string> 
     */
    static  std::pair< std::string,  std::string> getKeyValue(std::string line);

};