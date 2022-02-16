/*
 * lcd.h
 *
 * Created: 16/02/2022 10:14:50
 *  Author: stijn
 */ 


#ifndef LCD_H
#define LCD_H

void init();
void display_text(char *str);
void set_cursor(int position);

#endif