#pragma once
#include <stdint.h>
#include <stdbool.h>

// #include "print.h"

#define BUF_APPEND(fmt, ...)                \
    uprintf(fmt __VA_OPT__(, )__VA_ARGS__)

    // pr_offset += snprintf(pr_buffer + pr_offset, sizeof(pr_buffer) - pr_offset, fmt __VA_OPT__(, )__VA_ARGS__)

#define BUF_UPRINT_CLEAR()                   \
    uprintf("\n")

bool bufferUseTabs = false;

uint16_t lastEventTime = 0;
uint16_t eventElapStartTime = 0;
uint16_t funcElapStartTime = 0;
bool resetEventElaps = true;
bool resetFuncElaps = true;

bool _DEL_SPC_held = false;
bool _DEL_ENT_held = false;
bool _DEL_doubledown_no_clear_layer = false;


uint16_t lastFuncTimer = 0;

void bufferFuncTime(void) {
    if (bufferUseTabs) {
        if (resetFuncElaps) {
            BUF_APPEND("-----  -----  ");
            funcElapStartTime = timer_read();
        } else {
            BUF_APPEND("%u  %u  ",
                timer_elapsed(funcElapStartTime),
                timer_elapsed(lastFuncTimer)
            );
        }
    } else {
        if (resetFuncElaps) {
            BUF_APPEND("   func: -----, ----- ");
            funcElapStartTime = timer_read();
        } else {
            BUF_APPEND("   func: %5u, %5u ",
                timer_elapsed(funcElapStartTime),
                timer_elapsed(lastFuncTimer)
            );
        }
    }
    lastFuncTimer = timer_read();
    resetFuncElaps = false;
}

void bufferEventTime(uint16_t* keycode, keyrecord_t* record) {
    if (bufferUseTabs) {
        if (resetEventElaps) {
            BUF_APPEND("-----  -----  ");
            eventElapStartTime = record->event.time;
        } else if (record->event.time == 0) {
            BUF_APPEND("--  --  ");
        } else {
            BUF_APPEND("%u  ",
                TIMER_DIFF_16(record->event.time, eventElapStartTime)
            );
            BUF_APPEND("%d  ",
                TIMER_DIFF_16(record->event.time, lastEventTime)
            );
        }
    } else {
        if (resetEventElaps) {
            BUF_APPEND("   event: -----, ----- ");
            eventElapStartTime = record->event.time;
        } else if (record->event.time == 0) {
            BUF_APPEND("   event:    --,    -- ");
        } else {
            BUF_APPEND("   event: %5u",
                TIMER_DIFF_16(record->event.time, eventElapStartTime)
            );
            BUF_APPEND(", %5d ",
                TIMER_DIFF_16(record->event.time, lastEventTime)
            );
        }

    }
    if (record->event.time) {
        lastEventTime = record->event.time;
    }
    resetEventElaps = false;
}


    // uprintf("%s\n", pr_buffer);
    // memset(pr_buffer, 0, sizeof(pr_buffer));
    // pr_offset = 0

void bufferInfo(uint16_t* keycode, keyrecord_t* record, const char* funcString) {
    if (bufferUseTabs) {
        BUF_APPEND("%04X  ", *keycode);
        BUF_APPEND("%s  ", funcString);
        BUF_APPEND("%s  ",
            record->event.pressed ? "\\/" : "^"
        );
        // BUF_APPEND("Taps ");
        if (record->tap.count) {
            BUF_APPEND("%u  ", record->tap.count);
        } else {
            BUF_APPEND("-  ");
        }
        BUF_APPEND("%s  ",
            record->tap.interrupted ? "Int" : ""
        );

    } else {
        BUF_APPEND("  %04X ", *keycode);
        BUF_APPEND(" %s ", funcString);
        BUF_APPEND("%s ",
            record->event.pressed ? "\\/ " : "  ^"
        );
        BUF_APPEND("Taps ");
        if (record->tap.count) {
            BUF_APPEND("%1u", record->tap.count);
        } else {
            BUF_APPEND("-");
        }
        BUF_APPEND(" %s  ",
            record->tap.interrupted ? "Int" : "   "
        );

    }
}

