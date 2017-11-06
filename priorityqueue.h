#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>

namespace yao{
    namespace priority_queue{
        template <typename T>
        class PrioryQueue{
        public:
            PrioryQueue(){
            }

            const T& first() const /*throw exception*/{
                if(m_data.size() > 0){
                    return m_data[0];
                }
                throw std::exception();
            }

            const T extract() /*throw exception*/{
                if(m_data.size() > 0){
                    auto e = m_data[0];
                    m_data.erase(m_data.begin());
                    return e;
                }
                throw std::exception();
            }

            void insert(const T& e){
                m_data.push_back(e);
                bottom_up_heapify(m_data.size() - 1);
            }

            void change(const T& old, const T& v){
                //loop throw the vector
                //if found, replace it with v, if greater than parent, botto_up_heapify else top_down_heapify
                //else throw exception
            }

        private:
		//after adding a new node at the end of a heap, reheap the new heap
            void bottom_up_heapify(int pos){
                if(m_data.size() < 2){  //do not need to heapify, only one element
                    return;
                }

                auto parent = (pos - 1) / 2;

                if(parent > -1){
                    if(m_data[pos] > m_data[parent]){
                        std::swap(m_data[pos], m_data[parent]);
                        bottom_up_heapify(parent);
                    }
                }
            }
		//assume pos's right child and left child are both heapified, 
            void top_down_heapify(int pos){
                if(m_data.size() < 2){  //do not need to heapify
                    return;
                }

                if((pos + 1) * 2 > m_data.size()){
                    return;
                }

                auto leftChild = pos * 2 + 1;
                auto rightChild = pos * 2 + 2;

                auto largest = pos;
                if(m_data[leftChild] > m_data[largest]){
                    largest = leftChild;
                }

                if(rightChild < m_data.size()
                        && m_data[rightChild] > m_data[largest]){
                    largest = rightChild;
                }

                if(largest != pos){
                    std::swap(m_data[pos], m_data[largest]);
                    top_down_heapify(largest);
                }
            }

        private:
            std::vector<T> m_data;
        };
    }
}
#endif // PRIORITYQUEUE_H
