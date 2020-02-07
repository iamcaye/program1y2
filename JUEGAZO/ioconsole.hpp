//-------------------------------------------------------------------------
// Author: Vicente Benjumea
// File: ioconsole.hpp
// Creation time: 2010/11/26 15:34:07 CET
// Modification time: 2011/03/03 20:27:18 CET
//-------------------------------------------------------------------------
//------------------------------------
// Version 1.0 2010/01/25
//------------------------------------
#ifndef _ioconsole_hpp_
#define _ioconsole_hpp_
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cassert>
/*	--------------------------------------------------------
 *	text output and manipulation
 *	- writing and reading text
 *		+ cprintf	sends formatted output to the screen
 *		+ cputs		sends a string to the screen
 *		+ putch		sends a single character to the screen
 *		+ cscanf	performs formatted input from console
 *		+ cgets		reads a string from console
 *		+ getche	reads a character and echoes it to the screen
 *		+ getch		reads a character from console (no echoing)
 *		+ getpass	reads a password
 *		+ kbhit		checks for recent keystrokes
 *		+ ungetch	pushes a character back to the keyboard buffer
 *	- manipulating text (and the cursor) on-screen
 *		+ clrscr	clears the text window
 *		+ clreol	clears from the cursor to the end of the line
 *		+ delline	deletes the line where the cursor rests
 *		+ gotoxy	positions the cursor
 *		+ insline	inserts a blank line below the line where the cursor rests
 *		+ movetext	copies text from oen area on screen to another
 *	- moving blocks of text into and out of memory
 *		+ gettext	copies text from an area on screen to memory
 *		+ puttext	copies text from memory to an area on screen
 *	--------------------------------------------------------
 *	window and mode control
 *		+ textmode	sets the screen to a text mode
 *		+ window	defines a text-mode window
 *	--------------------------------------------------------
 *	attribute control
 *	- setting foreground and background
 *		+ textcolor			sets the foreground color (attribute)
 *		+ textbackground	sets the background color (attribute)
 *		+ textattr			sets the fore and background colors (attribute)
 *	- converting intensity
 *		+ highvideo		sets text to high intensity
 *		+ lowvideo		sets text to low intensity
 *		+ normvideo		sets text to original intensity
 *	--------------------------------------------------------
 *	state query
 *		+ gettextinfo	fills in a text_info with info about the curr window
 *		+ wherex		gives the x-coord of the cell containing the cursor
 *		+ wherey		gives the y-coord of the cell containing the cursor
 *	--------------------------------------------------------
 */
