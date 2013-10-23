/**
 * @file    StringUtils.hpp
 * @author  Mario Antunes (mariolpantunes@gmail.com)
 * @version 1.0
 * @date    October, 2013
 *
 * String utilities.
 * At the moment provides conversion from a unescaped
 * string to a escaped string and vice-versa.
 */

#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include<string>

std::string escapeJSON(const std::string& input);
std::string unescapeJSON(const std::string& input);

#endif
