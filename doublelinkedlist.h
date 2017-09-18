#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <exception>
namespace yao{
    namespace dlink{
        template <typename T>
        class Node{
        public:
            Node()
                : prev(nullptr)
                , next(nullptr){
            }

            Node(const T& t)
                : elem(t)
                , prev(nullptr)
                , next(nullptr){

            }

            const T& getElem() const{
                return elem;
            }

        private:
            T elem;
            Node <T>* prev;
            Node<T>* next;

            template <typename TT> friend class DoubleLinkedList;
        };

        template <typename T>
        class DoubleLinkedList
        {
        public:
            DoubleLinkedList()
                : m_size(0){
                head = new Node<T>();
                tail = new Node<T>();
                head->next = tail;
                tail->prev = head;
            }

            ~DoubleLinkedList(){
                clear();
                delete head;
                delete tail;
            }

            void clear(){
                auto cursor = head->next;
                while(cursor != tail->next){
                    auto delNode = cursor;
                    cursor = cursor->next;
                    delete delNode;
                }
                head->next = tail;
                tail->prev = head;
                m_size = 0;
            }

            const T& getElem(const int i) const{
                auto cursor = find(i);
                if(cursor
                        && cursor != tail){
                    return cursor->getElem();
                }

                throw std::exception();//i is invalid or list does not have enough elems
            }

            void remove(const int i){
                auto node = find(i);
                if(node
                        && node != tail){
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }else{
                    throw std::exception();
                }
            }

            const T& front() const{
                if(m_size){
                    return head->next->getElem();
                }
                throw std::exception();
            }

            const T& back() const{
                if(m_size){
                    return tail->prev->getElem();
                }
            }

            void addFront(const T& e){
                auto newNode = new Node<T>(e);
                newNode->next = head->next;
                newNode->prev = head;
                head->next->prev = newNode;
                head->next = newNode;
                m_size++;
            }

            void addBack(const T& e){
                auto newNode = new Node<T>(e);
                newNode->next = tail;
                newNode->prev = tail->prev;
                tail->prev->next = newNode;
                tail->prev = newNode;
                m_size++;
            }

            void removeFront(){
                if(m_size == 0){
                    throw std::exception();
                }

                auto delNode = head->next;
                head->next = delNode->next;
                delNode->next->prev = head;
                delete delNode;
                m_size--;
            }

            void removeBack(){
                if(m_size == 0){
                    throw std::exception();
                }

                auto delNode = tail->prev;
                tail->prev = delNode->prev;
                delNode->prev->next = tail;
                delete delNode;
                m_size--;
            }

            void insert(const int i, const T& t){
                if(i == m_size + 1){
                    auto newNode = new Node<T>(t);
                    newNode->next = tail;
                    newNode->prev = tail->prev;
                    tail->prev->next = newNode;
                    tail->prev = newNode;
                }else{
                    auto node = find(i);
                    if(node){
                        auto newNode = new Node<T>(t);
                        newNode->prev = node->prev;
                        newNode->next = node;
                        node->prev->next = newNode;
                        node->prev = newNode;
                    }else{
                        throw std::exception();
                    }
                }
            }

            void print() const{
                std::cout << "---------------" << std::endl;
                auto node = head->next;
                while(node != tail){
                    std::cout << node->getElem() << std::endl;
                    node = node->next;
                }
            }

        private:
            Node<T>* find(const int i) const{
                if(i < 0
                        || i > m_size){
                    return nullptr;
                }

                auto cursor = head->next;
                auto step = 0;
                while(cursor != tail){
                    if(i == step){
                        break;
                    }
                    step++;
                    cursor = cursor->next;
                }

                return cursor;
            }

            Node<T>* head;
            Node<T>* tail;
            int m_size;
        };
    }
}
#endif // DOUBLELINKEDLIST_H
