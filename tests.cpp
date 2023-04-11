#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Hashmap.h"
#include "HashmapInterface.h"

int count_buckets(const Hashmap &map) {
    return map.numBuckets();
}

void test_get(const Hashmap &map, const std::string &key) {
    try {
        int val = map.get(key);
        std::cout << "map.get(\"" << key << "\") = " << val << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << "map.get(\"" << key << "\") threw an invalid_argument exception" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "map.get(\"" << key << "\") threw an exception: " << e.what() << std::endl;
    }
}

void test_insert(Hashmap &map, std::string key, int val) {
    std::cout << "Inserting (\"" << key << "\", " << val << ") into map..." << std::endl;
    map.insert(key, val);
}

void test_contains(const Hashmap &map, const std::string &key) {
    std::cout << "map.contains(\"" << key << "\") = " << std::boolalpha << map.contains(key) << std::endl;
}

void test_operator_get(Hashmap &map, std::string key) {
    std::cout << "map[\"" << key << "\"] = " << map[key] << std::endl;
}

void test_operator_set(Hashmap &map, std::string key, int val) {
    std::cout << "Setting map[\"" << key << "\"] to " << val << "..." << std::endl;
    map[key] = val;
}

void test_remove(Hashmap &map, const std::string &key) {
    std::cout << "map.remove(\"" << key << "\") = " << std::boolalpha << map.remove(key) << std::endl;
}

void test_size(const Hashmap &map) {
    std::cout << "map.size() = " << map.size() << std::endl;
}

void test1() {
    std::cout << "--- Test 1 output ---\n" << std::endl;

    Hashmap map;

    test_get(map, "apple");
    test_get(map, "orange");
    test_get(map, "banana");
    test_get(map, "blueberry");
    std::cout << std::endl;

    test_insert(map, "apple", 3);
    test_insert(map, "orange", 5);
    test_insert(map, "banana", 11);
    std::cout << std::endl;

    test_get(map, "apple");
    test_get(map, "orange");
    test_get(map, "banana");
    test_get(map, "blueberry");
    std::cout << std::endl;

    test_insert(map, "apple", 4);
    test_get(map, "apple");
}

void test2() {
    std::cout << "--- Test 2 output ---\n" << std::endl;

    Hashmap map;

    test_insert(map, "one", 1);
    test_insert(map, "four", 1);
    test_insert(map, "five", 1);
    test_insert(map, "six", 1);
    test_insert(map, "seven", 1);
    test_insert(map, "nine", 1);
    std::cout << std::endl;

    test_contains(map, "one");
    test_contains(map, "two");
    test_contains(map, "three");
    test_contains(map, "four");
    test_contains(map, "five");
    test_contains(map, "six");
    test_contains(map, "seven");
    test_contains(map, "eight");
    test_contains(map, "nine");
    test_contains(map, "ten");
}

void test3() {
    std::cout << "--- Test 3 output ---\n" << std::endl;

    Hashmap map;

    test_operator_get(map, "Computer Science: Bioinformatics (BS)");
    test_operator_get(map, "Computer Science: Software Engineering (BS)");
    std::cout << std::endl;

    test_operator_set(map, "Computer Science (BS)", 1);
    test_operator_set(map, "Computer Science: Animation and Games (BS)", 2);
    test_operator_set(map, "Computer Science: Bioinformatics (BS)", 3);
    test_operator_set(map, "Computer Science: Data Science (BS)", 4);
    test_operator_set(map, "Computer Science: Software Engineering (BS)", 5);
    std::cout << std::endl;

    test_operator_get(map, "Computer Science (BS)");
    test_operator_get(map, "Computer Science: Animation and Games (BS)");
    test_operator_get(map, "Computer Science: Bioinformatics (BS)");
    test_operator_get(map, "Computer Science: Data Science (BS)");
    test_operator_get(map, "Computer Science: Software Engineering (BS)");
    std::cout << std::endl;

    test_operator_set(map, "Computer Science (BS)", 18);
    test_operator_get(map, "Computer Science (BS)");
}

void test4() {
    std::cout << "--- Test 4 output ---\n" << std::endl;

    Hashmap map;

    test_operator_set(map, "dog", 1);
    test_operator_set(map, "cat", 1);
    test_operator_set(map, "horse", 1);
    test_operator_set(map, "cow", 1);
    test_operator_set(map, "sheep", 1);
    test_operator_set(map, "pig", 1);
    std::cout << std::endl;

    test_remove(map, "cat");
    test_remove(map, "sheep");
    test_remove(map, "octopus");
    test_remove(map, "wolf");
    std::cout << std::endl;

    test_get(map, "dog");
    test_get(map, "cat");
    test_get(map, "horse");
    test_get(map, "cow");
    test_get(map, "sheep");
    test_get(map, "pig");
    test_get(map, "octopus");
    test_get(map, "wolf");
}

