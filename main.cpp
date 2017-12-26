//
//  main.cpp
//  HashMap
//
//  Created by Andrew on 11/23/17.
//  Copyright © 2017 Andrew Golovenko. All rights reserved.
//

#include <iostream>
#include "HashMap.cpp"

int main(int argc, const char * argv[]) {
    HashMap<std::string, std::string> map;
    map.insert("One", "Two");
    map.insert("abc", "def");
    map.print();
    
    std::string s;
    if (map.find("abc", s)) {
        std::cout << s << std::endl;
    }
    
    map.remove("abc");
    map.print();
    return 0;
}
