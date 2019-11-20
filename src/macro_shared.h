#ifndef MACRO_SHARED_H
#define MACRO_SHARED_H

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ " : " S2(__LINE__)

#endif // MACRO_SHARED_H
