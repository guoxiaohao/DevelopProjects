#pragma once

#if defined(__GNUC__) || defined(__GNUG__)
#include <unistd.h>
#define COMPLIER_NAME "g++"
#else
#include <Windows.h>
#define COMPLIER_NAME "MSCV"
#endif

#include <iostream>

#include <stdio.h>
#include <assert.h>
#include <string.h>