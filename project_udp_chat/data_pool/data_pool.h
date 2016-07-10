#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>

class data_pool{
	public:
		data_pool(int _cap = 256);
		void data_put(std::string &_in);
		void data_get(std::string &_out);
		~data_pool();
	private:
		std::vector<std::string> pool;
		int capacity;

		int put_index;
		int get_index;

		sem_t sem_buf;
		sem_t sem_data;
};




