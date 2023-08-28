#pragma once

#include "quantum.h"

#define LAYOUT( \
  k15, k16, k17, k18, k19, k06,                k07, k22, k23, k24, k25, k26, \
  k29, k30, k31, k32, k33, k20,                k21, k36, k37, k38, k39, k40, \
  k43, k44, k45, k46, k47, k34,                k35, k50, k51, k52, k53, k54, \
       k58, k59,    k60,   k61, k62,      k63, k64,   k65,    k66, k67       \
) \
{ \
    { KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,k06  }, \
    { k15,  k16,  k17,  k18,  k19,  k20  }, \
    { k29,  k30,  k31,  k32,  k33,  k34  }, \
    { k43,  k44,  k45,  k46,  k47,  KC_NO}, \
    { KC_NO,k58,  k59,  k60,  k61,  k62  }, \
    { k07,  KC_NO,KC_NO,KC_NO,KC_NO,KC_NO}, \
    { k21,  k22,  k23,  k24,  k25,  k26  }, \
    { k35,  k36,  k37,  k38,  k39,  k40  }, \
    { KC_NO,k50,  k51,  k52,  k53,  k54  }, \
    { k63,  k64,  k65,  k66,  k67,  KC_NO}  \
}
