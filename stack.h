#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <exception>
namespace yao{
    namespace stack{
        template <typename T>
        class Node{
        public:
            Node() = delete;
            Node(const T& t)
                : elem(t)
                , next(nullptr){
            }

            const T& getElem() const{
                return elem;
            }

        private:
            T elem;
            Node<T>* next;

            template <typename TT> friend class Stack;
        };

        template <typename T>
        class Stack
        {
        public:
            Stack()
                : head(nullptr)
                , m_size(0){
            }

            void push(const T& t){
                auto node = new Node<T>(t);
                if(head){
                    node->next = head;
                }
                head = node;

                m_size++;
            }

            const T& top() const{
                if(head){
                    return head->getElem();
                }
                throw std::exception();
            }

            void pop(){
                if(head){
                    auto delNode = head;
                    head = head->next;
                    delete delNode;
                    m_size--;
                }else{
                    throw std::exception();
                }
            }

            void clear(){
                while(head){
                    auto delNode = head;
                    head = head->next;
                    delete delNode;
                }
                m_size = 0;
            }

            ~Stack(){
                clear();
            }

            void print() const{
                auto node = head;
                std::cout << "-----------" << std::endl;
                while(node){
                    std::cout << node->getElem() << std::endl;
                    node = node->next;
                }
            }

        private:
            Node<T>* head;
            int m_size;
        };
    }
}

#endif // STACK_H
