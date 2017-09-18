#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "singlelinkedlist.h"
#include "doublelinkedlist.h"
#include "stack.h"
#include "queue.h"
#include "heapsort.h"
#include "hashmap.h"
#include "priorityqueue.h"
class BaseClass{
public:
    BaseClass()
        : BaseClass(0){
        std::cout << "BaseClass() is called" << std::endl;
    }

    BaseClass(unsigned int size){
        std::cout << "BaseClass(unsigned int) is called" << std::endl;
        m_size1 = size;
        if(m_size1 > 0){
            m_data1 = new char[m_size1];
            std::cout << "\tm_data1 newed:" << (void*)m_data1 << std::endl;
        }else{
            m_data1 = nullptr;
        }
    }

    BaseClass(const BaseClass& other){
        std::cout << "BaseClass(const BaseClass& other) is called" << std::endl;
        this->m_size1 = other.m_size1;
        if(m_size1 > 0){
            m_data1 = new char[m_size1];
            std::cout << "\tm_data1 newed:" << (void*)m_data1 << std::endl;
        }else{
            m_data1 = nullptr;
        }
    }

    BaseClass(BaseClass&& other){
        std::cout << "BaseClass(BaseClass&& other) is called" << std::endl;
        this->m_size1 = other.m_size1;
        if(m_size1 > 0){
            m_data1 = other.m_data1;
            other.m_data1 = nullptr;
            other.m_size1 = 0;
        }else{
            m_data1 = nullptr;
        }
    }

    BaseClass& operator=(const BaseClass& other){
        std::cout << "operator()(const BaseClass&) is called" << std::endl;
        if(&other != this){
            if(m_data1){
                std::cout << "\toperator=(const BaseClass& other)\tm_data1 deleted:" << (void*)m_data1 << std::endl;
                delete []m_data1;
            }
            m_size1 = other.m_size1;
            if(m_size1 > 0){
                m_data1 = new char[m_size1];
                std::cout << "\tm_data1 newed:" << (void*)m_data1 << std::endl;
            }else{
                m_data1 = nullptr;
            }
        }
        return *this;
    }

    BaseClass& operator=(BaseClass&& other){
        std::cout << "operator()(BaseClass&&) is called" << std::endl;
        this->m_size1 = other.m_size1;
        if(&other != this){
            if(m_data1){
                std::cout << "\toperator=(BaseClass&& other)\tm_data1 deleted:" << (void*)m_data1 << std::endl;
                delete []m_data1;
            }
            if(m_size1 > 0){
                m_data1 = other.m_data1;
                other.m_data1 = nullptr;
                other.m_size1 = 0;
            }else{
                m_data1 = nullptr;
            }
        }
        return *this;
    }

    virtual ~BaseClass(){
        std::cout << "~BaseClass() is called" << std::endl;
        if(m_data1){
            std::cout << "\t~BaseClass()\tm_data1 deleted:" << (void*)m_data1 << std::endl;
            delete []m_data1;
        }
        m_size1 = 0;
    }

protected:
    char* m_data1;
    unsigned int m_size1;
};

class DerivedClass: public BaseClass{
public:
    DerivedClass()
        : DerivedClass(0, 0){
        std::cout << "DerivedClass() is called" << std::endl;
    }

    DerivedClass(unsigned int size1, unsigned int size2)
        : BaseClass(size1){
        std::cout << "DerivedClass(unsigned int, unsigned int) is called" << std::endl;
        m_size2 = size2;
        if(m_size2 > 0){
            m_data2 = new char[m_size2];
            std::cout << "\tm_data2 newed:" << (void*)m_data2 << std::endl;
        }else{
            m_data2 = nullptr;
        }
    }

    DerivedClass(const DerivedClass& other)
        : BaseClass(other){
        std::cout << "DerivedClass(const DerivedClass& other) is called" << std::endl;
        this->m_size2 = other.m_size2;
        if(m_size2 > 0){
            m_data2 = new char[m_size2];
            std::cout << "\tm_data2 newed:" << (void*)m_data2 << std::endl;
        }else{
            m_data2 = nullptr;
        }
    }

