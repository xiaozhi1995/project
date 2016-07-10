#include "chat_window.h"

chat_window::chat_window()
{
	initscr(); //screen
	curs_set(0);
}

void chat_window::put_str_to_win(WINDOW *_win, int y, int x, const std::string &msg)
{
	mvwaddstr(_win, y, x, msg.c_str());
}

std::string chat_window::get_str_from_win( WINDOW *_win ) 
{
	char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));
	wgetnstr(_win, buf, sizeof(buf)-1);
	return buf;
}

void chat_window::clear_win_line( WINDOW *_win, int begin, int num)
{
	while( num-- > 0 ){
		wmove(_win, begin++, 0);
		wclrtoeol(_win);
	}
}

void chat_window::fflush_win(WINDOW *_win)
{
	//mutex_lock
	box(_win, 0, 0);
	wrefresh(_win);
	//mutex_unlock
}

void chat_window::create_header()
{
	int _y = 0;
	int _x = 0;
	int _w = COLS;
	int _h = LINES/5;
	header = newwin(_h, _w, _y, _x); 
	fflush_win(header);
}

void chat_window::create_output()
{
	int _y = LINES/5;
	int _x = 0;
	int _w = (COLS*3)/4;
	int _h = (LINES*3)/5;
	output = newwin(_h, _w, _y, _x); 
	fflush_win(output);
}

void chat_window::create_friends_list()
{
	int _y = LINES/5;
	int _x = (COLS*3)/4;
	int _w = COLS/4;
	int _h = (LINES*3)/5;
	friends_list = newwin(_h, _w, _y, _x); 
	fflush_win(friends_list);
}

void chat_window::create_input()
{
	int _y = (LINES*4)/5;
	int _x = 0;
	int _w = COLS;
	int _h = LINES/5;
	input = newwin(_h, _w, _y, _x); 
	fflush_win(input);
}

chat_window::~chat_window()
{
	endwin();
}

