
/*	AXIOM Remote
 **
 **	Copyright (C) 2018 Sebastian Pichelhofer
 * 
 **
 **	This program is free software; you can redistribute it and/or modify
 **    	it under the terms of the GNU General Public License 2 as published 
 **	by the Free Software Foundation.
 **
 **	Compile with -O6 for best experience
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "definitions.h"
#include "utility.c"

#ifndef PAGE_WB_HELP_C
#define PAGE_WB_HELP_C

uint16_t _help_page_text_color;
uint16_t _help_page_background_color;
uint8_t _help_page_padding_side;
uint16_t _help_page_scroll_index;
char _wb_help_text[512];

int8_t _wrap_tester;

void draw_wb_help_scroll_indicator(uint8_t line, uint8_t total_lines) {
    // maximum height is the screen without header area
    uint8_t srollbar_max_height = _height - 30;

    // height of the scroll indicator is defined by the ratio of number of items on screen vs total number of item. 
    // if there are 7 items on screen of total 14 items the scroll indicator shall be 50% of the scrollbar height
    uint8_t scrollbarheight = srollbar_max_height * (float) ((float) line / (float) (total_lines));

    //
    uint8_t scrollbaroffset = ((total_lines - line) - _menu_offset) * ((srollbar_max_height - scrollbarheight) / (total_lines - line));

    //Background
    fill_rect(framebuffer_width - 16, 0, 16, _height - 30, _help_page_background_color);

    //Thin Line
    fill_rect(framebuffer_width - 9, 0, 4, _height - 30, _help_page_text_color);

    //Thick Line
    fill_rect(framebuffer_width - 13, scrollbaroffset, 12, scrollbarheight, _help_page_text_color);
}

void draw_wb_help_page_side_items() {
    //left side

    //Home Icon
    if (_main_page[page_wb].page_item[6].highlighted) {
        drawRGBBitmap(0, 158, (uint16_t*) (home_icon_highlight.pixel_data), home_icon_highlight.width, home_icon_highlight.height);
    } else {
        drawRGBBitmap(0, 158, (uint16_t*) (home_icon.pixel_data), home_icon.width, home_icon.height);
    }

    // Back Icon
    if (_main_page[page_wb].page_item[7].highlighted) {
        drawRGBBitmap(0, 108, (uint16_t*) (back_icon_highlight.pixel_data), back_icon_highlight.width, back_icon_highlight.height);
    } else {
        drawRGBBitmap(0, 108, (uint16_t*) (back_icon.pixel_data), back_icon.width, back_icon.height);
    }
}


/**************************************************************************/
/*!
    @brief    draw the page
 */

/**************************************************************************/
void draw_wb_help_page() {
    //clear the screen
    fill_rect(0, 0, framebuffer_width, _height, _help_page_background_color);

    //draw header background
    //fill_rect(0, _top - 28, framebuffer_width, 28, _help_page_text_color);

    // Draw header
    draw_string(5, _height - 30, "White Balance Help", _help_page_text_color, _help_page_text_color,
            _FreeSans12pt7b, align_left, 0);

    //separation line
    draw_line(0, _top - 34, _right, _top - 34, color565(255, 128, 0));

    // draw side icons
    draw_wb_help_page_side_items();

    // draw scroll indicator
    draw_wb_help_scroll_indicator(_help_page_scroll_index, 10);

    //debug
    draw_rect(30 + 6, 5, framebuffer_width - 36 - 20 - _wrap_tester, 200, color565(255, 0, 0));

    //draw content
    draw_string(30 + 6, _top - 30 - 25 + _help_page_scroll_index, _wb_help_text, _help_page_text_color, _help_page_text_color,
            _FreeSans9pt7b, align_left, framebuffer_width - 36 - 20 - _wrap_tester);

    /*uint8_t length = string_len("This is a very long text with many letters ahahaha - its so incredible  lonmg.asdasd.");
    char debug[32];
    sprintf(debug, "length = %d", length);
    //debug_uart(_wb_help_text);
    debug_uart(debug);*/
}

void init_wb_help_page() {
    _help_page_text_color = color565(0, 0, 0);
    _help_page_background_color = color565(255, 255, 255);

    _help_page_padding_side = 10;
    _help_page_scroll_index = 0;

    strcpy(_wb_help_text, "Headline\nThis is a very long text with many letters - "
            "it's so incredibly long that it does not all fit into one line on the screen.");

    _wrap_tester = 0;
}

void wb_help_page_button_press_handler(ButtonID button_index) {
    if (button_index == P7) {
        _main_page[page_wb].page_item[6].highlighted = true;
    }
    if (button_index == P8) {
        _main_page[page_wb].page_item[7].highlighted = true;
    }
}

void wb_help_page_button_release_handler(ButtonID button_index) {
    if (button_index == P7) {
        _main_page[page_wb].page_item[6].highlighted = false;

        navigate_to_page(page_home, push_right);
    }
    if (button_index == P8) {
        _main_page[page_wb].page_item[7].highlighted = false;

        navigate_to_page(page_wb, push_right);
    }
}

void wb_help_page_knob_handler(ButtonID button_index, int8_t diff) {
    if (button_index == E1_rot) {
        _wrap_tester += diff;
        //_wrap_tester = limit_range(_wrap_tester, 0, 200);

        //_help_page_scroll_index += diff;
        //_help_page_scroll_index = limit_range(_help_page_scroll_index, 0, 100);
    }
}


#endif /* PAGE_WB_HELP_C */
