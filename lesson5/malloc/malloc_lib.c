#include <stdio.h> 
#include <unistd.h> 
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "safe_printf_lib.h"

#ifdef DEBUG
	#define info(... ) safe_printf(__VA_ARGS__)
#else
	#define info(... )
#endif


int has_initialized = 0;	//флаг инициализации malloc_init
void* managed_memory_start; //указатель на начало выделенной памяти
void* last_valid_address;	//указатель на последний доступный адрес

struct mem_control_block {
	int is_available;
	int size;
};

void malloc_init()
{
	last_valid_address = sbrk(0);	// получаем указатель на последний доступный адрес
	managed_memory_start = last_valid_address; // т.к. память еще не запрошена, то начало=конец
	has_initialized = 1;			//проинициализируем выполнение инициализации malloc_init
}


void* malloc(long unsigned numbytes) {
	
	static int i = 1;
	safe_printf("%d) Malloc %ld bytes\n", i, numbytes);
	i++;
	
	void* current_location;							//текущее расположение указателя
	struct mem_control_block* current_location_mcb; //текущее расположение указателя, приведенное к типу struct
	void* memory_location = NULL;					// возвращаемое значение
	if (!has_initialized) {
		malloc_init();
	}
	numbytes = numbytes + sizeof(struct mem_control_block); // добавляем к требуемому размеру памяти размер структуры
	current_location = managed_memory_start; // инициализируем текущее значение указателя начальным адресом

	while (current_location != last_valid_address) //двигаемся по памяти, пока не достигнем последнего доступного адреса
	{
		current_location_mcb =	(struct mem_control_block*)current_location; //запишем в current_location_mcb значение текущего указателя

		if (current_location_mcb->is_available)
		{
			if (current_location_mcb->size >= numbytes)
			{
				current_location_mcb->is_available = 0; // участок найден. Изменим флаг
				memory_location = current_location;		// возвращаемое значение = текущему значению
				break;
			}
		}
		current_location = current_location + current_location_mcb->size; //если текущий участок занят, то смещаемся на размер занятой памяти
	}

	if (!memory_location) //если при переборе всех выделенных ячеек, мы не можем уместить требуемый участок, то выделяем еще памяти
	{
		sbrk(numbytes); //сдвигаем program break на numbytes
		memory_location = last_valid_address;		// требуемый адрес находится по последнему доступному адресу
		last_valid_address = last_valid_address + numbytes; // смещаем последний доступный адрес
		current_location_mcb = memory_location;		//инициализируем current_location_mcb
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	info("Allocated:\t from %p to %p\n", memory_location, memory_location + numbytes);
	memory_location = memory_location + sizeof(struct mem_control_block); // перемещаем указатель на возвращаемое значение после структуры
	return memory_location; //возвращаем указатель
}

void free(void* firstbyte) {
	struct mem_control_block* mcb;
	mcb = firstbyte - sizeof(struct mem_control_block); //смещаем указатель на размер  mem_control_block
	mcb->is_available = 1; //отмечаем блок свободным
	info("Free:\t\t from %p to %p\n", mcb, firstbyte - sizeof(struct mem_control_block) + mcb->size);
	return;
}