//-------------------------------------------------------------------------
// void gettextinfo (struct text_info* info)
//		Returns information of the screen.
// void inittextinfo (void)
//		Call this if you need real value of normattr attribute in the
//		text_info structure.
// void clreol (void)
//		Clears rest of the line from cursor position to the end of line
//		without moving the cursor.
// void clrscr (void)
//		Clears whole screen.
// void delline (void)
//		Delete the current line (line on which is cursor) and then moves
//		all lines below one line up.
// void insline (void)
//		Insert blank line at the cursor position.
// void gettext (int left, int top, int right, int bottom,
//				struct char_info *buf)
//		Gets text from the screen.
// void puttext (int left, int top, int right, int bottom,
//				 struct char_info *buf)
//		Puts text back to the screen.
// void movetext (int left, int top, int right, int bottom,
//				  int destleft, int desttop)
//		Copies text.
// void gotoxy (int x, int y)
//		Moves cursor to the specified position.
// void cputsxy (int x, int y, char *str)
//		Puts string at the specified position.
// void putchxy (int x, int y, char ch)
//		Puts char at the specified position.
// void _setcursortype (int type)
//		Sets the cursor type.
// void textattr (int _attr)
//		Sets attribute of text.
// void normvideo (void)
//		Sets text attribute back to value it had after program start.
// void textbackground (int color)
//		Sets text background color.
// void textcolor (int color)
//		Sets text foreground color.
// int wherex (void)
//		Reads the cursor X position.
// int wherey (void)
//		Reads the cursor Y position.
// char* getpass (const char *prompt, char *str)
//		Reads password.
// void highvideo (void)
//		Makes foreground colors light.
// void lowvideo (void)
//		Makes foreground colors dark.
//---------------------------------------------------------------------
//-- Aleatorio --------------------------------------------------------
//---------------------------------------------------------------------
#if defined __unix__ || defined __APPLE__
#include <sys/time.h>
#elif defined __WIN32__
#include <windows.h>
#include <sys/types.h>
#include <sys/timeb.h>
#endif
namespace ioconsole_rand {
	// Inicializa el generador de numeros aleatorios
	inline unsigned ini_aleatorio(unsigned x = 0) {
		if (x == 0) {
#if defined __unix__ || defined __APPLE__
			struct timeval tv;
			gettimeofday(&tv, NULL);
			x = tv.tv_sec + tv.tv_usec;
#elif defined __WIN32__NO_DEFINIDO_
			struct _timeb tv;
			_ftime(&tv);
			x = tv.time + tv.millitm;
#else
			x = std::time(0) + std::clock();
#endif
		}
		std::srand(x);
		return x;
	}
	// Devuelve un numero aleatorio entre 0 y max (exclusive)
	inline unsigned aleatorio(unsigned max)
	{
		return unsigned(double(std::rand())*max/(RAND_MAX+1.0));
	}
	// devuelve un numero entre [inf..sup] ambos inclusive
	inline unsigned aleatorio(unsigned inf, unsigned sup)
	{
		return inf + aleatorio(sup - inf + 1);
	}
} // namespace ioconsole_rand
//-------------------------------------------------------------------------
//-- Base ---------------------------------------------------------------
//-------------------------------------------------------------------------
namespace conio_base {
	using namespace ioconsole_rand;
	//--------------------------------
	struct text_info {
		unsigned char winleft;
		unsigned char wintop;
		unsigned char winright;
		unsigned char winbottom;
		unsigned char attribute;
		unsigned char normattr;
		unsigned char currmode;
		unsigned char screenheight;
		unsigned char screenwidth;
		unsigned char curx;
		unsigned char cury;
	};
	//--------------------------------
	enum Colors {
		/*dark colors*/	// IRGB
		BLACK,			// 0000
		BLUE,			// 0001
		GREEN,			// 0010
		CYAN,			// 0011
		RED,			// 0100
		MAGENTA,		// 0101
		BROWN,			// 0110
		LIGHTGRAY,		// 0111
		/*light colors*/// IRGB
		DARKGRAY,		// 1000
		LIGHTBLUE,		// 1001
		LIGHTGREEN,		// 1010
		LIGHTCYAN,		// 1011
		LIGHTRED,		// 1100
		LIGHTMAGENTA,	// 1101
		YELLOW,			// 1110
		WHITE			// 1111
	};
	//--------------------------------
	enum Special_Key {
		//----------------------------
		KEY_ENTER	=0x0D,
		KEY_TAB		=0x09,
		KEY_ESC		=0x1B,
		KEY_BACKSP	=0x7F,
		//----------------------------
		KEY_HOME	=(KEY_ESC << 8) | 71,
		KEY_UP		=(KEY_ESC << 8) | 72,
		KEY_PGUP	=(KEY_ESC << 8) | 73,
		KEY_LEFT	=(KEY_ESC << 8) | 75,
		KEY_RIGHT	=(KEY_ESC << 8) | 77,
		KEY_END		=(KEY_ESC << 8) | 79,
		KEY_DOWN	=(KEY_ESC << 8) | 80,
		KEY_PGDOWN	=(KEY_ESC << 8) | 81,
		KEY_INSERT	=(KEY_ESC << 8) | 82,
		KEY_DELETE	=(KEY_ESC << 8) | 83,
		//----------------------------
		KEY_SHIFT_TAB 	=(KEY_ESC << 8) | 15,
		KEY_SHIFT_HOME 	=(KEY_ESC << 8) | 171,
		KEY_SHIFT_UP 	=(KEY_ESC << 8) | 172,
		KEY_SHIFT_PGUP 	=(KEY_ESC << 8) | 173,
		KEY_SHIFT_LEFT 	=(KEY_ESC << 8) | 175,
		KEY_SHIFT_RIGHT =(KEY_ESC << 8) | 177,
		KEY_SHIFT_END 	=(KEY_ESC << 8) | 179,
		KEY_SHIFT_DOWN 	=(KEY_ESC << 8) | 180,
		KEY_SHIFT_PGDOWN=(KEY_ESC << 8) | 181,
		KEY_SHIFT_INSERT=(KEY_ESC << 8) | 182,
		KEY_SHIFT_DELETE=(KEY_ESC << 8) | 183,
		//----------------------------
		KEY_META_HOME 	=(KEY_ESC << 8) | 151,
		KEY_META_UP 	=(KEY_ESC << 8) | 152,
		KEY_META_PGUP 	=(KEY_ESC << 8) | 153,
		KEY_META_LEFT 	=(KEY_ESC << 8) | 155,
		KEY_META_RIGHT 	=(KEY_ESC << 8) | 157,
		KEY_META_END 	=(KEY_ESC << 8) | 159,
		KEY_META_DOWN 	=(KEY_ESC << 8) | 160,
		KEY_META_PGDOWN =(KEY_ESC << 8) | 161,
		KEY_META_INSERT	=(KEY_ESC << 8) | 162,
		KEY_META_DELETE =(KEY_ESC << 8) | 163,
		//----------------------------
		KEY_SHIFT_META_HOME 	=(KEY_ESC << 8) | 90,
		KEY_SHIFT_META_UP 		=(KEY_ESC << 8) | 91,
		KEY_SHIFT_META_PGUP 	=(KEY_ESC << 8) | 92,
		KEY_SHIFT_META_LEFT 	=(KEY_ESC << 8) | 93,
		KEY_SHIFT_META_RIGHT 	=(KEY_ESC << 8) | 94,
		KEY_SHIFT_META_END 		=(KEY_ESC << 8) | 95,
		KEY_SHIFT_META_DOWN 	=(KEY_ESC << 8) | 96,
		KEY_SHIFT_META_PGDOWN	=(KEY_ESC << 8) | 97,
		KEY_SHIFT_META_INSERT	=(KEY_ESC << 8) | 98,
		KEY_SHIFT_META_DELETE	=(KEY_ESC << 8) | 99,
		//----------------------------
		KEY_CTRL_HOME 	=(KEY_ESC << 8) | 119,
		KEY_CTRL_UP 	=(KEY_ESC << 8) | 141,
		KEY_CTRL_PGUP 	=(KEY_ESC << 8) | 134,
		KEY_CTRL_LEFT 	=(KEY_ESC << 8) | 115,
		KEY_CTRL_RIGHT 	=(KEY_ESC << 8) | 116,
		KEY_CTRL_END 	=(KEY_ESC << 8) | 117,
		KEY_CTRL_DOWN 	=(KEY_ESC << 8) | 145,
		KEY_CTRL_PGDOWN =(KEY_ESC << 8) | 118,
		KEY_CTRL_INSERT	=(KEY_ESC << 8) | 146,
		KEY_CTRL_DELETE =(KEY_ESC << 8) | 147,
		//----------------------------
		KEY_SHIFT_CTRL_HOME 	=(KEY_ESC << 8) | 60,
		KEY_SHIFT_CTRL_UP 		=(KEY_ESC << 8) | 61,
		KEY_SHIFT_CTRL_PGUP 	=(KEY_ESC << 8) | 62,
		KEY_SHIFT_CTRL_LEFT 	=(KEY_ESC << 8) | 63,
		KEY_SHIFT_CTRL_RIGHT 	=(KEY_ESC << 8) | 64,
		KEY_SHIFT_CTRL_END 		=(KEY_ESC << 8) | 65,
		KEY_SHIFT_CTRL_DOWN 	=(KEY_ESC << 8) | 66,
		KEY_SHIFT_CTRL_PGDOWN 	=(KEY_ESC << 8) | 67,
		KEY_SHIFT_CTRL_INSERT	=(KEY_ESC << 8) | 68,
		KEY_SHIFT_CTRL_DELETE 	=(KEY_ESC << 8) | 69
		//----------------------------
	};
	//--------------------------------
}// namespace conio_base
//-------------------------------------------------------------------------
//-- Common ---------------------------------------------------------------
//-------------------------------------------------------------------------
namespace conio {
	using namespace conio_base;
	//---------------------------------------------------------------------
	enum Cursor {
		_NOCURSOR=0,
		_SOLIDCURSOR=1,
		_NORMALCURSOR=2
	};
	//--------------------------------
	namespace _impl_ {
		//--------------------------------
		enum Special_Dbl_Key {
			DOUBLE_CHAR_KEY_1=0,	// MS-DOS (0)
			DOUBLE_CHAR_KEY_2=224	// Windows :: Dev-C++ (0xE0)
		};
		//----------------------------
		template <typename TypeLabel>
		class Global {
			typedef typename TypeLabel::type Type;
			static Type val;
		public:
			static inline const Type& get() { return val; }
			static inline Type set(const Type& v) { Type x = val; val = v; return x; }
		};
		template <typename TypeLabel>
		typename Global<TypeLabel>::Type Global<TypeLabel>::val = TypeLabel::INIT_VAL;
		//----------------------------
		struct CursorType {
			typedef unsigned type;
			static const type INIT_VAL = 0;
		};
		struct ForeGround {
			typedef unsigned type;
			static const type INIT_VAL = LIGHTGRAY;
		};
		struct BackGround {
			typedef unsigned type;
			static const type INIT_VAL = BLACK;
		};
		struct MaxFil {
			typedef unsigned type;
			static const type INIT_VAL = 0;
		};
		struct MaxCol {
			typedef unsigned type;
			static const type INIT_VAL = 0;
		};
		//--------------------------------
	} // namespace _impl_
	//--------------------------------
	// NO IMPLEMENTADAS
	//--------------------------------
	// void _set_screen_lines(unsigned nlines);
	inline void textmode(unsigned /*_mode*/) {}
	inline void window(unsigned /*_left*/, unsigned /*_top*/,
					   unsigned /*_right*/, unsigned /*_bottom*/) {}
	inline int gettext(unsigned /*_left*/, unsigned /*_top*/,
					   unsigned /*_right*/, unsigned /*_bottom*/,
					   void */*_destin*/) {return 0;}
	inline int puttext(unsigned /*_left*/, unsigned /*_top*/,
					   unsigned /*_right*/, unsigned /*_bottom*/,
					   void* /*_source*/) {return 0;}
	inline int movetext(unsigned /*_left*/, unsigned /*_top*/,
						unsigned /*_right*/, unsigned /*_bottom*/,
						unsigned /*_destleft*/, unsigned /*_desttop*/) {return 0;}
	//--------------------------------
} // namespace conio
#ifdef __WIN32__
//-------------------------------------------------------------------------
//-- Windows --------------------------------------------------------------
//-------------------------------------------------------------------------
#include <windows.h>
#include <sys/types.h>
#include <sys/timeb.h>
namespace conio {
	//--------------------------------
	namespace _impl_ {
		//--------------------------------
		inline unsigned foregcol(unsigned c) {
			assert((FOREGROUND_BLUE==0x01)
				   &&(FOREGROUND_GREEN==0x02)
				   &&(FOREGROUND_RED==0x04)
				   &&(FOREGROUND_INTENSITY==0x08));
			return c;
		}
		//--------------------------------
		inline unsigned backgcol(unsigned c) {
			assert((BACKGROUND_BLUE==0x010)
				   &&(BACKGROUND_GREEN==0x020)
				   &&(BACKGROUND_RED==0x040)
				   &&(BACKGROUND_INTENSITY==0x080));
			return (c << 4);
		}
		//--------------------------------
		inline unsigned ch_attr(unsigned fc, unsigned bc) {
			return foregcol(fc) | backgcol(bc);
		}
		//--------------------------------
		inline unsigned ch_attr() {
			return ch_attr(_impl_::Global<_impl_::ForeGround>::get(),
						   _impl_::Global<_impl_::BackGround>::get());
		}
		//--------------------------------
		// Upper_Left_Corner: [1,1]
		inline void wherexy(unsigned& x, unsigned& y) {
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
			x = info.dwCursorPosition.X+1;
			y = info.dwCursorPosition.Y+1;
		}
		//--------------------------------
	} // namespace _impl_
	//---------------------------------------------------------------------
	inline void clear() {
		system("cls");
	}
	inline void pausa() {
		system("pause");
	}
	inline void msleep(unsigned milliseconds) {
		Sleep(milliseconds);	// milliseconds
	}
	//--------------------------------
	inline void gettextinfo(struct text_info* _r) {
		CONSOLE_SCREEN_BUFFER_INFO Info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
		_r->winleft = Info.srWindow.Left+1;
		_r->winright = Info.srWindow.Right+1;
		_r->wintop = Info.srWindow.Top+1;
		_r->winbottom = Info.srWindow.Bottom+1;
		_r->attribute = Info.wAttributes;
		_r->normattr = _impl_::ch_attr(LIGHTGRAY, BLACK);
		_r->currmode = '\0';
		//_r->screenheight = Info.dwSize.Y;
		//_r->screenwidth = Info.dwSize.X;
		_r->screenheight = _r->winbottom - _r->wintop + 1;
		_r->screenwidth = _r->winright - _r->winleft + 1;
		_r->curx = Info.dwCursorPosition.X+1;
		_r->cury = Info.dwCursorPosition.Y+1;
		_impl_::Global<_impl_::MaxFil>::set(_r->winbottom);
		_impl_::Global<_impl_::MaxCol>::set(_r->winright);
	}
	//--------------------------------
	inline void gettextinfo(struct text_info& _r) {
		gettextinfo(&_r);
	}
	//--------------------------------
	inline void disable_input_buffer() {}
	//--------------------------------
	inline unsigned _setcursortype(unsigned _type) {
		CONSOLE_CURSOR_INFO Info;
		switch (_type) {
		default:
			_type = _NOCURSOR;
		case _NOCURSOR:
			Info.bVisible = FALSE;
			Info.dwSize = 0;
			break;
		case _SOLIDCURSOR:
			Info.bVisible = TRUE;
			Info.dwSize = 100;
			break;
		case _NORMALCURSOR:
			Info.bVisible = TRUE;
			Info.dwSize = 1;
			break;
		}
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
		return _impl_::Global<_impl_::CursorType>::set(_type);
	}
	//--------------------------------
	// Upper_Left_Corner: [1,1]
	inline void gotoxy(unsigned x, unsigned y) {
		if (x >= 1 && x <= _impl_::Global<_impl_::MaxCol>::get()
			&& y >= 1 && y <= _impl_::Global<_impl_::MaxFil>::get()) {
			COORD c;
			c.X = x - 1;
			c.Y = y - 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}
	}
	//--------------------------------
	inline unsigned wherex() {
		unsigned x, y;
		_impl_::wherexy(x, y);
		return x;
	}
	//--------------------------------
	inline unsigned wherey() {
		unsigned x, y;
		_impl_::wherexy(x, y);
		return y;
	}
	//--------------------------------
	//inline void window(unsigned _left, unsigned _top,
	//				   unsigned _right, unsigned _bottom) {
	//	SMALL_RECT R;
	//	R.Left = _left-1;
	//	R.Top = _top-1;
	//	R.Right = _right-1;
	//	R.Bottom = _bottom-1;
	//	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &R);
	//	gotoxy(_left, _top);
	//}
	//--------------------------------
	inline void clreol() {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		COORD coord;
		coord.X = info.dwCursorPosition.X;
		coord.Y = info.dwCursorPosition.Y;
		DWORD written;
		FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
								   _impl_::ch_attr(),
								   info.dwSize.X - info.dwCursorPosition.X,
								   coord, &written);
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
								   info.dwSize.X - info.dwCursorPosition.X,
								   coord, &written);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	//--------------------------------
	inline void clrscr() {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		DWORD written;
		FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
								   _impl_::ch_attr(),
								   info.dwSize.X * info.dwSize.Y,
								   coord, &written);
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
								   info.dwSize.X * info.dwSize.Y,
								   coord, &written);
		SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	//--------------------------------
	void delline()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		COORD coord;
		coord.X = 0;
		coord.Y = info.dwCursorPosition.Y;
		SMALL_RECT rect;
		rect.Left = 0;
		rect.Top = info.dwCursorPosition.Y+1;
		rect.Right = info.dwSize.X - 1;
		rect.Bottom = info.dwSize.Y - 1;
		CHAR_INFO fillchar;
		fillchar.Attributes = _impl_::ch_attr();
		fillchar.Char.AsciiChar = ' ';
		ScrollConsoleScreenBuffer(GetStdHandle (STD_OUTPUT_HANDLE),
								  &rect, NULL, coord, &fillchar);

		gotoxy (info.dwCursorPosition.X+1, info.dwCursorPosition.Y+1);
	}
	//--------------------------------
	inline void insline() {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		COORD coord;
		coord.X = 0;
		coord.Y = info.dwCursorPosition.Y+1;
		SMALL_RECT rect;
		rect.Left = 0;
		rect.Top = info.dwCursorPosition.Y;
		rect.Right = info.dwSize.X - 1;
		rect.Bottom = info.dwSize.Y - 1;
		CHAR_INFO fillchar;
		fillchar.Attributes = _impl_::ch_attr();
		fillchar.Char.AsciiChar = ' ';
		ScrollConsoleScreenBuffer(GetStdHandle (STD_OUTPUT_HANDLE),
								  &rect, NULL, coord, &fillchar);

		gotoxy (info.dwCursorPosition.X+1, info.dwCursorPosition.Y+1);
	}
	//--------------------------------
	inline void textcolor(unsigned _color) {
		if (_color > WHITE) {
			_color = LIGHTGRAY;
		}
		_impl_::Global<_impl_::ForeGround>::set(_color);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
								_impl_::ch_attr());
	}
	//--------------------------------
	inline void textbackground(unsigned _color) {
		if (_color > WHITE) {
			_color = BLACK;
		}
		_impl_::Global<_impl_::BackGround>::set(_color);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
								_impl_::ch_attr());
	}
	//--------------------------------
	inline void textattr(unsigned _attr) {
		unsigned fc = (0x00F&_attr);
		unsigned bc = ((0x0F0&_attr)>>4);
		if (fc > WHITE) {
			fc = LIGHTGRAY;
		}
		if (bc > WHITE) {
			bc = BLACK;
		}
		_impl_::Global<_impl_::ForeGround>::set(fc);
		_impl_::Global<_impl_::BackGround>::set(bc);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
								_impl_::ch_attr());
	}
	//--------------------------------
	inline void intensevideo() {
		if (_impl_::Global<_impl_::ForeGround>::get() < DARKGRAY) {
			textcolor(_impl_::Global<_impl_::ForeGround>::get()+DARKGRAY);
		}
	}
	//--------------------------------
	inline void highvideo() {
		intensevideo();
	}
	//--------------------------------
	inline void lowvideo() {
		if (_impl_::Global<_impl_::ForeGround>::get() >= DARKGRAY) {
			textcolor(_impl_::Global<_impl_::ForeGround>::get()-DARKGRAY);
		}
	}
	//--------------------------------
	inline void blinkvideo() {
		intensevideo();
	}
	//--------------------------------
	inline void noblinkvideo() {
		lowvideo();
	}
	//--------------------------------
	inline void normvideo() {
		textattr(LIGHTGRAY | (BLACK<<4));
	}
	//--------------------------------
	//-- Predefined ------------------
	//--------------------------------
	extern "C" int	_cprintf (const char* format, ...)
