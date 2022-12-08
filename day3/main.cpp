#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

int main(int argv, char *argc[]){
    auto startTime = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile(argc[1]);

    if(inputFile.is_open()){
        std::string firstCompartment, secondCompartment;
        std::vector<std::string> rucksack;
        std::vector<std::vector<std::string>> rucksacks;

        for(std::string inputString; inputFile >> inputString; ){
            for(std::size_t index = 0; index < (inputString.length() / 2); ++index){
                firstCompartment.append(inputString, index, std::size_t(1));
            }
            for(std::size_t index = (inputString.length() / 2); index != inputString.size(); ++index){
                secondCompartment.append(inputString, index, std::size_t(1));
            }
            rucksack.push_back(firstCompartment); rucksack.push_back(secondCompartment); rucksacks.push_back(rucksack);
            firstCompartment.clear(); secondCompartment.clear(); rucksack.clear();
        }

        char itemType;
        char priorityList[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for(std::vector<std::vector<std::string>>::const_reference index : rucksacks){
            // compare the compartments' lengths of each rucksack in rucksacks
            if(index[0].length() == index[1].length()){ // just to be safe =)
                // for every item in the first compartment, use said item to find a common element in the second compartment
                for(const char &buf : index[0]){
                    if(index[1].find(buf) != std::string::npos){
                        itemType = buf;
                    }
                }
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = endTime - startTime;
        std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

        return 0;
    }

    std::cerr << "balls" << std::endl;
    return 1;
}
