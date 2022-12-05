#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char *argv[]){
    std::ifstream input(argv[1]);

    if(input.is_open()){
        // this will hold all elves
        std::vector<std::vector<std::string>> elves;
        // this will hold the list of foods carried by an elf
        std::vector<std::string> elf;

        // we won't need buf, so just use a for loop without the third value
        for(std::string buf; std::getline(input, buf); ){
            if(!buf.empty()){
                elf.push_back(buf);
            }
            else{
                // push a std::vector<std::string> element into elves and reset
                elves.push_back(elf);
                elf.clear();
            }
        }

        // now we have each elf and a list of what they're carrying, loop through each element and
        // transform the strings into ints (idk if this is the correct way)
        std::vector<int> newElf;
        unsigned int highestSum = 0;
        unsigned int sum = 0;

        for(const std::vector<std::string> &firstIndex : elves){
            for(const std::string &secondIndex : firstIndex){
                // am i an L for looking this up: https://stackoverflow.com/a/15619758/14514898
                std::stringstream parser(secondIndex);
                int buf;
                parser >> buf;
                sum += buf;
                newElf.push_back(buf);
            }
            // for every iterated std::vector<std::string>, find the greater sum then clear newElf and reset sum
            highestSum = (highestSum > sum) ? highestSum : sum;
            newElf.clear(); sum = 0;
        }

        std::cout << "The elf carrying the most calories has " << highestSum << " total calories." << std::endl;

        return 0;
    }

    std::cerr << "no file argument" << std::endl;
    return 1;
}
