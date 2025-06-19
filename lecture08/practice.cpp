#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <list>
#include <typeinfo>
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

template<typename InputIterator, typename DataType>
int countOccurrences(InputIterator begin, InputIterator end, DataType value) {
    int count = 0;
    for (auto it = begin; it != end; ++it) {
        if (*it == value) {
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

    std::list<int> lst{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = countOccurrences(lst.begin(), lst.end(), 5);

    std::cout << "Count of 5 in list: " << count << std::endl;
    std::vector<Time> times = {Time(1, 30), Time(2, 15), Time(0, 45)};
    int timeCount = countOccurrences(times.begin(), times.end(), Time(1, 30));
    std::cout << "Count of Time(1, 30) in vector: " << timeCount << std::endl;
    timeCount = countOccurrences(times.begin() + 1, times.end(), Time(1, 30));
    std::cout << "Count of Time(1, 30) in vector (from second element): " << timeCount << std::endl;

    // std::unordered_map<std::string, int> wordCount{
    //     {"apple", 3},
    //     {"banana", 2},
    //     {"orange", 5}
    // };
    // int wordOccurrences = countOccurrences(wordCount.begin(), wordCount.end(), std::make_pair(std::string("banana"), 2));
    // std::cout << "Count of ('banana', 2) in unordered_map: " << wordOccurrences << std::endl;
}