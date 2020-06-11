#include <iostream>
#include <chrono>
#include <random>
#include <map>
#include <unordered_set>
#include <climits> // for min/max int

//#include <string>
// #include <cstdlib>

//#include <fstream>


#include "CLI11.hpp"

// function prototypes
void randomNumberMaker(std::set<int>& randomNumbers, const int& howManyNumbers, const int& maxPossible);

// what are best practices for parsing words from an external file?
std::vector<std::string> wordDictionary = { "Apple", "Banana", "Carrot", "Daikon", "Eggplant", "Fennel", "Ginger" };


// add built-in dictionary options
// check out dict/dictd and goldendict on arch linux
// sounds like a good idea to be compatible with dictd formats!

// next feature:
// need a source of randomness
// need a selection method (use randomness to choose the words)


int main(int argc, char** argv)
{
    CLI::App app{
            "\n  OxPig: Oliver's Xkcd Password Idea Generator"
            "\n  Source code: <http://github.com/oliverocean/oxpig>"
            "\n  Released under the GNU GPL, 2020\n"};

    // add a range option -L in addition... OR replacing max/min? 'Range(min=1, max)'
    unsigned int minimumWordLength = 4;
    unsigned int maximumWordLength = 8;
    app.add_option("-m,--min", minimumWordLength, "Minimum word length", true);
    app.add_option("-M,--max", maximumWordLength, "Maximum word length", true);

    unsigned int wordCount = 4;
    app.add_option("-w,--wc", wordCount, "Total number of words", true);

    std::string dictionarySource = "../data/dictionaries/MobyList/FREQ.TXT";
    app.add_option("-d,--dict", dictionarySource, "Dictionary source file")->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv); // macro with try/catch block from CLI11.hpp


    // stream in dictionary
    std::ifstream dictSrc{dictionarySource, std::ios::in};
    if (!dictSrc)
    {
        std::cerr << "File could not be opened.\n";
        exit(EXIT_FAILURE);
    }

    std::string aWord;
    int countKeeps = 0;
    int countRejects = 0;
    int countDuplicates = 0;
    std::unordered_set<std::string> wordChecker;
    std::map<int, std::string> wordListMap;

    while (dictSrc >> aWord)
    {
        if (aWord.size() >= minimumWordLength && aWord.size() <= maximumWordLength)
        {
            if (wordChecker.find(aWord) != wordChecker.end())
            {
                ++countDuplicates;
            }
            else
            {
                wordChecker.insert(aWord);
                wordListMap.insert(std::make_pair(wordListMap.size(), aWord));
                ++countKeeps;
            }
        }
        else
        {
            ++countRejects;
        }
    }

    // make random numbers

    std::set<int> randomNumbers;
    int howManyNumbers = wordCount;
    int maxPossible = 100;
    randomNumberMaker(randomNumbers, howManyNumbers, maxPossible);

    std::cout << " >> Set    [ ";
    for (auto r : randomNumbers)
    {
        std::cout << r << ", ";
    }
    std::cout << "]\n";

    std::string res;
    std::cout << " >> Result [ ";
    for (auto r : randomNumbers)
    {
        std::cout << wordListMap.find(r)->second;
    }

    std::cout << " ]\n";

    std::cout << "Arguments:\n";
    std::cout << "wc: " << wordCount << "\n";
    std::cout << "min: " << minimumWordLength << "\n";
    std::cout << "max: " << maximumWordLength << "\n";
    std::cout << "dict: " << dictionarySource << "\n";
    std::cout << "\n > kept: " << countKeeps << "\n";
    std::cout << " > rejected: " << countRejects << "\n";
    std::cout << " > duplicates: " << countDuplicates << "\n";
    std::cout << " > set size: " << wordChecker.size() << "\n";
    std::cout << " > map size: " << wordListMap.size() << "\n";

    return 0;
}

void randomNumberMaker(std::set<int>& randomNumbers, const int& howManyNumbers, const int& maxPossible)
{
    // <---[ SEED ]---> //
    // start time measurement immediately (to produce larger value)
    typedef std::chrono::high_resolution_clock aHighResolutionClock;
    aHighResolutionClock::time_point aTimePoint = aHighResolutionClock::now();

    std::cout << "\nPress <ENTER> key to continue...\n";
    std::cin.get();

    // finish time measurement; generate duration-based seed
    aHighResolutionClock::duration aDuration = aHighResolutionClock::now() - aTimePoint;
    auto aDurationSeed = static_cast<unsigned int>(aDuration.count());

    // <---[ DISTRIBUTION ]---> //
    int low = 0;
    int high = maxPossible;
    std::uniform_int_distribution<int> aDistribution{low, high};

    // <---[ GENERATOR ]---> //
    std::default_random_engine anEngine;
    anEngine.seed(aDurationSeed);
    auto aGenerator = [&]() { return aDistribution(anEngine); };

    // <---[ POPULATE AND RETURN SET ]---> //
    while (randomNumbers.size() < howManyNumbers)
    {
        randomNumbers.insert(aGenerator());
    }
}

// EOF
