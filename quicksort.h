#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <algorithm>
namespace yao{
    namespace quicksort{
        int generateRandomNumber(int start, int end);

        template <typename T>
        int partition(T* A, const int start, const int end){
            auto randPivot = generateRandomNumber(start, end);
            std::swap(A[randPivot], A[end]);
            auto i = start - 1;
            for(auto j = start; j < end; j++){
                if(cmp(A[j] > A[end])){
                    exchange(A[++i], A[j]);
                }
            }
            std::swap(A[i + 1], A[end]);
            return i + 1;
        }

        template <typename T>
        void quicksort(T* A, int start, int end){
            if(start < end){
                auto pivot = partition(A, start, end);
                quicksort(A, start, pivot - 1);
                quicksort(A, pivot + 1, end);
            }
        }
    }
}
#endif // QUICKSORT_H
