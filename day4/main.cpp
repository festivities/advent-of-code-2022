#include <cstdio>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]){
    auto startTime = std::chrono::high_resolution_clock::now();

    std::FILE *inputFile = std::fopen(argv[1], "r+");

    if(inputFile != 0){
        std::pair<int, int> range;
        std::pair<std::pair<int, int>, std::pair<int, int>> sectionPair;
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> section;

        char inputChara;
        std::vector<int> buf;
        std::string x;
        while(std::fscanf(inputFile, "%c", &inputChara) != EOF){
            if(std::isdigit(inputChara))
                x += inputChara + '\0'; // unironically spent two hours on this just because I forgot about not having a null terminator
            else{
                buf.push_back(std::stoi(x));
                x.clear();

                if(inputChara == '\n'){
                    range.first = buf[0]; range.second = buf[1];
                    sectionPair.first = range;

                    range.first = buf[2]; range.second = buf[3];
                    sectionPair.second = range;

                    section.push_back(sectionPair);

                    buf.clear();
                }
            }
        }

        unsigned int containCount = 0, overlapCount = 0;
        for(const auto &pair : section){
            if((pair.first.first >= pair.second.first && pair.first.second <= pair.second.second)
               || (pair.first.first <= pair.second.first && pair.first.second >= pair.second.second)){
                ++containCount;
            }
            if(pair.first.first <= pair.second.second && pair.first.second >= pair.second.first){
                ++overlapCount;
            }
        }

        std::printf("The number of assignment pairs where one range fully contains the other is %u!\n"
                    "The number of assignment pairs where the ranges overlap is %u!", containCount, overlapCount);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = endTime - startTime;
        std::printf("\n------------------------------------\nExecution time: %f milliseconds", duration.count());

        return 0;
    }

    std::perror("Error");
    return 1;
}
