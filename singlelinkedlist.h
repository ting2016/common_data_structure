#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H
#include <exception>
#include <iostream>
namespace yao{
    namespace slink{
        template <typename T>
        class Node{
        public:
            Node ()= delete;
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
            template <typename TT>
            friend class SingleLinkedList;
        };
        
        template<class T>
        class SingleLinkedList
        {
        public:
            SingleLinkedList()
                : head(nullptr)
                , m_size(0){
            }
            
            ~SingleLinkedList(){
                if(m_size){
                    clear();
                }
            }
            
            void clear(){
                Node<T>* cursor;
                while(head){
                    cursor = head;
                    head = head->next;
                    delete cursor;
                }
                m_size = 0;
            }
            
            const T& getElemt(const int i) const{
                auto cursor = find(i);
                if(cursor){
                    return cursor->getElem();
                }
                
                throw std::exception();//i is invalid or list does not have enough elems
            }
            
            void insert(const int i, const T& t){
                if(i == 0){
                    auto node = new Node<T>(t);
                    node->next = head;
                    head = node;
                }else{
                    auto prevNode = find(i - 1);
                    if(prevNode){
                        auto node = new Node<T>(t);
                        node->next = prevNode->next;
                        prevNode->next = node;
                    }else{
                        throw std::exception();//i is invalid or list does not have enough elems
                    }
                }
                m_size++;
            }
            
            void remove(const int i){
                if(i == 0){
                    if(m_size > 1){
                        auto node = head;
                        head = head->next;
                        delete node;
                    }else{
                        delete head;
                        head = nullptr;
                    }
                }else{
                    auto prevNode = find(i - 1);
                    if(prevNode){
                        auto node = prevNode->next;
                        if(node){
                            prevNode->next = node->next;
                            delete node;
                        }else{
                            throw std::exception();//i is invalid or list does not have enough elems
                        }
                    }else{
                        throw std::exception();//i is invalid or list does not have enough elems
                    }
                }
                m_size--;
            }
            
            void print() const{
                std::cout << "---------------" << std::endl;
                auto node = head;
                while(node){
                    std::cout << node->getElem() << std::endl;
                    node = node->next;
                }
            }
            
        private:
            Node<T>* find(const int i) const{
                if(i < 0){
                    return nullptr;
                }
                
                if(i > m_size){
                    return nullptr;
                }
                
                auto cursor = head;
                auto step = 0;
                while(cursor){
                    if(i == step){
                        break;
                    }
                    step++;
                    cursor = cursor->next;
                }
                
                return cursor;
            }
            
            Node<T> * head;
            int m_size;
        };
    }
}
#endif // SINGLELINKEDLIST_H
