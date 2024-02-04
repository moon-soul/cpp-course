#include "dynamic_array.hpp"

#include <cassert>

int main()
{
    /* C-tor default */
    DynamicArray<int> arr1;
    assert(arr1.isEmpty() == true);
    assert(arr1.getCapacity() == 1);

    /* C-tor param size */
    constexpr size_t ctorSize = 10;
    DynamicArray<int> arr2(ctorSize);
    assert(arr2.isEmpty() == false);
    assert(arr2.getSize() == ctorSize);
    assert(arr2.getCapacity() == ctorSize);

    /* Default values of c-tor param size */
    for (size_t i = 0; i < arr2.getSize(); ++i)
    {
        assert(arr2[i] == 0);
    }

    /* Assign empty array */
    arr2 = arr1;
    assert(arr2.isEmpty() == true);
    assert(arr2.getSize() == 0);
    assert(arr2.getCapacity() == ctorSize);

    /* Equality of empty arrays */
    assert(arr2 == arr1);

    /* Shrink to fit */
    arr2.shrinkToFit();
    assert(arr2.getCapacity() == 1);

    /* Add 1st element */
    arr2.push_back(2);
    assert(arr2[0] == 2);

    /* Add 2nd element */
    arr2.push_back(4);
    assert(arr2[1] == 4);

    /* Add 3rd element */
    arr2.push_back(6);
    assert(arr2[2] == 6);

    /* Size after adding 3 elements */
    assert(arr2.getSize() == 3);

    /* Capacity after adding 3 elements */
    assert(arr2.getCapacity() == 4);

    /* Change 1st element */
    arr2[0] = 10;
    assert(arr2[0] == 10);

    /* Change 2nd element */
    arr2[1] = 20;
    assert(arr2[1] == 20);

    /* Remove 3rd (last) element */
    arr2.pop_back();
    assert(arr2.getSize() == 2);

    /* Get last element */
    assert(arr2.back() == 20);

    /* Set size shrink */
    constexpr size_t shrinkSize = 1;
    arr2.setSize(shrinkSize);
    assert(arr2.getSize() == shrinkSize);
    assert(arr2.back() == 10);

    /* Set size expand */
    constexpr size_t expandSize = 3;
    arr2.setSize(expandSize);
    assert(arr2.getSize() == expandSize);
    assert(arr2[0] == 10);
    assert(arr2[1] == 0);
    assert(arr2[2] == 0);

    /* C-tor param size equals 0 */
    DynamicArray<int> arr3(0);
    assert(arr3.isEmpty() == true);
    assert(arr3.getCapacity() == 1);

    /* Assign non-empty array */
    arr2[0] = 16;
    arr2[1] = 22;
    arr2[2] = 34;
    arr3 = arr2;
    assert(arr3.getSize() == arr2.getSize());
    assert(arr3.getCapacity() == arr2.getSize());
    for (size_t i = 0; i < arr3.getSize(); ++i)
    {
        assert(arr3[i] == arr2[i]);
    }

    /* C-tor copy */
    DynamicArray<int> arr4(arr3);
    assert(arr4.getSize() == arr3.getSize());
    assert(arr4.getCapacity() == arr3.getSize());
    for (size_t i = 0; i < arr4.getSize(); ++i)
    {
        assert(arr4[i] == arr3[i]);
    }

    /* Equality of non-empty arrays */
    assert(arr4 == arr3);

    /* Set size 0 */
    arr3.setSize(0);
    assert(arr3.isEmpty() == true);

    /* Equality of non-empty and empty array */
    assert((arr4 == arr3) == false);

    /* Clear */
    arr4.clear();
    assert(arr4.isEmpty() == true);

    /* Reserve */
    constexpr size_t reservedSpace = 10;
    arr4.reserve(reservedSpace);
    assert(arr4.getCapacity() == reservedSpace);

    return 0;
}
