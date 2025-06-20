#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <list>
#include <typeinfo>
#include <functional>
#include <unordered_map>

class Time {
    int hours;
    int minutes;
public:
    Time(int h, int m) : hours(h), minutes(m){}
    Time() : hours(0), minutes(0) {}
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << t.hours << "h " << t.minutes << "m";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Time& t) {
        char colon;
        is >> t.hours >> colon >> t.minutes;
        if (colon != ':') {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
    friend bool operator<(const Time& lhs, const Time& rhs) {
        return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
    }
    friend bool operator>(const Time& lhs, const Time& rhs) {
        return std::tie(lhs.hours, lhs.minutes) > std::tie(rhs.hours, rhs.minutes);
    }
    friend bool operator==(const Time& lhs, const Time& rhs) {
        return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
    }
};


template<typename T>
std::pair<T, T> myMinMax(T a, T b) {
    return {std::min(a, b), std::max(a, b)};
}

template<typename T>
void printMinMax(const std::pair<T, T>& p) {
    std::cout << "Min: " << p.first << ", Max: " << p.second << std::endl;
}

template<typename T>
T getTypeValue() {
    while (true) {
        std::cout << "Enter a " << typeid(T).name() << " value: ";

        std::string line;
        T result;
        char extra;
        if (!std::getline(std::cin, line))
            throw std::runtime_error("Failed to read input");
        std::istringstream iss(line);
        if (iss >> result && !(iss >> extra)) return result;
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

template<typename InputIterator, typename UnaryPredicate>
int countOccurrences(InputIterator begin, InputIterator end, UnaryPredicate predicate) {
    int count = 0;
    for (auto it = begin; it != end; ++it) {
        if (predicate(*it)) {
            ++count;
        }
    }
    return count;
}

int main() {
    auto result = myMinMax(10, 20);
    printMinMax(result);

    auto r2 = myMinMax(7.3, 8.1);
    printMinMax(r2);

    auto strPair = myMinMax<std::string>("apple", "banana");
    printMinMax(strPair);

    // int val0 = getTypeValue<int>();
    // int val1 = getTypeValue<int>();
    // double val2 = getTypeValue<double>();
    // Time val3 = getTypeValue<Time>();
    // std::cout << "You entered: " << val0 << ", " << val1 << ", " << val2 << ", " << val3 << std::endl;

    auto lessThanFive = [](int x) { return x < 5; };
    std::list<int> lst{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = countOccurrences(lst.begin(), lst.end(), lessThanFive);

    // auto countFunc = std::bind(countOccurrences, std::placeholders::_1, std::placeholders::_2, lessThanFive);

    std::cout << "Count of elements less than 5 in list: " << count << std::endl;
    std::vector<Time> times = {Time(1, 30), Time(2, 15), Time(0, 45)};
    std::shuffle(times.begin(), times.end(), std::mt19937{std::random_device{}()});

    std::copy(times.begin(), times.end(), std::ostream_iterator<Time>(std::cout, ", "));
    std::cout << std::endl;
    int timeCount = countOccurrences(times.begin(), times.end(), [](const Time& t) { return t == Time(1, 30); });
    std::cout << "Count of Time(1, 30) in vector: " << timeCount << std::endl;
    timeCount = countOccurrences(times.begin() + 1, times.end(), [](const Time& t) { return t == Time(1, 30); });
    std::cout << "Count of Time(1, 30) in vector (from second element): " << timeCount << std::endl;

    // std::unordered_map<std::string, int> wordCount{
    //     {"apple", 3},
    //     {"banana", 2},
    //     {"orange", 5}
    // };
    // int wordOccurrences = countOccurrences(wordCount.begin(),
    // wordCount.end(), std::make_pair(std::string("banana"), 2));
    // std::cout << "Count of ('banana', 2) in unordered_map: " << wordOccurrences << std::endl;

    // std::sort, std::nth_element, std::stable_partition, std::copy_if, std::remove_if
    std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::cout << "Before sorting: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    std::sort(vec.begin(), vec.end());
    std::cout << "After sorting: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    auto cmpFunc = [](int a, int b) { return a > b; };
    // int median = std::nth_element(vec.begin(), vec.begin() + vec.size() / 2, vec.end(), cmpFunc);
    // std::cout << "Median value: " << median << std::endl;
    std::stable_partition(vec.begin(), vec.end(), [](int x) { return x > 4; });
    std::cout << "After stable partitioning (elements > 4): ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::vector<int> filteredVec;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(filteredVec), [](int x) { return x < 5; });
    std::cout << "Filtered vector (elements < 5): ";
    std::copy(filteredVec.begin(), filteredVec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    auto end = std::remove_if(vec.begin(), vec.end(), [](int x) { return x < 5; });
    vec.erase(end, vec.end());
    std::cout << "After removing elements < 5: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::string s = "Hello, World!";
    std::string subStr = "World";
    // auto it = std::search(s.begin(), s.end(), std::string("World"));
    auto it = std::search(s.begin(), s.end(), subStr.begin(), subStr.end());
    std::cout << "Substring found at position: " << std::distance(s.begin(), it) << std::endl;

}