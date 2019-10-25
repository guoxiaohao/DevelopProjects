#pragma once

#include "guo_stdtypes.h"

namespace guo_rpc_contents 
{
	
template<class T, std::size_t MaxSize>
class SmallArrays
{

protected:
	T data[MaxSize];
};

}