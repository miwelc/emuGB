#ifndef _TIPOS_H_
#define _TIPOS_H_
#include <climits>

#if UCHAR_MAX > 0xFF
	#error Se necesita disponer de variables de 8bits pada poder compilar
#endif
typedef unsigned char byte;
typedef signed char signoB;

#if UINT_MAX > 0xFFFF
	#if USHRT_MAX > 0xFFFF
		#error Se necesita disponer de variables de 16bits pada poder compilar
	#endif
	typedef unsigned short word;
	typedef signed short signoW;
#else
	typedef unsigned int word;
	typedef signed int signoW;
#endif


#endif
