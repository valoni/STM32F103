/*
 * S3C2440_Cache.cpp
 *
 *  Created on: 14.6.2011
 *      Author: Matti Eerola
 */


#include <cores\arm\include\cpu.h>

#pragma arm section code = "SectionForBootstrapOperations"

void __section(SectionForBootstrapOperations) CPU_FlushCaches()
{
    CPU_ARM9_FlushCaches(8,64);
}

//--//

// OTHER CACHE FUNCTIONS COME FROM ARM9 common implemenation

//--//

size_t __section(SectionForBootstrapOperations) CPU_GetCachableAddress( size_t address )
{
    return address;
}

//--//

size_t __section(SectionForBootstrapOperations) CPU_GetUncachableAddress( size_t address )
{
	return address;
}

#pragma arm section code
