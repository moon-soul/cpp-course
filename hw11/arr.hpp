#pragma once

#include "sorting_direction.hpp"

void printArray(const int* arr, int size);
bool compare(int a, int b, SortingDirection direction);
bool isSorted(const int* arr, int size, SortingDirection direction);
