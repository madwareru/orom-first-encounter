#ifndef MACRO_SHARED_H
#define MACRO_SHARED_H

#include <iostream>

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION_INNER __FILE__ " : " S2(__LINE__)
#define LOCATION " (" LOCATION_INNER ")"

#define REPEAT_2(x) (x), (x)
#define REPEAT_4(x) REPEAT_2(x), REPEAT_2(x)
#define REPEAT_8(x) REPEAT_4(x), REPEAT_4(x)
#define REPEAT_16(x) REPEAT_8(x), REPEAT_8(x)
#define REPEAT_32(x) REPEAT_16(x), REPEAT_16(x)

#define ROW_4_ASCENDING(x) (x), (x) + 1, (x) + 2, (x) + 3
#define ROW_8_ASCENDING(x) ROW_4_ASCENDING(x), ROW_4_ASCENDING((x + 4))
#define ROW_16_ASCENDING(x) ROW_8_ASCENDING(x), ROW_8_ASCENDING((x + 8))
#define ROW_32_ASCENDING(x) ROW_16_ASCENDING(x), ROW_16_ASCENDING((x + 16))
#define ROW_64_ASCENDING(x) ROW_32_ASCENDING(x), ROW_32_ASCENDING((x + 32))

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

#define MEMBER_DEF(t, rec_type, member_name, entry_name)\
    MemberDefinition<t>{offsetof(rec_type, member_name), FieldDefinition<t>{#entry_name}}

#define LOG(message_sequence) std::cout << message_sequence << LOCATION << std::endl
#define LOG_ERROR(message_sequence) std::cerr << message_sequence << LOCATION << std::endl

#endif // MACRO_SHARED_H
