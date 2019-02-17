#pragma once

#if defined(__GNUC__) || defined(__GNUG__)
#include <unistd.h>
#else
#include <WinSock2.h>
#include <Windows.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
