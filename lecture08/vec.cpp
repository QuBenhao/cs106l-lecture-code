#include <algorithm>
#include <list>
#include <vector>
#include <ranges>
#include <iostream>

void printVector(const std::vector<int>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::cout << "Before sorting: ";
    printVector(vec);

    std::sort(vec.begin(), vec.end());
    int arr[]{3, 1, 2};
    std::sort(arr, arr + 3);
    std::ranges::sort(vec);
    std::cout << "After sorting: ";
    printVector(vec);

    auto lit = std::lower_bound(vec.begin(), vec.end(), 2);
    auto rit = std::upper_bound(vec.begin(), vec.end(), 2);

    std::cout << std::distance(vec.begin(), lit) << ", " << std::distance(vec.begin(), rit) << std::endl;

    std::list<int> lst;
    std::copy(vec.begin(), vec.end(), lst.begin());
    auto it = lst.begin();

}