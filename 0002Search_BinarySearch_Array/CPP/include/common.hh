#ifndef __COMMON_HEADER__
#define __COMMON_HEADER__

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define COUT std::cout<<"["<<__func__<<", "<<__LINE__<<"]"
#define COUT_ERROR std::cout<<"\x1b[31m"<<"["<<__func__<<", "<<__LINE__<<"]"
#define UNIT_TEST_FAIL COUT_ERROR<<"Unit Test Failed."<<"\x1b[30m"<<std::endl

#define COLOR_BLACK "\x1b[30m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"

#define COLOR_BG_BLACK "\x1b[40m"
#define COLOR_BG_RED "\x1b[41m"
#define COLOR_BG_GREEN "\x1b[42m"
#define COLOR_BG_YELLOW "\x1b[43m"
#define COLOR_BG_BLUE "\x1b[44m"
#define COLOR_BG_MAGENTA "\x1b[45m"
#define COLOR_BG_CYAN "\x1b[46m"
#define COLOR_BG_WHITE "\x1b[47m"

#endif
