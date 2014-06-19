#include <windows.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <queue>
using	namespace	std;

struct point_ {
	int x, y;
	point_() {}
	point_( int x, int y ) : x( x ), y( y ) {}
	point_& operator=( point_ p ) {
		x = p.x;
		y = p.y;
		return *this;
	}
};

/* =============================================== */
HWND hWnd;

void getHWND( char* argv[] ) {
	char arg[ 200 ] = { 0 };
	arg[ 0 ] = '\"';
	strcpy( arg + 1, argv[ 0 ] );
	int len = int( strlen( arg ) );
	arg[ len ] = '\"';

	hWnd = FindWindow( NULL, arg ); // 找到程序运行窗口的句柄
}

void drawLine( point_ p1, point_ p2 ) {
	HDC hDC = GetDC( hWnd ); // 通过窗口句柄得到该窗口的设备场境句柄
	HPEN hPen, hOldPen; // 画笔
	hPen = CreatePen( PS_SOLID, 2, 0x00ff00 ); // 生成绿色画笔
	hOldPen = ( HPEN )SelectObject( hDC, hPen ); // 把画笔引入设备
	MoveToEx( hDC, p1.x, p1.y, NULL ); // 设置画线起点
	LineTo( hDC, p2.x, p2.y ); // 画到终点
	SelectObject( hDC, hOldPen );
}

void eraseLine( point_ p1, point_ p2 ) {
	HDC hDC = GetDC( hWnd ); // 通过窗口句柄得到该窗口的设备场境句柄
	HPEN hPen, hOldPen; // 画笔
	hPen = CreatePen( PS_SOLID, 2, 0x000000 ); // 白色
	hOldPen = ( HPEN )SelectObject( hDC, hPen ); // 把画笔引入设备
	MoveToEx( hDC, p1.x, p1.y, NULL ); // 设置画线起点
	LineTo( hDC, p2.x, p2.y ); // 画到终点

	MoveToEx( hDC, p1.x + 1, p1.y, NULL ); // 设置画线起点
	LineTo( hDC, p2.x + 1, p2.y ); // 画到终点

	MoveToEx( hDC, p1.x - 1, p1.y, NULL ); // 设置画线起点
	LineTo( hDC, p2.x - 1, p2.y ); // 画到终点

	MoveToEx( hDC, p1.x, p1.y + 1, NULL ); // 设置画线起点
	LineTo( hDC, p2.x, p2.y + 1 ); // 画到终点

	MoveToEx( hDC, p1.x, p1.y - 1, NULL ); // 设置画线起点
	LineTo( hDC, p2.x, p2.y - 1 ); // 画到终点

	SelectObject( hDC, hOldPen );
}
/* =============================================== */

const point_ init_p1( 20, 100 );
const point_ init_p2( 620, 100 );

#define PUSH( point1, point2, th ) \
	point_queue##th.push( pair< point_, point_ >( point1, point2 ) )

void getThreeNewPoint( const point_& ps, const point_& pe, point_& p1, point_& p2, point_& p3 ) {
	double x1 = ( pe.x + 2 * ps.x ) / 3.0;
	double y1 = ( pe.y + 2 * ps.y ) / 3.0;
	p1 = point_( x1, y1 );

	double x3 = ( ps.x + 2 * pe.x ) / 3.0;
	double y3 = ( ps.y + 2 * pe.y ) / 3.0;
	p3 = point_( x3, y3 );

	double xt = ( pe.x + ps.x ) / 2.0;
	double yt = ( pe.y + ps.y ) / 2.0;

	double k = ( double )( pe.y - ps.y ) / ( pe.x - ps.x );
	double l = sqrt( ( pe.y - ps.y ) * ( pe.y - ps.y ) + ( pe.x - ps.x ) * ( pe.x - ps.x ) ) / 3;

	double x2, y2;
	if ( k == 0 ) {
		x2 = xt;
		y2 = sqrt( 3 ) / 2.0 * l + yt;
	} else {
		x2 = -sqrt( 3 ) / 2.0 * k / sqrt( k * k + 1 ) * l + xt;
		y2 = ( xt - x2 ) / k + yt;
	}
	p2 = point_( x2, y2 );
}

void koch( int n ) {
	queue< pair< point_, point_ > > point_queue1;
	queue< pair< point_, point_ > > point_queue2;
	PUSH( init_p1, init_p2, 1 );
	drawLine( init_p1, init_p2 );
	for ( int i = 0; i < n; ++i ) {
		if ( i & 1 ) {
			while ( !point_queue2.empty() ) {
				point_ ps = point_queue2.front().first;
				point_ pe = point_queue2.front().second;
				point_queue2.pop();

				point_ p1, p2, p3;
				getThreeNewPoint( ps, pe, p1, p2, p3 );
				PUSH( ps, p1, 1 );
				PUSH( p1, p2, 1 );
				PUSH( p2, p3, 1 );
				PUSH( p3, pe, 1 );

				drawLine( ps, p1 );
				drawLine( p1, p2 );
				drawLine( p2, p3 );
				drawLine( p3, pe );

				eraseLine( p1, p3 );
			}
		} else {
			while ( !point_queue1.empty() ) {
				point_ ps = point_queue1.front().first;
				point_ pe = point_queue1.front().second;
				point_queue1.pop();

				point_ p1, p2, p3;
				getThreeNewPoint( ps, pe, p1, p2, p3 );
				PUSH( ps, p1, 2 );
				PUSH( p1, p2, 2 );
				PUSH( p2, p3, 2 );
				PUSH( p3, pe, 2 );

				drawLine( ps, p1 );
				drawLine( p1, p2 );
				drawLine( p2, p3 );
				drawLine( p3, pe );

				eraseLine( p1, p3 );
			}
		}
	}
}

int main( int argc, char* argv[] ) {
	getHWND( argv );
	while ( true ) {
		int n;
		cin >> n;
		koch( n );
		system( "pause" );
		system( "cls" );
	}
	
	return 0;
}