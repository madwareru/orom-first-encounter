#ifndef MACRO_SHARED_H
#define MACRO_SHARED_H

#include <iostream>

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION_INNER __FILE__ " : " S2(__LINE__)
#define LOCATION " (" LOCATION_INNER ")"

#define LOG(message_sequence) std::cout << message_sequence << LOCATION << std::endl
#define LOG_ERROR(message_sequence) std::cerr << message_sequence << LOCATION << std::endl

#endif // MACRO_SHARED_H