#ifdef __GNUC__
		__attribute__ ((format (printf, 1, 2)))
#endif
		;
	extern "C" int	_cscanf (const char* format, ...)
#ifdef __GNUC__
		__attribute__ ((format (scanf, 1, 2)))
#endif
		;
	extern "C" char* _cgets(char* szBuffer);
	extern "C" int _cputs(const char* str);
	extern "C" int _putch(int c);
	extern "C" int _ungetch(int c);
	extern "C" int _kbhit();
	extern "C" int _getch();
	extern "C" int _getche();
	//--------------------------------
#define cprintf _cprintf
#define cscanf _cscanf
	//--------------------------------
	//--------------------------------
	inline char* cgets(char* szBuffer) {
		unsigned oldval = _setcursortype(_NORMALCURSOR);
		char* res = _cgets(szBuffer);
		_setcursortype(oldval);
		return res;
	}
	//--------------------------------
	inline void cgets(std::string& str) {
		unsigned oldval = _setcursortype(_NORMALCURSOR);
		std::getline(std::cin, str);
		_setcursortype(oldval);
	}
	//--------------------------------
	//inline char *getpass(const char *prompt) {
	//	return prompt; // ??? !!!
	//}
	//--------------------------------
	inline int cputs(const char* str) {
		return _cputs(str);
	}
	//--------------------------------
	inline int cputs(const std::string& str) {
		return cputs(str.c_str());
	}
	//--------------------------------
	inline int putch(int c) {
		return _putch(c);
	}
	//--------------------------------
	inline int ungetch(int c) {
		return _ungetch(c);
	}
	//--------------------------------
	inline int kbhit() {
		return _kbhit();
	}
	//--------------------------------
	inline int getkey() {
		int ch = _getch();
		if ((ch == _impl_::DOUBLE_CHAR_KEY_1)
			||(ch == _impl_::DOUBLE_CHAR_KEY_2)) {
			ch = (KEY_ESC << 8) | (0x0FF & _getch());
		} else if ((ch == '\n')||(ch == '\r')) {
			ch = KEY_ENTER;
		} else if (ch == '\b') {
			ch = KEY_BACKSP;
		} else if (ch == '\t') {
			ch = KEY_TAB;
		}
		return ch;
	}
	//--------------------------------
	inline int getch() {
		int ch = _getch();
		if (ch == _impl_::DOUBLE_CHAR_KEY_2) {
			ch = _impl_::DOUBLE_CHAR_KEY_1;
		}
		return ch;
	}
	//--------------------------------
	inline int getche() {
		int ch = _getche();
		if (ch == _impl_::DOUBLE_CHAR_KEY_2) {
			ch = _impl_::DOUBLE_CHAR_KEY_1;
		}
		return ch;
	}
	//---------------------------------------------------------------------
	namespace _impl_ {
		//--------------------------------
		template <typename Tipo>
		inline void cgetx(Tipo& x) {
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin >> x;
			_setcursortype(oldval);
		}
		//--------------------------------
		inline void cinws() {
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin >> std::ws;
			_setcursortype(oldval);
		}
		//--------------------------------
		inline void cgetc(char& x) {
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin.get(x);
			_setcursortype(oldval);
		}
		//--------------------------------
		//inline void maximize() {
			//ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
		//}
		//--------------------------------
		//inline void minimize() {
			//ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
		//}
		//--------------------------------
		//inline void hide() {
			//ShowWindow(GetConsoleWindow(), SW_HIDE);
		//}
		//--------------------------------
		//inline void swnormal() {
			//ShowWindow(GetConsoleWindow(), SW_NORMAL);
		//}
		//----------------------------
		inline void conio_end()
		{
			_setcursortype(_NORMALCURSOR);
		}
		//----------------------------
		inline unsigned conio_init() {
			static bool init = true;
			if (init) {
				init = false;
				//------------------------
				std::cerr.sync_with_stdio();
				std::cout.sync_with_stdio();
				std::cin.sync_with_stdio();
				//------------------------
				ini_aleatorio();
				text_info info; gettextinfo(info);
				std::atexit(conio_end);
				//------------------------
			}
			return 1;
		}
		static const unsigned trigger_init = conio_init();
		//----------------------------
		//----------------------------
	} // namespace _impl_
	//---------------------------------------------------------------------
} //namespace conio
#elif defined __unix__ || defined __APPLE__
//-------------------------------------------------------------------------
//-- Unix -----------------------------------------------------------------
//-------------------------------------------------------------------------
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/poll.h>
#include <sys/time.h>
/*
 * SCO defines TIOCGSIZE and the corresponding struct.  Other systems (SunOS,
 * Solaris, IRIX) define TIOCGWINSZ and struct winsize.
 */
