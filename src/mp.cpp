#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

typedef struct chunk
{
	void		 *data;
	struct chunk *next;

} _chunk;

class Cmpool 
{
	private :
		_chunk	*head;
		_chunk	*tail;	//tail
		int		remain;
		int		length;
		size_t	size;
		
	public :
		Cmpool( size_t n, int len )
		{
//			mp		= (_chunk*)malloc( sizeof(_chunk) ); 
//			mp->data= (_chunk*)malloc( n ); 
//
//			head	= mp;

			remain	= length = len;
			size	= n;

			for( int i = 0; i < length; i++ )
			{
				_chunk *p	= (_chunk*)malloc( sizeof(_chunk) ); 
				p->data		= (_chunk*)malloc( n ); 

				printf( "%p\n", p );
				
				if( i == 0 )
				{
					head = tail = p;
					continue;
				}

				tail->next = p;
				tail = p;
			}
		}

		~Cmpool()
		{
			cout << "-----------" << endl;

			while( head )
			{
				_chunk *p = head;

				printf( "s:%p\n", p );

				head = head->next;

				if( p )
				{
					if( p->data )
					{
						free(p->data);
						//printf( "d:%p\n", p->data );
					}
					free(p);
				}
			}
		}
	
	public :
		void *alloc()
		{
			_chunk *p = head;
			head = head->next;
			remain--;

			p->next = 0;

			return p;
		}

		void dealloc( void *p )
		{
			memset( p, 0x00, sizeof( _chunk ) );

			tail->next = (_chunk*)p;
			tail = (_chunk*)p;

			remain++;
		}
};


int main()
{
	//Cmpool mp( sizeof(_chunk), 10 );
	Cmpool *mp = new Cmpool( 128, 10 );

	//void *p = mp.alloc();
	void *p = mp->alloc();

	cout << " ===== " << endl;
	cout << p << endl;

	//mp.dealloc(p);
	mp->dealloc(p);

	delete mp;

	return 0;
}


// end of file
