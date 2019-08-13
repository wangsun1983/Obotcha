#ifndef __NUMBER_FORMATTER_HPP__
#define __NUMBER_FORMATTER_HPP__

#include <vector>
#include <algorithm>
#include <sys/time.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "DateTime.hpp"

using namespace std;

#define MAX_INT_STRING_LEN 65
#define MAX_FLT_STRING_LEN 780

namespace obotcha {

class Ptr
		/// Utility char pointer wrapper class.
		/// Class ensures increment/decrement remain within boundaries.
	{
	public:
		Ptr(char* ptr, std::size_t offset): _beg(ptr), _cur(ptr), _end(ptr + offset)
		{
		}
	
		char*& operator ++ () // prefix
		{
			checkBounds(_cur + 1);
			return ++_cur;
		}

		char* operator ++ (int) // postfix
		{
			checkBounds(_cur + 1);
			char* tmp = _cur++;
			return tmp;
		}
	
		char*& operator -- () // prefix
		{
			checkBounds(_cur - 1);
			return --_cur;
		}

		char* operator -- (int) // postfix
		{
			checkBounds(_cur - 1);
			char* tmp = _cur--;
			return tmp;
		}

		char*& operator += (int incr)
		{
			checkBounds(_cur + incr);
			return _cur += incr;
		}

		char*& operator -= (int decr)
		{
			checkBounds(_cur - decr);
			return _cur -= decr;
		}

		operator char* () const
		{
			return _cur;
		}

		std::size_t span() const
		{
			return _end - _beg;
		}

	private:
		bool checkBounds(char* ptr)
		{
			if (ptr > _end) {
				return false;
			};
			return true;
		}

		const char* _beg;
		char*       _cur;
		const char* _end;
};

DECLARE_SIMPLE_CLASS(NumberFormatter) {

public:
    static String format(const int value);
		/// Formats an integer value in decimal notation.

	static String format(const int value, const int width);
		/// Formats an integer value in decimal notation,
		/// right justified in a field having at least
		/// the specified width.

	static String format0(const int value, const int width);
		/// Formats an integer value in decimal notation,
		/// right justified and zero-padded in a field
		/// having at least the specified width.

	static String formatHex(const int value, const bool prefix = false);
		/// Formats an int value in hexadecimal notation.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.
		/// The value is treated as unsigned.

	static String formatHex(const int value, const int width, const bool prefix = false);
		/// Formats a int value in hexadecimal notation,
		/// right justified and zero-padded in
		/// a field having at least the specified width.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.
		/// The value is treated as unsigned.

	static String format(const unsigned value);
		/// Formats an unsigned int value in decimal notation.

	static String format(const unsigned value, const int width);
		/// Formats an unsigned long int in decimal notation,
		/// right justified in a field having at least the
		/// specified width.

	static String format0(const unsigned int value, const int width);
		/// Formats an unsigned int value in decimal notation,
		/// right justified and zero-padded in a field having at
		/// least the specified width.

	static String formatHex(const unsigned value, const bool prefix = false);
		/// Formats an unsigned int value in hexadecimal notation.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.

	static String formatHex(const unsigned value, const int width, const bool prefix = false);
		/// Formats a int value in hexadecimal notation,
		/// right justified and zero-padded in
		/// a field having at least the specified width.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.

	static String format(const long value);
		/// Formats a long value in decimal notation.

	static String format(const long value, const int width);
		/// Formats a long value in decimal notation,
		/// right justified in a field having at least the
		/// specified width.

	static String format0(const long value, const int width);
		/// Formats a long value in decimal notation,
		/// right justified and zero-padded in a field
		/// having at least the specified width.

	static String formatHex(const long value, const bool prefix = false);
		/// Formats an unsigned long value in hexadecimal notation.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.
		/// The value is treated as unsigned.

	static String formatHex(const long value, const int width, const bool prefix = false);
		/// Formats an unsigned long value in hexadecimal notation,
		/// right justified and zero-padded in a field having at least the
		/// specified width.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.
		/// The value is treated as unsigned.

	static String format(const unsigned long value);
		/// Formats an unsigned long value in decimal notation.

	static String format(const unsigned long value, const int width);
		/// Formats an unsigned long value in decimal notation,
		/// right justified in a field having at least the specified
		/// width.

	static String format0(const unsigned long value, const int width);
		/// Formats an unsigned long value in decimal notation,
		/// right justified and zero-padded
		/// in a field having at least the specified width.

	static String formatHex(const unsigned long value, const bool prefix = false);
		/// Formats an unsigned long value in hexadecimal notation.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.

	static String formatHex(const unsigned long value, const int width, const bool prefix = false);
		/// Formats an unsigned long value in hexadecimal notation,
		/// right justified and zero-padded in a field having at least the
		/// specified width.
		/// If prefix is true, "0x" prefix is prepended to the
		/// resulting string.

	static String format(const float value);
		/// Formats a float value in decimal floating-point notation,
		/// according to std::printf's %g format with a precision of 8 fractional digits.

	static String format(const float value, const int precision);
		/// Formats a double value in decimal floating-point notation,
		/// according to std::printf's %f format with the given precision.

	static String format(const float value, const int width, const int precision);
		/// Formats a double value in decimal floating-point notation,
		/// right justified in a field of the specified width,
		/// with the number of fractional digits given in precision.

	static String format(const double value);
		/// Formats a double value in decimal floating-point notation,
		/// according to std::printf's %g format with a precision of 16 fractional digits.

	static String format(const double value, const int precision);
		/// Formats a double value in decimal floating-point notation,
		/// according to std::printf's %f format with the given precision.

	static String format(const double value, const int width, const int precision);
		/// Formats a double value in decimal floating-point notation,
		/// right justified in a field of the specified width,
		/// with the number of fractional digits given in precision.

	static String format(const void* ptr);
		/// Formats a pointer in an eight (32-bit architectures) or
		/// sixteen (64-bit architectures) characters wide
		/// field in hexadecimal notation.

private:
    static std::string intToStr (int number, 
                                unsigned short base, 
                                bool prefix = false, 
                                int width = -1, 
                                char fill = ' ', 
                                char thSep = 0);

    static bool intToStr(int value,
                  unsigned short base,
	              char* result,
	              std::size_t& size,
	              bool prefix = false,
	              int width = -1,
	              char fill = ' ',
	              char thSep = 0);

    static std::string uIntToStr (long number, 
                                  unsigned short base, 
                                  bool prefix = false, 
                                  int width = -1,
                                  char fill = ' ', 
                                  char thSep = 0);

    static bool uIntToStr(long value,
	                      unsigned short base,
	                      char* result,
	                      std::size_t& size,
	                      bool prefix = false,
	                      int width = -1,
	                      char fill = ' ',
	                      char thSep = 0);

    static std::string floatToStr(float value, 
                                  const int precision = -1, 
                                  const int width = 0, 
                                  const char thSep = 0, 
                                  char decSep = 0);
    
	static std::string doubleToStr(double value,
                                    int precision = -1,
                                    int width = 0,
                                    char thSep = 0,
                                    char decSep = 0);


    static std::string replaceInPlace(std::string& str, 
	                           const std::string::value_type from, 
							   const std::string::value_type to = 0, 
							   std::string::size_type start = 0);


    static void insertThousandSep(std::string& str, 
	                              const char thSep, 
								  const char decSep);

	static void pad(std::string& str, 
	                                  const int precision, 
									  const int width, 
									  const char prefix = ' ' , 
									  const char decSep = '.');

};

}
#endif
