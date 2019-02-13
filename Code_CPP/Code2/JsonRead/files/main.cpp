#include "pch.h"

int main(int argc, char** argv)
{
#ifdef MACRO_PREDEFINES
std::cout << "Get Macro" << std::endl;
#endif

    system("pause");

    return 0;
}