void test5() {
    std::cout << "--- Test 5 output ---\n" << std::endl;

    Hashmap map;

    test_insert(map, "one", 1);
    test_insert(map, "two", 1);
    test_insert(map, "three", 1);
    test_insert(map, "four", 1);
    test_insert(map, "five", 1);
    std::cout << std::endl;

    std::cout << "Clearing the map...\n" << std::endl;
    map.clear();

    test_contains(map, "one");
    test_contains(map, "two");
    test_contains(map, "three");
    test_contains(map, "four");
    test_contains(map, "five");
    std::cout << std::endl;

    test_insert(map, "two", 2);
    test_insert(map, "three", 3);
    test_insert(map, "five", 5);
    std::cout << std::endl;

    test_get(map, "zero");
    test_get(map, "one");
    test_get(map, "two");
    test_get(map, "three");
    test_get(map, "four");
    test_get(map, "five");
}

void test6() {
    std::cout << "--- Test 6 output ---\n" << std::endl;

    Hashmap map;

    test_size(map);
    std::cout << std::endl;

    test_insert(map, "chicken", 1);
    test_size(map);
    std::cout << std::endl;

    test_insert(map, "turkey", 1);
    test_size(map);
    std::cout << std::endl;

    test_insert(map, "duck", 1);
    test_size(map);
    std::cout << std::endl;

    test_operator_set(map, "goose", 1);
    test_size(map);
    std::cout << std::endl;

    test_operator_set(map, "rabbit", 1);
    test_size(map);
    std::cout << std::endl;

    test_operator_set(map, "hamster", 1);
    test_size(map);
    std::cout << std::endl;

    test_insert(map, "rabbit", 2);
    test_size(map);
    std::cout << std::endl;

    test_operator_set(map, "chicken", 2);
    test_size(map);
    std::cout << std::endl;

    test_remove(map, "turkey");
    test_size(map);
    std::cout << std::endl;

    test_remove(map, "hamster");
    test_size(map);
    std::cout << std::endl;

    test_remove(map, "bear");
    test_size(map);
    std::cout << std::endl;

    std::cout << "Clearing the map..." << std::endl;
    map.clear();
    test_size(map);
    std::cout << std::endl;

    test_insert(map, "coyote", 5);
    test_size(map);
    std::cout << std::endl;

    test_operator_set(map, "shark", 7);
    test_size(map);
}

void test7() {
    std::cout << "--- Test 7 output ---\n" << std::endl;

    Hashmap map;

    test_insert(map, "apple", 3);
    test_insert(map, "orange", 5);
    test_insert(map, "banana", 11);
    test_insert(map, "lemon", 8);
    test_insert(map, "lime", 11);
    test_insert(map, "watermelon", 7);
    test_insert(map, "honeydew", 1);
    std::cout << std::endl;

    std::cout << "map has " << count_buckets(map) << " buckets" << std::endl;
    std::cout << std::endl;

    test_insert(map, "nectarine", 19);
    test_insert(map, "pear", 7);
    std::cout << std::endl;

    std::cout << "map has " << count_buckets(map) << " buckets" << std::endl;
    std::cout << std::endl;

    test_insert(map, "mango", 3);
    test_insert(map, "kiwi", 6);
    test_insert(map, "strawberry", 18);
    test_insert(map, "raspberry", 5);
    test_insert(map, "date", 2);
    test_insert(map, "tangerine", 5);
    std::cout << std::endl;

    std::cout << "map has " << count_buckets(map) << " buckets" << std::endl;
    std::cout << std::endl;

    test_operator_set(map, "apple", 1);
    test_operator_set(map, "apple", 2);
    test_operator_set(map, "apple", 3);
    test_operator_set(map, "apple", 4);
    test_operator_set(map, "apple", 5);
    test_operator_set(map, "apple", 6);
    test_operator_set(map, "apple", 7);
    test_operator_set(map, "apple", 8);
    test_operator_set(map, "apple", 9);
    test_operator_set(map, "apple", 10);
    test_insert(map, "apple", 11);
    test_insert(map, "apple", 12);
    test_insert(map, "apple", 13);
    test_insert(map, "apple", 14);
    test_insert(map, "apple", 15);
    test_insert(map, "apple", 16);
    test_insert(map, "apple", 17);
    test_insert(map, "apple", 18);
    test_insert(map, "apple", 19);
    test_insert(map, "apple", 20);
    std::cout << std::endl;

    std::cout << "map has " << count_buckets(map) << " buckets" << std::endl;
    std::cout << std::endl;

    test_operator_set(map, "blueberry", 14);
    test_operator_set(map, "cherry", 1);
    std::cout << std::endl;

    std::cout << "map has " << count_buckets(map) << " buckets" << std::endl;
    std::cout << std::endl;

    test_get(map, "apple");
    test_get(map, "orange");
    test_get(map, "banana");
    test_get(map, "lemon");
    test_get(map, "lime");
    test_get(map, "watermelon");
    test_get(map, "honeydew");
    test_get(map, "nectarine");
    test_get(map, "pear");
    test_get(map, "mango");
    test_get(map, "kiwi");
    test_get(map, "strawberry");
    test_get(map, "raspberry");
    test_get(map, "date");
    test_get(map, "tangerine");
    test_get(map, "blueberry");
    test_get(map, "cherry");
}

