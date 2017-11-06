#ifndef QUEUE_H
#define QUEUE_H
#include <exception>
#include <iostream>
namespace yao{
    namespace queue{
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

            template <typename TT> friend class Queue;
        };

//doublelinked list based queue, this is the real implementation of std::list
        template <typename T>
        class Deque{
        public:
            Deque()
                : m_size(0){
                head = new Node<T>()
                        , tail = new Node<T>();
                head->next = tail;
                tail->prev = head;
            }

            ~Deque(){
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


            void enqueue (const T& e){
                insert_back(e);
            }

            void dequeue() throw(std::exception){
                if(m_size == 0){
                    throw std::exception();
                }

                auto delNode = head->next;
                head->next = delNode->next;
                delNode->next->prev = head;
                delete delNode;
                m_size--;
            }

            void insert_front(const T& e){
                auto newNode = new Node<T>(e);
                newNode->next = head->next;
                newNode->prev = head;
                head->next->prev = newNode;
                head->next = newNode;
                m_size++;
            }

            void insert_back(const T& e){
                auto newNode = new Node<T>(e);
                newNode->next = tail;
                newNode->prev = tail->prev;
                tail->prev->next = newNode;
                tail->prev = newNode;
                m_size++;
            }

            const T& front() const throw(std::exception){
                if(m_size){
                    return head->next->getElem();
                }
                throw std::exception();
            }

            const T& back() const throw(std::exception){
                if(m_size){
                    return tail->prev->getElem();
                }
                throw std::exception();
            }

            void erase_front() throw(std::exception){
                if(m_size == 0){
                    throw std::exception();
                }

                auto delNode = head->next;
                head->next = delNode->next;
                delNode->next->prev = head;
                delete delNode;
                m_size--;
            }

            void erase_back() throw(std::exception){
                if(m_size == 0){
                    throw std::exception();
                }

                auto delNode = tail->prev;
                tail->prev = delNode->prev;
                delNode->prev->next = tail;
                delete delNode;
                m_size--;
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
            Node<T>* head;
            Node<T>* tail;
            int m_size;
        };
//circule queue with fixed capacity
#define QUEUE_CAPACITY 1024
        template <typename T>
        class Queue{
        public:
            Queue()
                : m_size(0)
                , m_front(-1)
                , m_rear(-1){
            }

            bool isEmpty() const{
                return (m_front == -1 && m_rear == -1);
            }

            bool isFull() const{
                return (m_rear + 1) % QUEUE_CAPACITY == m_front;
            }

            void enqueue(const T& t){
                if(isFull()){
                    throw std::exception();
                }

                if(isEmpty()){
                    m_front = m_rear = 0;
                }else{
                    m_rear = (m_rear + 1) % QUEUE_CAPACITY;
                }
                m_data[m_rear] = t;
                m_size++;
            }

            void dequeue() throw(std::exception){
                if(isEmpty()){
                    throw std::exception();
                }

                if(m_front == m_rear){
                    m_front = m_rear = -1;
                }else{
                    m_front = (m_front + 1) % QUEUE_CAPACITY;
                }
                m_size--;
            }

            const T& front() throw(std::exception){
                if(isEmpty()){
                    throw std::exception();
                }
                return m_data[m_front];
            }

        private:
            int m_size;
            int m_front;
            int m_rear;
            T m_data[QUEUE_CAPACITY];
        };

//circule queue with dynamically allocated capacity, this is the real implementation of std::deque
        template <typename T>
        class Queue2{
        public:
            Queue2()
                : m_size(0)
                , m_capacity(1024)
                , m_front(-1)
                , m_rear(-1){
                m_data = new T[m_capacity];
            }

            ~Queue2(){
                delete []m_data;
            }

            bool isEmpty() const{
                return (m_front == -1 && m_rear == -1);
            }

            bool isFull() const{
                return (m_rear + 1) % m_capacity == m_front;
            }

            void enqueue(const T& t){
                if(isFull()){
			resize();
                }

                if(isEmpty()){
                    m_front = m_rear = 0;
                }else{
                    m_rear = (m_rear + 1) % m_capacity;
                }
                *m_data[m_rear] = t;
            }

            void dequeue() throw(std::exception){
                if(isEmpty()){
                   throw std::exception();
                }

                if(m_front == m_rear){
                    m_front = m_rear = -1;
                }else{
                    m_front = (m_front + 1) % m_capacity;
                }
            }

            void resize(){
                auto new_capacity =  m_capacity * 2;
                T* old_data = m_data;
                m_data = new T[new_capacity];

                auto j = -1;
                for(auto i = m_front; i != m_rear; i++){
                    if(i == m_capacity){
                        i -= m_capacity;
                    }
                    m_data[++j] = old_data[i];
                }
                m_data[++j] = old_data[m_rear];

                delete []old_data;
                m_capacity = new_capacity;
                m_front = 0;
                m_rear = j;
            }

            const T& front() throw(std::exception){
                if(isEmpty()){
                    resize();
                }
                return m_data[m_front];
            }

        private:
            int m_size;
            int m_front;
            int m_rear;
            int m_capacity;
            T *m_data;
        };
    }
}
#endif // QUEUE_H
