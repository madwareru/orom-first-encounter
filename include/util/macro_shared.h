#ifndef MACRO_SHARED_H
#define MACRO_SHARED_H

#include <iostream>

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION_INNER __FILE__ " : " S2(__LINE__)
#define LOCATION " (" LOCATION_INNER ")"

#define LOOKUP_CASE(dest, key, value)\
    case (key):                      \
        (dest) = (value);            \
        break;

#define LOOKUP_BUTTON_CASE(dest, btn_name) LOOKUP_CASE(dest, btn_name##_ID, btn_name##_ORDER)

#define DELCARE_BUTTON(btn_name, id, order, left, top) \
    const uint16_t btn_name##_ID = (id);               \
    const uint16_t btn_name##_ORDER = (order);         \
    const uint16_t btn_name##_LEFT = (left);           \
    const uint16_t btn_name##_TOP = (top);

#define COORDS_OF(btn_name) {btn_name##_LEFT, btn_name##_TOP}
#define GET_BUTTON_X(order) BUTTON_COORDS[(order)][0]
#define GET_BUTTON_Y(order) BUTTON_COORDS[(order)][1]

#define COORDS_OF_OFFSETTED(btn_name, dx, dy) {btn_name##_LEFT + (dx), btn_name##_TOP + (dy)}

#define LOG(message_sequence) std::cout << message_sequence << LOCATION << std::endl
#define LOG_ERROR(message_sequence) std::cerr << message_sequence << LOCATION << std::endl

#endif // MACRO_SHARED_H
