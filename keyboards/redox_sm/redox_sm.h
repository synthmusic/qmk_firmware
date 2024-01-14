#pragma once

#include "quantum.h"

#define LAYOUT( \
  l00, l01, l02, l03, l04,                          r41, r42, r43, r44, r45, \
  l10, l11, l12, l13, l14, l05,                r40, r51, r52, r53, r54, r55, \
  l20, l21, l22, l23, l24, l15,                r50, r61, r62, r63, r64, r65, \
       l31, l32,    l33,   l34, l35,      r70, r71,   r72,    r73, r74       \
) \
{ \
    { KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO}, \
    { l00,  l01,  l02,  l03,  l04,  l05  }, \
    { l10,  l11,  l12,  l13,  l14,  l15  }, \
    { l20,  l21,  l22,  l23,  l24,  KC_NO}, \
    { KC_NO,l31,  l32,  l33,  l34,  l35  }, \
    { KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO}, \
    { r40,  r41,  r42,  r43,  r44,  r45  }, \
    { r50,  r51,  r52,  r53,  r54,  r55  }, \
    { KC_NO,r61,  r62,  r63,  r64,  r65  }, \
    { r70,  r71,  r72,  r73,  r74,  KC_NO}  \
}
