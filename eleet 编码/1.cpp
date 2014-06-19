#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char source[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
	'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z'
};

const char dest[] = {
	'@', '6', '[', 'd', '3', 'f', '9', 'h',
	'!', 'j', 'k', '1', 'm', 'n', '0', 'p',
	'q', 'r', '5', '+', 'u', 'v', 'w', 'x',
	'y', 'z',
	'4', '8', 'C', ')', '&', 'F', 'G', '#',
	'|', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', '2', 'S', '7', 'U', 'V', 'W', 'X',
	'Y', 'Z'
};

int get_cursor( int argc, char ch ) {
	int flag = -1;
	if ( argc == 2 ) {
		for ( int i = 0; i < ( int ) strlen( source ); ++i ) if ( source[ i ] == ch ) {
			flag = i;
			break;
		}
	} else if ( argc == 3 ) {
		for ( int i = 0; i < ( int ) strlen( dest ); ++i ) if ( dest[ i ] == ch ) {
			flag = i;
			break;
		}
	}
	return flag;
}

int main( int argc, char* argv[] ) {
	if ( argc != 2 && argc != 3 ) {
		printf( "format error\n" );
		exit( 0 );
	}

	FILE* fp = fopen( "eleet.txt", "a+" );

	if ( argc == 2 ) {
		int length = strlen( argv[ 1 ] );
		char* param = ( char* ) malloc( length * sizeof( char ) );
		strcpy( param, argv[ 1 ] );

		for ( int i = 0; i < length; ++i ) {
			int cursor = get_cursor( argc, param[ i ] );
			if ( cursor != -1 ) { 
				param[ i ] = dest[ cursor ];
			}
		}

		printf( "%s\n", param );
		fprintf( fp, "%s\n", param );
	} else if ( argc == 3 ) {
		int length = strlen( argv[ 2 ] );
		char* param = ( char* ) malloc( length * sizeof( char ) );
		strcpy( param, argv[ 2 ] );

		for ( int i = 0; i < length; ++i ) {
			int cursor = get_cursor( argc, param[ i ] );
			if ( cursor != -1 ) { 
				param[ i ] = source[ cursor ];
			}
		}

		printf( "%s\n", param );
		fprintf( fp, "%s\n", param );
	}

	fclose( fp );
	
	return 0;
}
