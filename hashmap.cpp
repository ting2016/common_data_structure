#include "hashmap.h"


unsigned long yao::hash::hashFunc(int key){
    return key % TABLE_SIZE;
}


void yao::hash::test (){
//    typedef unsigned long (*HASH_FUN)(int);
    HashMap1<int, std::string, unsigned long(*)(int)> map(hashFunc);
    map.put(23, "hello");
    map.put(1, "jim");
    std::cout << map.get(23) << std::endl;
    try{
        map.remove(23);
        std::cout << map.get(23) << std::endl;
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }catch(...){
        std::cout << "unknown exception." << std::endl;
    }
}
