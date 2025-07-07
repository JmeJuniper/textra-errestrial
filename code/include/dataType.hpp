/******************************************************************************
 * dataType.hpp
 * Solo header file
 * Defines "dataType" type alias for use in other files.
******************************************************************************/

#ifndef DATATYPE_H
    #define DATATYPE_H
    
    #include <string>
    #include <variant>
    #include <unordered_map>
    #include <SFML/Graphics.hpp>

    // Alias to store global data
    using dataType = std::unordered_map<
        std::string, std::variant<
            std::string
        >
    >;

#endif