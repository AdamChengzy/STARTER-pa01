#include <iostream>
#include <fstream>
#include "card_list.h"

int main(int argc, char *argv[]) {
    if(argc < 3) { std::cerr << "Provide two files!" << std::endl; return 1; }
    std::ifstream fa(argv[1]), fb(argv[2]);
    if(!fa || !fb) { std::cerr << "Cannot open files" << std::endl; return 1; }

    CardBST alice, bob;
    char s; std::string v;
    while(fa >> s >> v) alice.insert(Card(s,v));
    while(fb >> s >> v) bob.insert(Card(s,v));

    playGame(alice, bob);
    return 0;
}