    DerivedClass(DerivedClass&& other)
        : BaseClass(std::move(other)){
        std::cout << "DerivedClass(DerivedClass&& other) is called" << std::endl;
        this->m_size2 = other.m_size2;
        if(m_size2 > 0){
            m_data2 = other.m_data2;
            other.m_data2 = nullptr;
            other.m_size2 = 0;
        }else{
            m_data2 = nullptr;
        }
    }

    DerivedClass& operator=(const DerivedClass& other){
        std::cout << "operator()(const DerivedClass&) is called" << std::endl;
        BaseClass::operator =(other);
        if(&other != this){
            if(m_data2){
                std::cout << "\toperator=(const DerivedClass& other)\tm_data2 deleted:" << (void*)m_data2 << std::endl;
                delete []m_data2;
            }
            m_size2 = other.m_size2;
            if(m_size2 > 0){
                m_data2 = new char[m_size2];
                std::cout << "\tm_data2 newed:" << (void*)m_data2 << std::endl;
            }else{
                m_data2 = nullptr;
            }
        }
        return *this;
    }

    DerivedClass& operator=(DerivedClass&& other){
        std::cout << "operator()(DerivedClass&&) is called" << std::endl;
        BaseClass::operator =(std::move(other));
        this->m_size2 = other.m_size2;
        if(&other != this){
            if(m_data2){
                std::cout << "\toperator=(const DerivedClass&& other)\tm_data2 deleted:" << (void*)m_data2 << std::endl;
                delete []m_data2;
            }
            if(m_size2 > 0){
                m_data2 = other.m_data2;
                other.m_data2 = nullptr;
                other.m_size2 = 0;
            }else{
                m_data2 = nullptr;
            }
        }
        return *this;
    }

    virtual ~DerivedClass(){
        std::cout << "~DerivedClass() is called" << std::endl;
        if(m_data2){
            std::cout << "\t~DerivedClass\tm_data2 deleted:" << (void*)m_data2 << std::endl;
            delete []m_data2;
        }
        m_size2 = 0;
    }

protected:
    char* m_data2;
    unsigned int m_size2;
};

class Foo{
public:
    Foo(){
        generateUUID();
    }

    void bar() const{
        std::cout << "my id is:" << id << std::endl;
        //std::cout << std::stol(id) << std::endl;
    }
private:
    std::string id;
    void generateUUID(){
        id = std::to_string(++uniq_id);
    }

    static unsigned uniq_id;
};
unsigned Foo::uniq_id = 0;

void test_ctor(){
    DerivedClass b1(3, 5);
    std::cout << "-----------" << std::endl;
    DerivedClass b2(b1);
    std::cout << "-----------" << std::endl;
    DerivedClass b3 = b1;
    std::cout << "-----------" << std::endl;
    b1 = b2;
    std::cout << "-----------" << std::endl;
    DerivedClass b4(std::move(b1));
    std::cout << "-----------" << std::endl;
    DerivedClass b5 = std::move(b4);
    std::cout << "-----------" << std::endl;
    b4 = std::move(b5);
    std::cout << "finished" << std::endl;
    std::cout << "-----------" << std::endl;
}

namespace bloomberg_interview{
    class FileBase{
        //permition
    };

    class File: FileBase{

    };

    class Fold: FileBase{

    };

    class Node{
    private:
        std::vector<FileBase*> pNodes;
        Node* parent;
    };

    class FileSystem{
    public:
        FileSystem();
        void up();
        void back();
        void forward();
        void go(const std::string& path);
        void deleteNode(Node* pNode);
        void copy(Node* pNode);
        void paste(Node* pNode);
        void cut(Node* pNode);
        void newFile();
        void newFold();
    private:
        Node* currentNode;
        Node* root;
    };
}
int main(){

    yao::hash::test();
    std::cout << "finished" << std::endl;
}
