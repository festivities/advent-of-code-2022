#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>

int main(int argc, char *argv[]){
    auto startTime = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile(argv[1]);

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
        const char priorityList[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int prioritySum = 0;

        for(std::vector<std::vector<std::string>>::const_reference index : rucksacks){
            // compare the compartments' lengths of each rucksack in rucksacks
            if(index[0].length() == index[1].length()){ // just to be safe =)
                // for every item in first compartment, use said item to find the common element in second compartment
                for(const char &x : index[0]){
                    if(index[1].find(x) != std::string::npos){
                        itemType = x;

                        for(std::size_t y = 0; y < 52; ++y){
                            if(itemType == priorityList[y]){
                                prioritySum += static_cast<int>(++y);
                            }
                        }

                        // this very important!!!! spent an hour suffering bc i forgot this keyword aaaaaaaaaaaaaaaaaaaaaaaaaaa
                        break;
                    }
                }
            }
        }

        std::cout << "Sum of all the priorities is: " << prioritySum << "!\n----------------------------------------\n";

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = endTime - startTime;
        std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

        return 0;
    }

    std::cerr << "Usage: \"day3.exe input.txt\"" << std::endl;
    return 1;
}
