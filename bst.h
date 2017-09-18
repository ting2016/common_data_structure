#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
namespace yao{
    namespace bst{
        template <typename T>
        class Node{
        public:
            Node() = delete;
            Node(const T& e)
                : m_data(e){
            }

            const T& getElem() const{
                return m_data;
            }

            bool isLeaf() const{
                if(m_left)
                    return false;
                if(m_right)
                    return false;
                return true;
            }

            bool hasLeftChild() const{
                return m_left;
            }

            bool hasRightChild() const{
                return m_right;
            }
        private:
            T m_data;
            Node<T>* m_left;
            Node<T>* m_right;

            template <typename TT> friend class BST;
        };

        template <typename T>
        class BST
        {
        public:
            BST()
                : root(nullptr){
            }

            void insert(const T& e){
                if(root){
                    insert(root, e);
                }else{
                    root = new Node<T>(e);
                }
            }

            bool find(const T& e) const{
                return find(root, e);
            }

            void remove(const T& e) throw (std::exception){
                root = remove(root, e);
            }

            void print() const{
                std::cout << "---------------" << std::endl;
                print(root);
            }

        private:

            Node<T>* remove(Node<T>* node, const T& e){
                if(node){
                    if(node->m_data > e){
                        node->m_left = remove(node->m_left, e);
                    }else if(node->m_data < e){
                        node->m_right = remove(node->m_right, e);
                    }else{  //node->m_data == e
                        if(node->isLeaf()){ //does not have any child
                            delete node;
                            node = nullptr;
                        }else if(node->hasLeftChild() && node->hasRightChild()){ //has two children
                            auto rightMin = findMin(node->m_right);
                            node->m_data = rightMin->m_data;
                            remove(node->m_right, node->m_data);
                        }else if(node->hasLeftChild()){  //only left child, no right child
                            auto delNode = node;
                            node = node->m_left;
                            delete delNode;
                        }else{  //only right child, no left child
                            auto delNode = node;
                            node = node->m_right;
                            delete delNode;
                        }
                    }
                    return node;
                }else{  //node is null
                    throw std::exception(); //did not find target element
                }
            }

            Node<T>* findMin(Node<T>* node)
            {
                if(node){
                    if(node->hasLeftChild()){
                        return findMin(node->m_left);
                    }else{
                        return node;
                    }
                }
                return nullptr;
            }

            void insert(Node<T>* node, const T& e){
                if(node->m_data < e){   //put to the right side
                    if(node->m_right){  //has right child
                        insert(node->m_right, e);
                    }else{
                        node->m_right = new Node<T>(e);
                    }
                }else{  //put to the left side
                    if(node->m_left){  //has right child
                        insert(node->m_left, e);
                    }else{
                        node->m_left = new Node<T>(e);
                    }
                }
            }


            bool find(const Node<T>* node, const T& e) const{
                if(node){
                    if(node->m_data == e){
                        return true;
                    }

                    if(node->m_data < e){
                        return find(node->m_left, e);
                    }

                    if(node->m_data > e){
                        return find(node->m_right, e);
                    }
                }
                return false;
            }

            void print(const Node<T>* const node) const{
                if(node){
                    std::cout << node->m_data << std::endl;
                    print(node->m_left);
                    print(node->m_right);
                }
            }


        private:
            Node<T>* root;
        };
    }
}

#endif // BST_H
