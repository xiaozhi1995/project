#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <ncurses.h>
#include "comm.h"
//#define _SIZE_ 1024

class chat_window{
	public:
		chat_window();
		void put_str_to_win(WINDOW *_win, int y, int x, const std::string &msg);
		std::string get_str_from_win( WINDOW *_win );
		void clear_win_line( WINDOW *_win, int begin, int num);
		void create_header();
		void create_output();
		void create_friends_list();
		void create_input();
		void fflush_win(WINDOW *_win);
		~chat_window();

//	private:
	public:
		WINDOW *header;
		WINDOW *output;
		WINDOW *friends_list;
		WINDOW *input;
};




