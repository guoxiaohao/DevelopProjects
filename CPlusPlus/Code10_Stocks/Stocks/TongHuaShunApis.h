#pragma once

#include <functional>

using tonghuashun_login = int(*)(const char * szUserName, const char * szPassword);
using tonghuashun_logout = int(*)();
