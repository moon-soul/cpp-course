#include "dynamic_int_array.hpp"

#include <cassert>

int main()
{
    /* C-tor default */
    DynamicIntArray arr1{};
    assert(arr1.isEmpty() == true);

    /* C-tor param size */
    DynamicIntArray arr2{10};
    assert(arr2.getSize() == 10);

    /* Default values of c-tor param size */
    for (size_t i = 0; i < arr2.getSize(); ++i)
    {
        assert(arr2[i] == 0);
    }

    /* Assign empty array */
    arr2 = arr1;
    assert(arr2.isEmpty() == true);

    /* Add 1 element */
    arr2.push_back(2);
    assert(arr2[0] == 2);

    /* Add 2 element */
    arr2.push_back(4);
    assert(arr2[1] == 4);

    /* Size after adding 2 elements */
    assert(arr2.getSize() == 2);

    /* Change 1 element */
    arr2[0] = 10;
    assert(arr2[0] == 10);

    /* Change 2 element */
    arr2[1] = 20;
    assert(arr2[1] == 20);

    /* Clear array */
    arr2.clear();
    assert(arr2.isEmpty() == true);

    /* Set size */
    const size_t size = 3;
    arr2.setSize(size);
    assert(arr2.getSize() == size);

    /* Default values of resizing */
    for (size_t i = 0; i < arr2.getSize(); ++i)
    {
        assert(arr2[i] == 0);
    }

    /* C-tor param size equals 0 */
    DynamicIntArray arr3{0};
    assert(arr3.isEmpty() == true);

    /* Assign non-empty array */
    arr2[0] = 16;
    arr2[1] = 22;
    arr2[2] = 34;
    arr3 = arr2;
    assert(arr3.getSize() == arr2.getSize());
    for (size_t i = 0; i < arr3.getSize(); ++i)
    {
        assert(arr3[i] == arr2[i]);
    }

    /* C-tor copy */
    DynamicIntArray arr4{arr3};
    assert(arr4.getSize() == arr3.getSize());
    for (size_t i = 0; i < arr4.getSize(); ++i)
    {
        assert(arr4[i] == arr3[i]);
    }

    /* Set size to 0 */
    arr4.setSize(0);
    assert(arr4.isEmpty() == true);

    return 0;
}
