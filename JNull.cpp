/**
 * @file JNull.cpp
 * @class JNull
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JNull class
 *
 */

#include "JObject.hpp"

namespace json
{
    JNull::JNull():JValue(JNULL)
    {
    }

    void JNull::toString(std::string& toString) const
    {
        toString.append("null");
    }

    JValue* JNull::clone() const
    {
        return new JNull();
    }

    JNull::~JNull()
    {
    }
}
