#ifndef SORT_H
#define SORT_H
#include <algorithm>
namespace yao{
    namespace heapsort{
        template <typename T>
        void heapify(T* A, const int& size, const int& i){
            if(size < 2){   // only one node, do not heapify it
                return ;
            }

            if((i + 1) * 2 > size){ // element i does not have child, do not heapify it
                return;
            }

            auto l = 2 * i + 1; //left child
            auto r = 2 * i + 2; //right child
            auto larger = i;
            if(A[l] > A[i]){
                larger = l;
            }

            if(r < size && A[r] > A[larger]){
                larger = r;
            }

            if(larger != i){
                std::swap(A[i], A[larger]);
                heapify(A, size, larger);  //re-heapify
            }

        }

        template <typename T>
        void buildHeap(T* A, const int& size){
            auto half = size / 2 -1;
            for(auto i = half; i > -1; i--){
                heapify(A, size, i);
            }
        }

        template <typename T>
        void heapsort(T* A, int size){
            buildHeap(A, size);
            for(auto i = size - 1; i > 0; i--){
                std::swap(A[i], A[0]);
                heapify(A, i, 0);
            }
        }
    }
}

#endif // SORT_H
