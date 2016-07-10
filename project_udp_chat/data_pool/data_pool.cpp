#include "data_pool.h"

data_pool::data_pool( int _cap )
	:capacity(_cap)
	,pool(_cap)
	,put_index(0)
	,get_index(0)
{
	sem_init(&sem_buf, 0, _cap);
	sem_init(&sem_data, 0, 0);
}

void data_pool::data_put(std::string &_in)
{
	sem_wait( &sem_buf );

	//pthread_mutex_lock();
	pool[put_index] = _in;
	put_index++;
	put_index %= capacity;
	//pthread_mutex_unlock();

	sem_post( &sem_data );
}

void data_pool::data_get(std::string &_out)
{
	sem_wait( &sem_data );

	_out = pool[get_index];
	get_index++;
	get_index %= capacity;

	sem_post( &sem_buf );
}

data_pool::~data_pool()
{
	sem_destroy(&sem_buf);
	sem_destroy(&sem_data);
}




