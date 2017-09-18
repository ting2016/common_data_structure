
#include "quicksort.h"
#include <chrono>
#include <random>
int yao::quicksort::generateRandomNumber(int start, int end){
    if(start == end)
        return start;

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rand_num = std::minstd_rand0 (seed)() % std::abs(end - start);
    return (start < end)? start + rand_num: end + rand_num;
}
