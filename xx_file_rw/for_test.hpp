#pragma once
#include <unordered_map>

std::unordered_map<int, int> g_map;
static void for_test1()
{
    g_map[1] = 1;
    for(auto it = g_map.begin(); it != g_map.end(); ++it)
    {
        printf("xxx1 %d\n", it->second);
    }
}

static void for_test2()
{
    g_map[2] = 2;
    auto begin = g_map.begin();
    auto end = g_map.end();
    for(auto it = begin; it != end; ++it)
    {
        printf("xxx2 %d\n", it->second);
    }
}
static void for_test()
{
    for_test1();
    for_test2();
}
