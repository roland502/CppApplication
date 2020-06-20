#pragma once

#include <string>
using namespace std;

struct Base_item
{
    int id;
    int parent_id;
    string name;
    string planned_start;
    string planned_end;
    int completed;
};


