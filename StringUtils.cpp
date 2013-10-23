#include "StringUtils.hpp"

enum State {ESCAPED, UNESCAPED};

std::string escapeJSON(const std::string& input)
{
    std::string output;
    output.reserve(input.length());

    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        switch (input[i]) {
            case '"':
                output += "\\\"";
                break;
            case '/':
                output += "\\/";
                break;
            case '\b':
                output += "\\b";
                break;
            case '\f':
                output += "\\f";
                break;
            case '\n':
                output += "\\n";
                break;
            case '\r':
                output += "\\r";
                break;
            case '\t':
                output += "\\t";
                break;
            case '\\':
                output += "\\\\";
                break;
            default:
                output += input[i];
                break;
        }

    }

    return output;
}

std::string unescapeJSON(const std::string& input)
{
    State s = UNESCAPED;
    std::string output;
    output.reserve(input.length());

    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        switch(s)
        {
            case ESCAPED:
                {
                    switch(input[i])
                    {
                        case '"':
                            output += '\"';
                            break;
                        case '/':
                            output += '/';
                            break;
                        case 'b':
                            output += '\b';
                            break;
                        case 'f':
                            output += '\f';
                            break;
                        case 'n':
                            output += '\n';
                            break;
                        case 'r':
                            output += '\r';
                            break;
                        case 't':
                            output += '\t';
                            break;
                        case '\\':
                            output += '\\';
                            break;
                        default:
                            output += input[i];
                            break;
                    }
                
                    s = UNESCAPED;
                    break;
                }
            case UNESCAPED:
                {
                    switch(input[i])
                    {
                        case '\\':
                            s = ESCAPED;
                            break;
                        default:
                            output += input[i];
                            break;
                    }
                }
        }
    }
    return output;
}