void test8() {
    std::cout << "--- Test 8 output ---\n" << std::endl;

    Hashmap map;

    std::cout << "Reading in 1Nephi.txt" << std::endl;
    std::string input;
    try {
        std::ifstream fin("1Nephi.txt");
        fin.exceptions(std::ios_base::badbit);

        const size_t BUFFER_SIZE = 4096;
        char buf[BUFFER_SIZE];

        fin.read(buf, BUFFER_SIZE);
        while (!fin.eof()) {
            input.append(buf, BUFFER_SIZE);
            fin.read(buf, BUFFER_SIZE);
        }
        input.append(buf, fin.gcount());

        fin.close();
    } catch (const std::ifstream::failure &e) {
        std::cerr << "Failed to read from 1Nephi.txt" << std::endl;
        return;
    }
    std::cout << std::endl;

    size_t starting_index = 0;
    size_t index;
    for (index = 0; index < input.size(); ++index) {
        if (std::isspace(input[index]) || input[index] == ',' || input[index] == '.' || input[index] == ';' ||
            input[index] == ':' || input[index] == '?' || input[index] == '!') {
            if (starting_index != index) {
                ++map[input.substr(starting_index, index - starting_index)];
            }
            starting_index = index + 1;
        }
        if (index % 10000 == 9999) {
            std::cout << index + 1 << " characters into 1Nephi.txt, map has " << map.size()
                      << " distinct words distributed among " << count_buckets(map) << " buckets" << std::endl;
        }
    }
    if (starting_index != index) {
        ++map[input.substr(starting_index, index - starting_index)];
    }

    std::cout << "After having read 1Nephi.txt, map has " << map.size() << " distinct words distributed among "
              << count_buckets(map) << " buckets" << std::endl << std::endl;

    test_get(map, "Nephi");
    test_get(map, "Israel");
    test_get(map, "behold");
    test_get(map, "I");
    test_get(map, "the");
}

void test9() {
    std::cout << "--- Test 9 output ---\n" << std::endl;

    Hashmap map;

    std::cout << "Reading in words.txt" << std::endl;
    std::vector<std::string> dictionary;
    try {
        std::ifstream fin("words.txt");
        fin.exceptions(std::ios_base::badbit);

        std::string word;
        while (std::getline(fin, word)) {
            dictionary.push_back(word);
        }

        fin.close();
    } catch (const std::ifstream::failure &e) {
        std::cerr << "Failed to read from words.txt" << std::endl;
        return;
    }
    std::cout << std::endl;

    int words_inserted = 0;
    for (const std::string &word: dictionary) {
        ++words_inserted;
        map.insert(word, 1);
        if (words_inserted % 500 == 0) {
            std::cout << words_inserted << " words into the dictionary, map.size() = " << map.size() << " and map has "
                      << count_buckets(map) << " buckets" << std::endl;
        }
    }
    std::cout << std::endl;

    bool found_missing_word = false;
    for (const std::string &word: dictionary) {
        if (!map.contains(word)) {
            found_missing_word = true;
            std::cout << "ERROR: expected " << word << " to be in the dictionary, but map.contains(\"" << word
                      << "\") returned false" << std::endl;
        }
    }
    if (found_missing_word) {
        std::cout << std::endl;
    }

    int words_removed = 0;
    for (const std::string &word: dictionary) {
        ++words_removed;
        map.remove(word);
        if (words_removed % 500 == 0) {
            std::cout << "After having removed " << words_removed << " words from the dictionary, map.size() = "
                      << map.size() << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [TEST]" << std::endl;
        std::cerr << "where TEST is in the range of 1-9 or all" << std::endl;
        return 1;
    }

    std::string test = argv[1];

    if (test == "1") {
        test1();
    } else if (test == "2") {
        test2();
    } else if (test == "3") {
        test3();
    } else if (test == "4") {
        test4();
    } else if (test == "5") {
        test5();
    } else if (test == "6") {
        test6();
    } else if (test == "7") {
        test7();
    } else if (test == "8") {
        test8();
    } else if (test == "9") {
        test9();
    } else if (test == "all") {
        test1();

        std::cout << "\n\n";
        test2();

        std::cout << "\n\n";
        test3();

        std::cout << "\n\n";
        test4();

        std::cout << "\n\n";
        test5();

        std::cout << "\n\n";
        test6();

        std::cout << "\n\n";
        test7();

        std::cout << "\n\n";
        test8();

        std::cout << "\n\n";
        test9();
    } else {
        std::cerr << test << " is not a valid test to run. The valid options are any number in the range 1-9 and all"
                  << std::endl;
        return 1;
    }

    return 0;
}
