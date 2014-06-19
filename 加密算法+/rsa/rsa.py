#!/usr/bin/python

class rsa:
    def __init__( self, p, q ):
        self.p = p;
        self.q = q;

    def __get_list__( self ):
        e_list = []
        for n in range( 2, self.phi ):
            if self.__gcd__( self.phi, n ) == 1:
                e_list.append( n )
        return e_list

    def __extend_Eulid__( self ):
        def __get_args_list__(x, y):
            # assume x > y
            if y == 0:
                return x
            t = x / y
            m = x % y
            self.x_list.append( x )
            self.xt_list.append( 1 )
            self.y_list.append( y )
            self.yt_list.append( t )
            self.m_list.append( m )
            return __get_args_list__( y, m )

        __get_args_list__( self.phi, self.e )

        self.x_list.pop()
        self.xt_list.pop()
        self.y_list.pop()
        self.yt_list.pop()
        self.m_list.pop()
        for i in range( 0, len( self.yt_list ) ):
            self.yt_list[ i ] = -self.yt_list[ i ]
        self.m_list.reverse()
        self.x_list.reverse()
        self.xt_list.reverse()
        self.y_list.reverse()
        self.yt_list.reverse()

        m = self.m_list[ 0 ]
        x = self.x_list[ 0 ]
        xt = self.xt_list[ 0 ]
        y = self.y_list[ 0 ]
        yt = self.yt_list[ 0 ]
        # x always greater than y
        for i in range( 1, len( self.m_list ) ):
            tmp_yt = yt
            tmp_xt = xt
            x = self.x_list[ i ]
            xt = self.xt_list[ i ] * tmp_yt
            y = self.y_list[ i ]
            yt = tmp_xt + self.yt_list[ i ] * tmp_yt

        return yt % self.phi

    def __gcd__( self, x, y ):
        # assume x > y
        if y == 0:
            return x
        return self.__gcd__( y, x % y )

    def gen_key( self ):
        self.x_list = []
        self.xt_list = []
        self.y_list = []
        self.yt_list = []
        self.m_list = []
        self.n = p * q
        self.phi = ( p - 1 ) * ( q - 1 )
        self.e = int( raw_input( "input e " + str( self.__get_list__() ) + ": " ) )
        self.d = self.__extend_Eulid__()

    def encode( self, m ):
        return m ** self.e % self.n

    def dncode( self, c ):
        return c ** self.d % self.n

if __name__ == "__main__":
    p = int( raw_input( "input p: " ) )
    q = int( raw_input( "input q: " ) )

    ins_rsa = rsa( p = p, q = q )
    ins_rsa.gen_key()

    while True:
        m = int( raw_input( "input m:" ) )
        c = ins_rsa.encode( m )
        print c
        m = ins_rsa.dncode( c )
        print m

