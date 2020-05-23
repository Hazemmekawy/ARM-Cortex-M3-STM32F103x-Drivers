
#include "STD_TYPES.h"
#include <dFLASH.h>

#define ADDRESS_1      (0x08001E70)
#define ADDRESS_2      (0x08001EC0)
#define DATA_2_SIZE     6
#define DATA_1          0xABCDEF12

int
main(void)
{

	dFLASH_unlock();

	dFLASH_erasePage((void *)ADDRESS_1);

	dFLASH_writeWord((void *)ADDRESS_1,DATA_1);

	u32 temp = *((u32 *)ADDRESS_1);

	trace_printf("DATA 1: %x \n",temp);

	dFLASH_erasePage(ADDRESS_1);

	dFLASH_erasePage(ADDRESS_2);

	u8 arr[DATA_2_SIZE] = {1,2,3,4,5};

	dFLASH_programWrite((void *)ADDRESS_2,arr,DATA_2_SIZE);

	dFLASH_erasePage(ADDRESS_2);

	dFLASH_lock();


  while (1)
    {

    }
  return 0;
}

