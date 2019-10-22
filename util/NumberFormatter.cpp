#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <cmath>
#include <sstream>
#include <memory>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "NumberFormatter.hpp"

using namespace std;

namespace obotcha {

String _NumberFormatter::format(const int value) {
    std::string str = intToStr(value, 10);
	return createString(str);
}

String _NumberFormatter::format(const int value, const int width) {
    std::string str = intToStr(value, 10, false, width, ' ');
	return createString(str);
}
		
String _NumberFormatter::format0(const int value, const int width) {
    std::string str = intToStr(value, 10, false, width, '0');
	return createString(str);
}
		
String _NumberFormatter::formatHex(const int value, const bool prefix) {
    std::string str = uIntToStr(static_cast<unsigned int>(value), 0x10, prefix);
    return createString(str);
}
		
String _NumberFormatter::formatHex(const int value, const int width, const bool prefix) {
    std::string str = uIntToStr(static_cast<unsigned int>(value), 0x10, prefix, width, '0');
	return createString(str);
}
		
String _NumberFormatter::format(const unsigned value) {
    std::string str = uIntToStr(value, 10);
	return createString(str);
}
		
String _NumberFormatter::format(const unsigned value, const int width) {
    std::string str = uIntToStr(value, 10, false, width, ' ');
	return createString(str);
}

String _NumberFormatter::format0(const unsigned int value, const int width) {
    std::string str = uIntToStr(value, 10, false, width, '0');
	return createString(str);
}
		
String _NumberFormatter::formatHex(const unsigned value, const bool prefix) {
    std::string str = uIntToStr(value, 0x10, prefix);
	return createString(str);
}
		
String _NumberFormatter::formatHex(const unsigned value, const int width, const bool prefix) {
    std::string str = uIntToStr(value, 0x10, prefix, width, '0');
	return createString(str);
}

String _NumberFormatter::format(const long value) {
    std::string str = intToStr(value, 10);
	return createString(str);
}

String _NumberFormatter::format(const long value, const int width) {
    std::string str = intToStr(value, 10, false, width, ' ');
	return createString(str);
}

String _NumberFormatter::format0(const long value, const int width) {
    std::string str = intToStr(value, 10, false, width, '0');
	return createString(str);
}

String _NumberFormatter::formatHex(const long value, const bool prefix) {
    std::string str = uIntToStr(static_cast<unsigned long>(value), 0x10, prefix);
	return createString(str);
}

String _NumberFormatter::formatHex(const long value, const int width, const bool prefix) {
    std::string str = uIntToStr(static_cast<unsigned long>(value), 0x10, prefix, width, '0');
	return createString(str);
}

String _NumberFormatter::format(const unsigned long value) {
    std::string str = uIntToStr(value, 10);
	return createString(str);
}

String _NumberFormatter::format(const unsigned long value, const int width){
	std::string str = uIntToStr(value, 10, false, width, ' ');
	return createString(str);
}

String _NumberFormatter::format0(const unsigned long value, const int width) {
    std::string str = uIntToStr(value, 10, false, width, '0');
	return createString(str);
}

String _NumberFormatter::formatHex(const unsigned long value, const bool prefix) {
    std::string str = uIntToStr(value, 0x10, prefix);
	return createString(str);
}

String _NumberFormatter::formatHex(const unsigned long value, const int width, const bool prefix){
	std::string str = uIntToStr(value, 0x10, prefix, width, '0');
	return createString(str);
}

String _NumberFormatter::format(const float value) {
    std::string str = floatToStr(value);
	return createString(str);
}

String _NumberFormatter::format(const float value, const int precision){
    std::string str = floatToStr(value, precision);
	return createString(str);
}

String _NumberFormatter::format(const float value, const int width, const int precision) {
    std::string str = floatToStr(value, precision,width);
	return createString(str);
}

String _NumberFormatter::format(const double value) {
    std::string str = doubleToStr(value);
	return createString(str);
}

String _NumberFormatter::format(const double value, const int precision) {
    std::string str = doubleToStr(value,precision);
	return createString(str);
}

String _NumberFormatter::format(const double value, const int width, const int precision){
	std::string str = doubleToStr(value,precision,width);
	return createString(str);
}

String _NumberFormatter::format(const void* ptr) {
    //TODO
	return nullptr;
}

std::string _NumberFormatter::intToStr (int number, 
                                unsigned short base, 
                                bool prefix, 
                                int width, 
                                char fill, 
                                char thSep) {
    std::string result;
	char res[MAX_INT_STRING_LEN] = {0};
	std::size_t size = MAX_INT_STRING_LEN;
	bool ret = intToStr(number, base, res, size, prefix, width, fill, thSep);
	if (ret) result.assign(res, size);
	return result;
}

bool _NumberFormatter::intToStr(int value,
                  unsigned short base,
	              char* result,
	              std::size_t& size,
	              bool prefix,
	              int width,
	              char fill,
	              char thSep) {
    if (base < 2 || base > 0x10)
	{
		*result = '\0';
		return false;
	}

	Ptr ptr(result, size);
	int thCount = 0;
	int tmpVal;
	do
	{
		tmpVal = value;
		value /= base;
		*ptr++ = "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
		if (thSep && (base == 10) && (++thCount == 3))
		{
			*ptr++ = thSep;
			thCount = 0;
		}
	} while (value);

	if ('0' == fill)
	{
		if (tmpVal < 0) --width;
		if (prefix && base == 010) --width;
		if (prefix && base == 0x10) width -= 2;
		while ((ptr - result) < width) *ptr++ = fill;
	}

	if (prefix && base == 010) *ptr++ = '0';
	else if (prefix && base == 0x10)
	{
		*ptr++ = 'x';
		*ptr++ = '0';
	}

	if (tmpVal < 0) *ptr++ = '-';

	if ('0' != fill)
	{
		while ((ptr - result) < width) *ptr++ = fill;
	}

	size = ptr - result;
	//poco_assert_dbg (size <= ptr.span());
	//poco_assert_dbg ((-1 == width) || (size >= size_t(width)));
	*ptr-- = '\0';

	char* ptrr = result;
	char tmp;
	while(ptrr < ptr)
	{
		 tmp    = *ptr;
		*ptr--  = *ptrr;
		*ptrr++ = tmp;
	}

	return true;
}

bool _NumberFormatter::uIntToStr(long value,
	                      unsigned short base,
	                      char* result,
	                      std::size_t& size,
	                      bool prefix,
	                      int width,
	                      char fill,
	                      char thSep) {
    if (base < 2 || base > 0x10)
	{
		*result = '\0';
		return false;
	}
	
	Ptr ptr(result, size);
	int thCount = 0;
	uint64_t tmpVal;
	do
	{
		tmpVal = value;
		value /= base;
		*ptr++ = "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
		if (thSep && (base == 10) && (++thCount == 3))
		{
			*ptr++ = thSep;
			thCount = 0;
		}
	} while (value);
	
	if ('0' == fill)
	{
		if (prefix && base == 010) --width;
		if (prefix && base == 0x10) width -= 2;
		while ((ptr - result) < width) *ptr++ = fill;
	}
	
	if (prefix && base == 010) *ptr++ = '0';
	else if (prefix && base == 0x10)
	{
		*ptr++ = 'x';
		*ptr++ = '0';
	}
	
	if ('0' != fill)
	{
		while ((ptr - result) < width) *ptr++ = fill;
	}
	
	size = ptr - result;
	//poco_assert_dbg (size <= ptr.span());
	//poco_assert_dbg ((-1 == width) || (size >= size_t(width)));
	*ptr-- = '\0';
	
	char* ptrr = result;
	char tmp;
	while(ptrr < ptr)
	{
		tmp    = *ptr;
		*ptr--  = *ptrr;
		*ptrr++ = tmp;
	}
	
	return true;
}

std::string _NumberFormatter::uIntToStr (long number, 
                                  unsigned short base, 
                                  bool prefix, 
                                  int width,
                                  char fill, 
                                  char thSep) {
    std::string result;
	char res[MAX_INT_STRING_LEN] = {0};
	std::size_t size = MAX_INT_STRING_LEN;
	const bool ret = uIntToStr(number, base, res, size, prefix, width, fill, thSep);
	if (ret) result.assign(res, size);
	return result;
}

std::string _NumberFormatter::floatToStr(float value, 
                                  const int precision, 
                                  const int width, 
                                  const char thSep, 
                                  char decSep) {
    std::string result;
    if (!decSep) decSep = '.';
    if (precision == 0) value = std::floor(value);

    std::stringstream ss;
    ss<<value;

    result = ss.str();

    if (decSep && (decSep != '.') && (result.find('.') != std::string::npos))
        replaceInPlace(result, '.', decSep);

    if (thSep) insertThousandSep(result, thSep, decSep);
    if (precision > 0 || width) pad(result, precision, width, ' ', decSep ? decSep : '.');
    return result;
}

std::string _NumberFormatter::replaceInPlace(std::string& str, 
                           const std::string::value_type from, 
                           const std::string::value_type to, 
						   std::string::size_type start) {
	if (from == to) return str;

	typename std::string::size_type pos = 0;
	do
	{
		pos = str.find(from, start);
		if (pos != std::string::npos)
		{
			if (to) str[pos] = to;
			else str.erase(pos, 1);
		}
	} while (pos != std::string::npos);

	return str;
}

void _NumberFormatter::insertThousandSep(std::string& str, const char thSep, const char decSep) {
    if (str.size() == 0) return;

	std::string::size_type exPos = str.find('e');
	if (exPos == std::string::npos) exPos = str.find('E');
	const std::string::size_type decPos = str.find(decSep);
	// there's no rinsert, using forward iterator to go backwards
	std::string::iterator it = str.end();
	if (exPos != std::string::npos) it -= str.size() - exPos;

	if (decPos != std::string::npos)
	{
		while (it != str.begin())
		{
			--it;
			if (*it == decSep) break;
		}
	}
	int thCount = 0;
	if (it == str.end()) --it;
	for (; it != str.begin();)
	{
		const std::string::iterator pos = it;
		const std::string::value_type chr = *it;
		const std::string::value_type prevChr = *--it;

		if (!std::isdigit(chr)) continue;

		if (++thCount == 3 && std::isdigit(prevChr))
			it = str.insert(pos, thSep);

		if (thCount == 3) thCount = 0;
	}
}

void _NumberFormatter::pad(std::string& str, 
                           const int precision, 
						   const int width, 
						   const char prefix, 
						   const char decSep)
	/// Pads the string with prefix space and postfix 0.
	/// Alternative prefix (e.g. zero instead of space) can be supplied by caller.
	/// Used only internally.
{
	// these cases should never happen, if they do, it's a library bug
	//poco_assert_dbg (precision > 0);
	//poco_assert_dbg (str.length());

	std::string::size_type decSepPos = str.find(decSep);
	if (decSepPos == std::string::npos)
	{
		str.append(1, '.');
		decSepPos = str.size() - 1;
	}

	std::string::size_type frac = str.length() - decSepPos - 1;

	const std::string::size_type ePos = str.find_first_of("eE");
	std::unique_ptr<std::string> eStr;
	if (ePos != std::string::npos)
	{
		eStr.reset(new std::string(str.substr(ePos, std::string::npos)));
		frac -= eStr->length();
		str = str.substr(0, str.length() - eStr->length());
	}

	if (frac != precision)
	{
		if (frac < precision)
		{
			str.append(precision - frac, '0');
		}
		else if ((frac > precision) && (decSepPos != std::string::npos))
		{
			int pos = static_cast<int>(decSepPos) + 1 + precision;
			if (str[pos] >= '5') // we must round up
			{
				char carry = 0;
				if(str[--pos] == '9')
				{
					str[pos] = '0';
					carry = 1;
				}
				else
				{
					++str[pos];
					carry = 0;
				}
				while (--pos >= 0)
				{
					if(str[pos] == decSep) continue;
					if(carry)
					{
						if((str[pos] + carry) <= '9')
						{
							++str[pos];
							carry = 0;
						}
						else
						{
							str[pos] = '0';
							carry = 1;
						}
					}
				}
				if (carry) str.insert(str.begin(), 1, '1');
			}
			str = str.substr(0, decSepPos + 1 + precision);
		}
	}

	if (eStr.get()) str += *eStr;

	if (width && (str.length() < width)) str.insert(str.begin(), width - str.length(), prefix);
}

std::string _NumberFormatter::doubleToStr(double value,
                                          int precision,
                                          int width,
                                          char thSep,
                                          char decSep) {
    std::string result;
    if (!decSep) decSep = '.';
    if (precision == 0) value = std::floor(value);

    std::stringstream ss;
    ss<<value;

    result = ss.str();

    if (decSep && (decSep != '.') && (result.find('.') != std::string::npos))
        replaceInPlace(result, '.', decSep);

    if (thSep) insertThousandSep(result, thSep, decSep);
    if (precision > 0 || width) pad(result, precision, width, ' ', decSep ? decSep : '.');
    return result;
}

}
