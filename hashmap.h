#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <exception>
#include <iostream>
#define TABLE_SIZE  10000
namespace yao{
    namespace hash{
        class Exception : public std::exception{
        protected:
            std::string _what;
        public:
            Exception(std::string _what) : _what(_what){}
            const char* what() const noexcept {return _what.c_str();}
            ~Exception() throw(){}
        };


        template <typename K, typename V>
        class  HashNode{
        public:
            HashNode(const K &key, const V &value) :
                key(key), value(value), next(nullptr) {
            }

        private:
            // key-value pair
            K key;
            V value;
            // next bucket with the same key
            HashNode *next;

            template <typename T1, typename T2, typename HASH_FUN>
            friend class HashMap1;

            template <typename T1, typename T2, typename HASH_FUN>
            friend class HashMap2;
        };

        template <typename K, typename V, typename HASH_FUN>
        class HashMap1 {
        public:
            HashMap1(HASH_FUN hashFunc)
                : hashFunc(hashFunc){
                m_data.resize(TABLE_SIZE);
            }

            ~HashMap1() {
                for(auto& vec: m_data){
                    for(auto & v: vec){
                        delete v;
                    }
                }
            }

            const V& get(const K& key){
                unsigned long hashValue = hashFunc(key);
                const auto& vec = m_data[hashValue];
                for(const auto& e: vec){
                    if(e->key == key){
                        return e->value;
                    }
                }
                throw Exception("Elem not found");
            }

            void put(const K& key, const V& v){
                std::cout << "key :" << key << std::endl;
                auto hashValue = hashFunc(key);
                auto& vec = m_data[hashValue];
                for(auto& e: vec){
                    if(e->key == key){
                        e->value = v;
                        return;
                    }
                }
                vec.push_back(new HashNode<K, V>(key, v));
            }

            void remove(const K& key){
                auto hashValue = hashFunc(key);
                auto& vec = m_data[hashValue];
                for(auto iter = vec.begin(); iter != vec.end(); ++iter){
                    if((*iter)->key == key){
                        delete (*iter);
                        vec.erase(iter);
                        return;
                    }
                }
                throw Exception("Elem not found");
            }
        private:
            // hash table
            std::vector<std::vector<HashNode<K, V>*>> m_data;
            HASH_FUN hashFunc;
        };

        template <typename K, typename V, typename HASH_FUN>
        class HashMap2 {
        public:
            HashMap2(HASH_FUN hashFunc)
                : hashFunc(hashFunc){
                m_data = new HashNode<K, V> *[TABLE_SIZE];
                for(auto i = 0; i < TABLE_SIZE; i++){
                    m_data[i] = nullptr;
                }
            }

            ~HashMap2() {
                for(auto i = 0; i < TABLE_SIZE; i++){
                    auto nodes = m_data[i];
                    while(nodes){
                        auto delNode = nodes;
                        nodes = nodes->next;
                        delete delNode;
                    }
                }
                delete []m_data;
            }

            const V& get(const K& key){
                auto hashValue = hashFunc(key);
                auto nodes = m_data[hashValue];

                while(nodes){
                    if(nodes->key == key){
                        return nodes->value;
                    }
		    nodes=nodes->next;
                }

                throw Exception("Elem not found");
            }

            void put(const K& key, const V& v){
                std::cout << "key :" << key << std::endl;
                auto hashValue = hashFunc(key);

                auto nodes = m_data[hashValue];
                while(nodes){
                    if(nodes->key == key){
                        nodes->value = v;
                        return;
                    }
		    nodes= nodes->next;
                }
		//insert new node at front
                auto newNode = new HashNode<K, V>(key, v);
                newNode->next = m_data[hashValue];
                m_data[hashValue] = newNode;
            }

            void remove(const K& key){
                auto hashValue = hashFunc(key);
                auto nodes = m_data[hashValue];

                auto prevNode = nodes;
                while(nodes){
                    if(nodes->key == key){
                        if(nodes == m_data[hashValue]){
                            m_data[hashValue] = nodes->next;
                        }else{
                            prevNode->next = nodes->next;
                        }
                        delete nodes;
                        return;
                    }
                    prevNode = nodes;
                    nodes = nodes->next;
                }

                throw Exception("Elem not found");
            }
        private:
            // hash table
            HashNode<K, V> **m_data;
            HASH_FUN hashFunc;
        };

        void test();
        unsigned long hashFunc(int key);

    }
}
#endif // HASHMAP_H
