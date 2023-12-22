#ifndef __EXCEPT_H__
#define __EXCEPT_H__
#include <stdexcept>

class UsernameNotFound : public std::exception {};
class invalidArg : public std::exception {};
class IncorrectPassword : public std::exception {};

#endif