#ifdef TIOCGSIZE
# define IOCTL_WINSIZE TIOCGSIZE
# define STRUCT_WINSIZE struct ttysize
# define WINSIZE_ROWS(n) (int)n.ts_lines
# define WINSIZE_COLS(n) (int)n.ts_cols
#else
# ifdef TIOCGWINSZ
#  define IOCTL_WINSIZE TIOCGWINSZ
#  define STRUCT_WINSIZE struct winsize
#  define WINSIZE_ROWS(n) (int)n.ws_row
#  define WINSIZE_COLS(n) (int)n.ws_col
# endif
#endif
namespace conio {
	//---------------------------------------------------------------------
	namespace _impl_ {
		enum FD_Ctes {
			FD_STDIN  = 0,
			FD_STDOUT = 1,
			FD_STDERR = 2
		};
		struct Term_Data {
			int fd;
			struct termios antes;
		};
		//----------------------------
		inline int set_icanon_echo(Term_Data& td)
		{
			struct termios nueva;
			td.fd = FD_STDIN; // fileno(stdin);
			tcgetattr(td.fd, &td.antes);
			nueva = td.antes;
			nueva.c_lflag |= (ICANON|ECHO);
			return tcsetattr(td.fd, TCSANOW, &nueva);
		}
		//----------------------------
		inline int reset_icanon_echo(Term_Data& td)
		{
			struct termios nueva;
			td.fd = FD_STDIN; // fileno(stdin);
			tcgetattr(td.fd, &td.antes);
			nueva = td.antes;
			nueva.c_lflag &= ~(ICANON|ECHO);
			//nueva.c_cc[VMIN] = 1;
			//nueva.c_cc[VTIME] = 0;
			return tcsetattr(td.fd, TCSANOW, &nueva);
		}
		//----------------------------
		inline int reset_icanon(Term_Data& td)
		{
			struct termios nueva;
			td.fd = FD_STDIN; //fileno(stdin);
			tcgetattr(td.fd, &td.antes);
			nueva = td.antes;
			nueva.c_lflag &= ~(ICANON);
			nueva.c_lflag |= ECHO;
			//nueva.c_cc[VMIN] = 1;
			//nueva.c_cc[VTIME] = 0;
			return tcsetattr(td.fd, TCSANOW, &nueva);
		}
		//----------------------------
		inline int reset_term(Term_Data& td)
		{
			return tcsetattr(td.fd, TCSANOW, &td.antes);
		}
		//----------------------------
		inline void screen_size(unsigned& nf, unsigned& nc)
		{
			int st;
			nf = 0;
			nc = 0;
			if (isatty(FD_STDOUT)) {
				STRUCT_WINSIZE size;
				errno = 0;
				while (((st = ioctl(FD_STDOUT, IOCTL_WINSIZE, &size)) < 0)
					   &&(errno == EINTR)) {
					/*vacio*/
				}
				if (st >= 0) {
					nf = WINSIZE_ROWS(size);
					nc = WINSIZE_COLS(size);
				}
			}
		}
		//------------------------------------
		static const unsigned COL2ANSI[16] = {
			0, 4, 2, 6, 1, 5, 3, 7, 0, 4, 2, 6, 1, 5, 3, 7
		};
		static const unsigned COL2INTENSITY[16] = {
			23, 23, 23, 23, 23, 23, 23, 23, 3, 3, 3, 3, 3, 3, 3, 3
		};
		//------------------------------------
		inline unsigned foregcol(unsigned c) {
			if (c <= WHITE) {
				c = 30+COL2ANSI[c];
			} else {
				c = 30+9;
			}
			return c;
		}
		//------------------------------------
		inline unsigned backgcol(unsigned c) {
			if (c <= WHITE) {
				c = 40+COL2ANSI[c];
			} else {
				c = 40+9;
			}
			return c;
		}
		//------------------------------------
		inline unsigned foregint(unsigned c) {
			if (c <= WHITE) {
				c = COL2INTENSITY[c];
			} else {
				c = 22;
			}
			return c;
		}
		//------------------------------------
		inline unsigned backgint(unsigned c) {
			return foregint(c);
		}
		//------------------------------------
		// Upper_Left_Corner: [1,1]
		inline void wherexy(unsigned& col, unsigned& fil) {
			std::fprintf(stdout, "\033[6n"); std::fflush(stdout);
			int l=0, c=0;
			std::scanf(" \033[%d;%dR",&l,&c);
			fil = l; col = c;
		}
		//----------------------------
		struct Key_Code {
			unsigned key;
			const char* seq;
		};
		static const Key_Code ESC_KEY_CODES[] = {
			// Ordenado por Secuencia
			{ KEY_UP,			"\033OA" },		// XTERM
			{ KEY_DOWN, 		"\033OB" },		// XTERM
			{ KEY_RIGHT, 		"\033OC" },		// XTERM
			{ KEY_LEFT, 		"\033OD" },		// XTERM
			{ KEY_END, 			"\033OF" },		// XTERM
			{ KEY_HOME, 		"\033OH" },		// XTERM

			{ KEY_SHIFT_UP, 	"\033[1;2A" },	// XTERM
			{ KEY_SHIFT_DOWN, 	"\033[1;2B" },	// XTERM
			{ KEY_SHIFT_RIGHT, 	"\033[1;2C" },	// XTERM
			{ KEY_SHIFT_LEFT, 	"\033[1;2D" },	// XTERM
			{ KEY_SHIFT_END, 	"\033[1;2F" },	// XTERM
			{ KEY_SHIFT_HOME, 	"\033[1;2H" },	// XTERM

			{ KEY_META_UP, 		"\033[1;3A" },	// XTERM
			{ KEY_META_DOWN, 	"\033[1;3B" },	// XTERM
			{ KEY_META_RIGHT, 	"\033[1;3C" },	// XTERM
			{ KEY_META_LEFT, 	"\033[1;3D" },	// XTERM
			{ KEY_META_END, 	"\033[1;3F" },	// XTERM
			{ KEY_META_HOME, 	"\033[1;3H" },	// XTERM

			{ KEY_SHIFT_META_UP, 	"\033[1;4A" },	// XTERM
			{ KEY_SHIFT_META_DOWN,	"\033[1;4B" },	// XTERM
			{ KEY_SHIFT_META_RIGHT,	"\033[1;4C" },	// XTERM
			{ KEY_SHIFT_META_LEFT, 	"\033[1;4D" },	// XTERM
			{ KEY_SHIFT_META_END, 	"\033[1;4F" },	// XTERM
			{ KEY_SHIFT_META_HOME, 	"\033[1;4H" },	// XTERM

			{ KEY_CTRL_UP, 		"\033[1;5A" },	// XTERM
			{ KEY_CTRL_DOWN,	"\033[1;5B" },	// XTERM
			{ KEY_CTRL_RIGHT,	"\033[1;5C" },	// XTERM
			{ KEY_CTRL_LEFT, 	"\033[1;5D" },	// XTERM
			{ KEY_CTRL_END, 	"\033[1;5F" },	// XTERM
			{ KEY_CTRL_HOME, 	"\033[1;5H" },	// XTERM

			{ KEY_SHIFT_CTRL_UP, 	"\033[1;6A" },	// XTERM
			{ KEY_SHIFT_CTRL_DOWN,	"\033[1;6B" },	// XTERM
			{ KEY_SHIFT_CTRL_RIGHT,	"\033[1;6C" },	// XTERM
			{ KEY_SHIFT_CTRL_LEFT, 	"\033[1;6D" },	// XTERM
			{ KEY_SHIFT_CTRL_END, 	"\033[1;6F" },	// XTERM
			{ KEY_SHIFT_CTRL_HOME, 	"\033[1;6H" },	// XTERM

			{ KEY_HOME,	 		"\033[1~" },	// linux

			{ KEY_SHIFT_INSERT,		"\033[2;2~" },	// XTERM
			{ KEY_META_INSERT, 		"\033[2;3~" },	// XTERM
			{ KEY_SHIFT_META_INSERT,"\033[2;4~" },	// XTERM
			{ KEY_CTRL_INSERT, 		"\033[2;5~" },	// XTERM
			{ KEY_SHIFT_CTRL_INSERT,"\033[2;6~" },	// XTERM
			{ KEY_INSERT, 			"\033[2~" },	// XTERM

			{ KEY_SHIFT_DELETE,		"\033[3;2~" },	// XTERM
			{ KEY_META_DELETE, 		"\033[3;3~" },	// XTERM
			{ KEY_SHIFT_META_DELETE,"\033[3;4~" },	// XTERM
			{ KEY_CTRL_DELETE, 		"\033[3;5~" },	// XTERM
			{ KEY_SHIFT_CTRL_DELETE,"\033[3;6~" },	// XTERM
			{ KEY_DELETE, 			"\033[3~" },	// XTERM

			{ KEY_END,	 		"\033[4~" },	// linux

			{ KEY_SHIFT_PGUP, 		"\033[5;2~" },	// XTERM
			{ KEY_META_PGUP, 		"\033[5;3~" },	// XTERM
			{ KEY_SHIFT_META_PGUP, 	"\033[5;4~" },	// XTERM
			{ KEY_CTRL_PGUP, 		"\033[5;5~" },	// XTERM
			{ KEY_SHIFT_CTRL_PGUP, 	"\033[5;6~" },	// XTERM

			{ KEY_CTRL_UP, 			"\033[5A" },	// ANSI
			{ KEY_CTRL_DOWN,		"\033[5B" },	// ANSI
			{ KEY_CTRL_RIGHT,		"\033[5C" },	// ANSI
			{ KEY_CTRL_LEFT, 		"\033[5D" },	// ANSI

			{ KEY_PGUP, 			"\033[5~" },	// XTERM linux
			
			{ KEY_SHIFT_PGDOWN, 	"\033[6;2~" },	// XTERM
			{ KEY_META_PGDOWN, 		"\033[6;3~" },	// XTERM
			{ KEY_SHIFT_META_PGDOWN,"\033[6;4~" },	// XTERM
			{ KEY_CTRL_PGDOWN, 		"\033[6;5~" },	// XTERM
			{ KEY_SHIFT_CTRL_PGDOWN,"\033[6;6~" },	// XTERM
			{ KEY_PGDOWN, 			"\033[6~" },	// XTERM linux

			{ KEY_UP, 			"\033[A" },		// ANSI linux
			{ KEY_DOWN, 		"\033[B" },		// ANSI linux
			{ KEY_RIGHT,		"\033[C" },		// ANSI linux
			{ KEY_LEFT, 		"\033[D" },		// ANSI linux
			{ KEY_END, 			"\033[F" },		// ANSI
			{ KEY_HOME, 		"\033[H" },		// ANSI

			{ KEY_INSERT, 		"\033[L" },		// ANSI
			{ KEY_SHIFT_TAB,	"\033[Z" },		// ANSI
		};
		//----------------------------
// 		inline bool esta_ordenado()
// 		{
// 			unsigned i = 0;
// 			unsigned f = sizeof(ESC_KEY_CODES)/sizeof(ESC_KEY_CODES[0]);
// 			while ((i < f-1)
// 				   &&(std::strcmp(ESC_KEY_CODES[i].seq,
// 								  ESC_KEY_CODES[i+1].seq)<0)) {
// 				++i;
// 			}
// 			return (i == f-1);
// 		}
		//----------------------------
		inline unsigned buscar_bin_mayig(char c,unsigned ix,const Key_Code v[],
										 unsigned i, unsigned f)
		{
			while (i < f) {
				unsigned m = (i + f) / 2;
				if (c <= v[m].seq[ix]) {
					f = m;
				} else {
					i = m + 1;
				}
			}
			return i;
		}
		//----------------------------
		inline unsigned buscar_bin_may(char c, unsigned ix, const Key_Code v[],
									   unsigned i, unsigned f)
		{
			while (i < f) {
				unsigned m = (i + f) / 2;
				if (c < v[m].seq[ix]) {
					f = m;
				} else {
					i = m + 1;
				}
			}
			return i;
		}
		//----------------------------
		inline void buscar_bin_rango(char c, unsigned ix, const Key_Code v[],
									 unsigned i, unsigned f,
									 unsigned& ii, unsigned& ff)
		{
			unsigned m = (i + f) / 2;
			while ((i < f)&&(c != v[m].seq[ix])) {
				if (c < v[m].seq[ix]) {
					f = m;
				} else {
					i = m + 1;
				}
				m = (i + f) / 2;
			}
			if (i < f) {
				ii = buscar_bin_mayig(c, ix, v, i, m);
				ff = buscar_bin_may(c, ix, v, m+1, f);
			} else {
				ii = ff = i;
			}
		}
		//----------------------------
		inline int getkey()
		{
			int c = std::cin.get();
			if ((c == _impl_::DOUBLE_CHAR_KEY_1)
				||(c == _impl_::DOUBLE_CHAR_KEY_2)) {
				c = (KEY_ESC << 8) | (0x0FF & std::cin.get());
			} else if ((c == '\n')||(c == '\r')) {
				c = KEY_ENTER;
			} else if (c == '\b') {
				c = KEY_BACKSP;
			} else if (c == '\t') {
				c = KEY_TAB;
			} else if (c == KEY_ESC) {
				unsigned ix = 0;
				unsigned i = 0;
				unsigned f = sizeof(ESC_KEY_CODES)/sizeof(ESC_KEY_CODES[0]);
				do {
					c = std::cin.get();
					++ix;
					buscar_bin_rango(char(c), ix, ESC_KEY_CODES, i, f, i, f);
				} while((i < f)&&(ESC_KEY_CODES[i].seq[ix+1] != '\0'));
				if ((i < f)&&(ESC_KEY_CODES[i].seq[ix+1] == '\0')) {
					c = ESC_KEY_CODES[i].key;
				} else {
					c = KEY_ESC;
				}
			}
			return c;
		}
		//----------------------------
		//inline void getline(std::string& str) {
		//	str = "";
		//	//int c;
		//	//while ((c=getchar())&&(c != EOF)&&(c != '\n')&&(c != '\r')) {
		//	char c;
		//	while (std::cin.get(c) && (c != '\n') && (c != '\r')) {
		//		str += char(c);
		//		//std::cout << int(c) <<' ';
		//	}
		//	//std::cout << int(c) << "# ";
		//}
		//--------------------------------
	}// namespace impl_
	//---------------------------------------------------------------------
	//--------------------------------
	inline void clear() {
		system("clear");
	}
	inline void pausa() {
		system("sh -c \"read -p 'press ENTER '\"");
	}
	inline void msleep(unsigned milliseconds) {
		struct timespec ts;
		ts.tv_sec = milliseconds/1000;				// seconds
		ts.tv_nsec = (milliseconds%1000)*1000000;	// nanoseconds
		nanosleep(&ts, NULL);
		//extern "C" void usleep(unsigned long usec);
		//usleep(milliseconds*1000);				// microseconds
	}
	//--------------------------------
	inline void disable_input_buffer() {
		//std::cin.rdbuf()->pubsetbuf(0,0);
		//setvbuf(stdin, (char *)NULL, _IOLBF, 0); //setlinebuf(stdin);
		//setvbuf(stdin, (char *)NULL, _IONBF, 0);   //setbuf(stdin, 0);
		std::setbuf(stdin, 0);
	}
	//--------------------------------
	inline unsigned _setcursortype(unsigned _type)
	{
		switch (_type) {
		default:
			_type = _NOCURSOR;
		case _NOCURSOR:
			std::fprintf(stdout, "\033[?25l");
			std::fflush(stdout);
			break;
		case _SOLIDCURSOR:
			std::fprintf(stdout, "\033[?12l\033[?25h");
			std::fflush(stdout);
			break;
		case _NORMALCURSOR:
			std::fprintf(stdout, "\033[?12l\033[?25h");
			std::fflush(stdout);
			break;
		}
		return _impl_::Global<_impl_::CursorType>::set(_type);
	}
	//------------------------------------
	// Upper_Left_Corner: [1,1]
	inline void gotoxy(unsigned x, unsigned y) {
		// Esquina superior izquierda: [1,1]
		if (x >= 1 && x <= _impl_::Global<_impl_::MaxCol>::get()
			&& y >= 1 && y <= _impl_::Global<_impl_::MaxFil>::get()) {
			std::fprintf(stdout, "\033[%d;%dH", y, x);
			//std::fflush(stdout);
		}
	}
	//--------------------------------
	inline unsigned wherex() {
		unsigned x, y;
		_impl_::wherexy(x, y);
		return x;
	}
	//--------------------------------
	inline unsigned wherey() {
		unsigned x, y;
		_impl_::wherexy(x, y);
		return y;
	}
	//--------------------------------
	inline void gettextinfo(struct text_info* _r)
	{
		unsigned nf, nc;
		_impl_::screen_size(nf, nc);
		_r->winleft = 1;
		_r->winright = (unsigned char)nc;
		_r->wintop = 1;
		_r->winbottom = (unsigned char)nf;
		_r->attribute = (unsigned char)(_impl_::Global<_impl_::ForeGround>::get()
						 | (_impl_::Global<_impl_::BackGround>::get() << 4));
		_r->normattr = 0;
		_r->currmode = 0;
		_r->screenheight = (unsigned char)nf;
		_r->screenwidth = (unsigned char)nc;
		unsigned x, y;
		_impl_::wherexy(x, y);
		_r->curx = (unsigned char)x; //wherex();
		_r->cury = (unsigned char)y; //wherey();
		_impl_::Global<_impl_::MaxFil>::set(_r->winbottom);
		_impl_::Global<_impl_::MaxCol>::set(_r->winright);
	}
	//--------------------------------
	inline void gettextinfo(struct text_info& _r) {
		gettextinfo(&_r);
	}
	//--------------------------------
	inline void delline()
	{
		std::fprintf(stdout, "\033[M");
		std::fflush(stdout);
	}
	//--------------------------------
	inline void insline() {
		std::fprintf(stdout, "\033[L");
		std::fflush(stdout);
	}
	//------------------------------------
	inline void clreol()
	{
		std::fprintf(stdout, "\033[K");
		std::fflush(stdout);
	}
	//------------------------------------
	inline void clrscr()
	{
		//std::fprintf(stdout, "\033[H\033[2J"); // XTERM
		std::fprintf(stdout, "\033[H\033[J"); // ANSI
		std::fflush(stdout);
	}
	//--------------------------------
	inline void textcolor(unsigned _color) {
		if (_color > WHITE) {
			_color = LIGHTGRAY;
		}
		_impl_::Global<_impl_::ForeGround>::set(_color);
		std::fprintf(stdout, "\033[%d;%dm",
					 _impl_::foregint(_color),
					 _impl_::foregcol(_color));
		//std::fflush(stdout);
	}
	//--------------------------------
	inline void textbackground(unsigned _color) {
		if (_color > WHITE) {
			_color = BLACK;
		}
		_impl_::Global<_impl_::BackGround>::set(_color);
		std::fprintf(stdout, "\033[%dm",
					 _impl_::backgcol(_color));
		//std::fflush(stdout);
	}
	//--------------------------------
	inline void textattr(unsigned _attr) {
		unsigned fc = (0x00F&_attr);
		unsigned bc = ((0x0F0&_attr)>>4);
		if (fc > WHITE) {
			fc = LIGHTGRAY;
		}
		if (bc > WHITE) {
			bc = BLACK;
		}
		_impl_::Global<_impl_::ForeGround>::set(fc);
		_impl_::Global<_impl_::BackGround>::set(bc);
		std::fprintf(stdout, "\033[%d;%d;%dm",
					 _impl_::backgcol(bc),
					 _impl_::foregint(fc),
					 _impl_::foregcol(fc));
		//std::fflush(stdout);
	}
	//------------------------------------
	inline void intensevideo()
	{
		//std::fprintf(stdout, "\033[7m");
		std::fprintf(stdout, "\033[3m");
		//std::fflush(stdout);
		//if (_impl_::Global<_impl_::ForeGround>::get() < DARKGRAY) {
		//	textcolor(_impl_::Global<_impl_::ForeGround>::get()+DARKGRAY);
		//}
	}
	//------------------------------------
	inline void highvideo()
	{
		intensevideo();
	}
	//------------------------------------
	inline void lowvideo()
	{
		//std::fprintf(stdout, "\033[27m");
		std::fprintf(stdout, "\033[23m");
		//std::fflush(stdout);
		//if (_impl_::Global<_impl_::ForeGround>::get() >= DARKGRAY) {
		//	textcolor(_impl_::Global<_impl_::ForeGround>::get()-DARKGRAY);
		//}
	}
	//------------------------------------
	inline void blinkvideo()
	{
		std::fprintf(stdout, "\033[5m");
		//std::fflush(stdout);
	}
	//------------------------------------
	inline void noblinkvideo()
	{
		std::fprintf(stdout, "\033[25m");
		//std::fflush(stdout);
	}
	//------------------------------------
	inline void normvideo()
	{
		std::fprintf(stdout, "\033[0m");
		//std::fflush(stdout);
	}
	//--------------------------------
	int cprintf(const char* format, ...)
#ifdef __GNUC__
		__attribute__ ((format (printf, 1, 2)))
#endif
		;
	inline int cprintf(const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		int res = std::vfprintf(stdout, format, ap);
		//std::fflush(stdout);
		va_end(ap);
		return res;
	}
	//--------------------------------
	int cscanf(const char* format, ...)
#ifdef __GNUC__
		__attribute__ ((format (scanf, 1, 2)))
#endif
		;
	inline int cscanf(const char* format, ...)
	{
		//-DRIE-----------------------
		_impl_::Term_Data old_flags;	// DRIE
		set_icanon_echo(old_flags);		// DRIE
		//----------------------------
		unsigned oldval = _setcursortype(_NORMALCURSOR);
		va_list ap;
		va_start(ap, format);
		int res = std::vscanf(format, ap);
		va_end(ap);
		_setcursortype(oldval);
		//-DRIE-----------------------
		reset_term(old_flags);			// DRIE
		//----------------------------
		return res;
	}
	//--------------------------------
	inline char* cgets(char* szBuffer) {
		//-DRIE-----------------------
		_impl_::Term_Data old_flags;	// DRIE
		set_icanon_echo(old_flags);		// DRIE
		//----------------------------
		unsigned oldval = _setcursortype(_NORMALCURSOR);
		std::cin.getline(&szBuffer[2], szBuffer[0]);
		szBuffer[1] = (char)0;
		if (std::cin.gcount() > 0) {
			szBuffer[1] = (char)std::cin.gcount();
			if (! std::cin.fail()) {
				--szBuffer[1]; // elimino '\n' de la cuenta
			}
		}
		_setcursortype(oldval);
		//-DRIE-----------------------
		reset_term(old_flags);			// DRIE
		//----------------------------
		return &szBuffer[2];
	}
	//--------------------------------
	inline void cgets(std::string& str) {
		//-DRIE-----------------------
		_impl_::Term_Data old_flags;	// DRIE
		set_icanon_echo(old_flags);		// DRIE
		//----------------------------
		unsigned oldval = _setcursortype(_NORMALCURSOR);
		std::getline(std::cin, str);
		_setcursortype(oldval);
		//-DRIE-----------------------
		reset_term(old_flags);			// DRIE
		//----------------------------
	}
	//--------------------------------
	//inline char *getpass(const char *prompt) {
	//	return prompt; // ??? !!!
	//}
	//--------------------------------
	inline int cputs(const char* str) {
		std::fprintf(stdout,"%s", str);
		//std::fflush(stdout);
		return 0;
	}
	//--------------------------------
	inline int cputs(const std::string& str) {
		return cputs(str.c_str());
	}
	//--------------------------------
	inline int putch(int c) {
		std::fprintf(stdout,"%c", char(c));
		//std::fflush(stdout);
		return 0;
	}
	//--------------------------------
	inline int ungetch(int c) {
		std::cin.putback(char(c));
		return 0;
	}
	//--------------------------------
	inline int kbhit() {
		struct pollfd pfds[1];
		pfds[0].fd = _impl_::FD_STDIN;
		pfds[0].events = POLLIN|POLLPRI;
		pfds[0].revents = 0;
		//-DRIE-----------------------
		//_impl_::Term_Data old_flags;	// DRIE
		//reset_icanon_echo(old_flags);	// DRIE
		//----------------------------
		int key_pressed = (poll(pfds, 1, 0) > 0);
		//-DRIE-----------------------
		//reset_term(old_flags);		// DRIE
		//----------------------------
		return key_pressed;
	}
	//--------------------------------
	//inline int kbhit () {
	//	fd_set rdfs;
	//	struct timeval tv;
	//	tv.tv_sec = 0;
	//	tv.tv_usec = 0;
	//	FD_ZERO(&rdfs);
	//	FD_SET (_impl_::FD_STDIN, &rdfs);
	//	select(_impl_::FD_STDIN+1, &rdfs, NULL, NULL, &tv);
	//	return FD_ISSET(_impl_::FD_STDIN, &rdfs);
	//}
	//--------------------------------
	inline int getkey() {
		//-DRIE-----------------------
		//_impl_::Term_Data old_flags;	// DRIE
		//reset_icanon_echo(old_flags);	// DRIE
		//----------------------------
		int c = _impl_::getkey();
		//-DRIE-----------------------
		//reset_term(old_flags);		// DRIE
		//----------------------------
		return c;
	}
	//--------------------------------
	inline int getch() {
		int c = getkey();
		//----------------------------
		if ((c&0x0FF00) == (KEY_ESC << 8)) {
			ungetch(c&0x00FF);
			c = _impl_::DOUBLE_CHAR_KEY_1;
		}
		//----------------------------
		return c;
	}
	//--------------------------------
	inline int getche() {
		int c = getch();
		if ((c >= 0x20)&&(c <= 0x7F)) {
			putch(c&0x7F);
		}
		return c;
	}
	//---------------------------------------------------------------------
	namespace _impl_ {
		//--------------------------------
		template <typename Tipo>
		inline void cgetx(Tipo& x) {
			//-DRIE-----------------------
			_impl_::Term_Data old_flags;	// DRIE
			set_icanon_echo(old_flags);		// DRIE
			//----------------------------
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin >> x;
			_setcursortype(oldval);
			//-DRIE-----------------------
			reset_term(old_flags);			// DRIE
			//----------------------------
		}
		//--------------------------------
		inline void cinws() {
			//-DRIE-----------------------
			_impl_::Term_Data old_flags;	// DRIE
			set_icanon_echo(old_flags);		// DRIE
			//----------------------------
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin >> std::ws;
			_setcursortype(oldval);
			//-DRIE-----------------------
			reset_term(old_flags);			// DRIE
			//----------------------------
		}
		//--------------------------------
		inline void cgetc(char& x) {
			//-DRIE-----------------------
			_impl_::Term_Data old_flags;	// DRIE
			set_icanon_echo(old_flags);		// DRIE
			//----------------------------
			unsigned oldval = _setcursortype(_NORMALCURSOR);
			std::cin.get(x);
			_setcursortype(oldval);
			//-DRIE-----------------------
			reset_term(old_flags);			// DRIE
			//----------------------------
		}
		//----------------------------
		inline void conio_end()
		{
			_setcursortype(_NORMALCURSOR);
			//-DRIE-------------------
			Term_Data old_flags;		// DRIE
			set_icanon_echo(old_flags);	// DRIE
			//------------------------
		}
		//----------------------------
		inline unsigned conio_init()
		{
			static bool init = true;
			if (init) {
				init = false;
				//------------------------
				std::cerr.sync_with_stdio();
				std::cout.sync_with_stdio();
				std::cin.sync_with_stdio();
				//--------------------
				//disable_input_buffer();
				//--------------------
				//assert(esta_ordenado());
				//-DRIE---------------
				Term_Data old_flags;			// DRIE
				reset_icanon_echo(old_flags);	// DRIE
				//--------------------
				ini_aleatorio();
				text_info info; gettextinfo(info);
				std::atexit(conio_end);
				//------------------------
				//unsigned nf, nc;
				//screen_size(nf, nc);
				//------------------------
			}
			return 1;
		}
		static const unsigned trigger_init = conio_init();
	}// namespace impl_
	//---------------------------------------------------------------------
} //namespace conio
#endif //  defined __WIN32__ OR __unix__ OR __APPLE__
namespace ioconsole {
	//--------------------------------
	//--------------------------------
	struct ConsoleIO {
		ConsoleIO(){}
		//----------------------------
		inline bool fail() const { return std::cout.fail() || std::cin.fail(); }
		inline void clear() const { std::cout.clear(); std::cin.clear(); }
		//----------------------------
		inline std::ios::fmtflags flags() const { return std::cout.flags(); }
		inline std::ios::fmtflags flags(std::ios::fmtflags f) const { return std::cout.flags(f); }
		inline void unsetf(std::ios::fmtflags f) const { std::cout.unsetf(f); }
		inline std::ios::fmtflags setf(std::ios::fmtflags f) const { return std::cout.setf(f); }
		inline std::ios::fmtflags setf(std::ios::fmtflags f, std::ios::fmtflags m) const { return std::cout.setf(f, m); }
		//----------------------------
		inline void disable_input_buffer() const { conio::disable_input_buffer(); }
		//----------------------------
		inline void flush() const { std::cout << std::flush; }
		inline void endl() const { std::cout << std::endl; }
		inline void dec() const { std::cout << std::dec; }
		inline void hex() const { std::cout << std::hex; }
		inline void oct() const { std::cout << std::oct; }
		inline void boolalpha() const { std::cout << std::boolalpha; }
		inline void precision(unsigned p) const { std::cout.precision(p); }
		inline void width(unsigned w) const { std::cout.width(w); }
		inline void fill(char f) const { std::cout.fill(f); }
		//----------------------------
		inline void get(char& x) const { conio::_impl_::cgetc(x); }
		inline void ungetch(char c) const { conio::ungetch(c); }
		inline bool kbhit() const { return conio::kbhit(); }
		inline int  getkey() const { return conio::getkey(); }
		inline void getkey(int& k) const { k = conio::getkey(); }
		inline void getkey(unsigned& k) const { k = conio::getkey(); }
		//----------------------------
		inline void no_cursor() const { conio::_setcursortype(conio::_NOCURSOR); }
		inline void solid_cursor() const { conio::_setcursortype(conio::_SOLIDCURSOR); }
		inline void normal_cursor() const { conio::_setcursortype(conio::_NORMALCURSOR); }
		inline void clear_line() const { conio::clreol(); }
		inline void clear_screen() const { conio::clrscr(); }
		inline void insert_line() const { conio::insline(); }
		inline void delete_line() const { conio::delline(); }
		inline void intense_video() const { conio::intensevideo(); }
		inline void high_video() const { conio::highvideo(); }
		inline void low_video() const { conio::lowvideo(); }
		inline void normal_video() const { conio::normvideo(); }
		inline void blink_video() const { conio::blinkvideo(); }
		inline void no_blink_video() const { conio::noblinkvideo(); }
		//----------------------------
	};
	static const ConsoleIO cio;
	//--------------------------------
	inline void flush(const ConsoleIO& c) { c.flush(); }
	inline void endl(const ConsoleIO& c) { c.endl(); }
	inline void dec(const ConsoleIO& c) { c.dec(); }
	inline void hex(const ConsoleIO& c) { c.hex(); }
	inline void oct(const ConsoleIO& c) { c.oct(); }
	inline void boolalpha(const ConsoleIO& c) { c.boolalpha(); }
	//--------------------------------
	inline void ws(const ConsoleIO&, const ConsoleIO&) { conio::_impl_::cinws(); }
	inline void ignore(const ConsoleIO&, const ConsoleIO&) { std::cin.ignore(100000,'\n'); }
	inline void disable_buffer(const ConsoleIO&c, const ConsoleIO&) { c.disable_input_buffer(); }
	//--------------------------------
	inline void no_cursor(const ConsoleIO& c) { c.no_cursor(); }
	inline void solid_cursor(const ConsoleIO& c) { c.solid_cursor(); }
	inline void normal_cursor(const ConsoleIO& c) { c.normal_cursor(); }
	inline void clear_line(const ConsoleIO& c) { c.clear_line(); }
	inline void clear_screen(const ConsoleIO& c) { c.clear_screen(); }
	inline void insert_line(const ConsoleIO& c) { c.insert_line(); }
	inline void delete_line(const ConsoleIO& c) { c.delete_line(); }
	inline void intense_video(const ConsoleIO& c) { c.intense_video(); }
	inline void high_video(const ConsoleIO& c) { c.high_video(); }
	inline void low_video(const ConsoleIO& c) { c.low_video(); }
	inline void normal_video(const ConsoleIO& c) { c.normal_video(); }
	inline void blink_video(const ConsoleIO& c) { c.blink_video(); }
	inline void no_blink_video(const ConsoleIO& c) { c.no_blink_video(); }
	//--------------------------------
	struct GetKey {
		unsigned& _k;
		GetKey(unsigned& k) : _k(k) {}
	};
	//inline GetKey getkey(unsigned& k) { return GetKey(k); }
	inline GetKey key(unsigned& k) { return GetKey(k); }
	struct WhereXY {
		unsigned& _x;
		unsigned& _y;
		WhereXY(unsigned& x, unsigned& y) : _x(x), _y(y) {}
	};
	inline WhereXY wherexy(unsigned& x, unsigned& y) { return WhereXY(x, y); }
	struct CursorXY {
		unsigned _x;
		unsigned _y;
		CursorXY(unsigned x, unsigned y) : _x(x), _y(y) {}
	};
	inline CursorXY cursorxy(unsigned x, unsigned y) { return CursorXY(x, y); }
	struct Color {
		unsigned frgnd;
		unsigned bckgnd;
		Color(unsigned f, unsigned b=-1) : frgnd(f), bckgnd(b) {}
	};
	inline Color color(unsigned f, unsigned b=-1) { return Color(f, b); }
	struct BgColor {
		unsigned bckgnd;
		BgColor(unsigned b) : bckgnd(b) {}
	};
	inline BgColor bgcolor(unsigned b) { return BgColor(b); }
	struct SetPrec {
		unsigned _p;
		SetPrec(unsigned p) : _p(p) {}
		SetPrec(const std::_Setprecision& p) : _p(p._M_n) {}
	};
	inline SetPrec setprecision(unsigned p) { return SetPrec(p); }
	struct SetW {
		unsigned _w;
		SetW(unsigned w) : _w(w) {}
		SetW(const std::_Setw& w) : _w(w._M_n) {}
	};
	inline SetW setw(unsigned w) { return SetW(w); }
	struct SetFill {
		char _f;
		SetFill(char f) : _f(f) {}
		SetFill(const std::_Setfill<char>& f) : _f(f._M_c) {}
	};
	inline SetFill setfill(char f) { return SetFill(f); }
	//--------------------------------
	inline const ConsoleIO& operator>>(const ConsoleIO& c, conio::text_info& x) {
		conio::gettextinfo(&x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, const GetKey& x) {
		x._k = conio::getkey();
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, const WhereXY& x) {
		conio::_impl_::wherexy(x._x, x._y);
		return c;
	}
	//--------------------------------
	inline const ConsoleIO& operator>>(const ConsoleIO& c, void (*f)(const ConsoleIO&,const ConsoleIO&)) {
		f(c,c);
		return c;
	}
	//--------------------------------
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const CursorXY& x) {
		conio::gotoxy(x._x, x._y);
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, void (*f)(const ConsoleIO&)) {
		f(c);
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const Color& x) {
		if (x.bckgnd == unsigned(-1)) {
			conio::textcolor(x.frgnd);
		} else {
			conio::textattr((0x0F&x.frgnd) | ((0x0F&x.bckgnd)<<4));
		}
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const BgColor& x) {
		conio::textbackground(x.bckgnd);
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const SetPrec& x) {
		c.precision(x._p);
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const SetW& x) {
		c.width(x._w);
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const SetFill& x) {
		c.fill(x._f);
		return c;
	}
	//--------------------------------
	inline const ConsoleIO& operator>>(const ConsoleIO& c, char& x) {
		//conio::cscanf(" %c", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, short& x) {
		//conio::cscanf(" %hd", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, unsigned short& x) {
		//conio::cscanf(" %hu", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, int& x) {
		//conio::cscanf(" %d", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, unsigned& x) {
		//conio::cscanf(" %u", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, long& x) {
		//conio::cscanf(" %ld", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, unsigned long& x) {
		//conio::cscanf(" %lu", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, float& x) {
		//conio::cscanf(" %f", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, double& x) {
		//conio::cscanf(" %lf", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, long double& x) {
		//conio::cscanf(" %Lf", &x);
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& operator>>(const ConsoleIO& c, std::string& x) {
		conio::_impl_::cgetx(x);
		return c;
	}
	inline const ConsoleIO& getline(const ConsoleIO& c, std::string& x) {
		conio::cgets(x);
		return c;
	}
	//--------------------------------
	inline const ConsoleIO& operator<<(const ConsoleIO& c, char x) {
		//conio::cprintf("%c", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, short x) {
		//conio::cprintf("%hd", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, unsigned short x) {
		//conio::cprintf("%hu", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, int x) {
		//conio::cprintf("%d", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, unsigned x) {
		//conio::cprintf("%u", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, long x) {
		//conio::cprintf("%ld", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, unsigned long x) {
		//conio::cprintf("%lu", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, float x) {
		//conio::cprintf("%g", double(x));
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, double x) {
		//conio::cprintf("%g", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, long double x) {
		//conio::cprintf("%Lg", x);
		std::cout << x;
		return c;
	}
	inline const ConsoleIO& operator<<(const ConsoleIO& c, const std::string& x) {
		//conio::cputs(x);
		std::cout << x;
		return c;
	}
	//--------------------------------
	using namespace conio_base;
	using conio::clear;
	using conio::pausa;
	using conio::msleep;
	//--------------------------------
}// namespace ioconsole
using namespace ioconsole;
#endif
