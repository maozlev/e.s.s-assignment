//Question 1 - basic STL

//Task 1: improve fill_vector and vecOfVec.push_back performance - execution time can be reduced significantly,
// please explain the changes you made and how they improve
// the application performance.

//Task 2: Implement count_total_elements without using a "visible" for loop

//Task 3: Implement merge_vec_of_vec

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify ELEMENT_COUNT and ITERATIONS and functions fill_vector,count_total_elements and merge_vec_of_vec function signatures

#include <chrono>
#include <iostream>
#include <vector>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
    //TODO: improve function performance
    // Vectors are allocate for each push (on power of 2: 1,2,4,8,16....)
    // That's why I need to choose between 2 options:
    // 1) Reallocate place for the vector with reserve() before and then push_back or emplace_back (emplace_back was slow..)
    //    push_back makes copies on the stack and on the vector address
    // 2) Do vector element assignment - give the size and then assign the elements by index and assign the element
    //    in the address without any copy.

    /// method 1: Average iteration duration in microseconds: 116725
//    std::vector<uint64_t> vec;
//    vec.reserve(elementCount);
//    for (size_t i = 0; i < elementCount; i++) {
//        vec.push_back(i);
//    }

    /// method 2: Average iteration duration in microseconds: 77200
    std::vector<uint64_t> vec(elementCount);
    for (size_t i = 0; i < elementCount; i++) {
        vec[i]=i;
    }
    return vec;
}

/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
    size_t total_elements=0, tmp=0;
    total_elements = (vecOfVec.end() - vecOfVec.begin()) * ELEMENT_COUNT;
    return total_elements;
    //TODO: replace with your code
    // I just need to know the begin and end addresses then multiply by ELEMENT_COUNT for each vector
}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
    std::vector<uint64_t> mergedVec;
    mergedVec.reserve(ITERATIONS * ELEMENT_COUNT); // reallocate memory
    for(std::vector<size_t> v: vecOfVec){
        mergedVec.insert(mergedVec.end(),v.begin(), v.end());
    }
    //TODO: Your code here
    // for loop that get each vector and insert his variables to the mergeVec

    return mergedVec;
}

int main(int argc, char** argv)
{
    //Create vector of vectors
    std::vector<std::vector<uint64_t>> vecOfVec(ITERATIONS);
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < ITERATIONS; i++) {
        std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
        //TODO: improve inserting performance
        // use the assigment method
//        vecOfVec.push_back(vec);
        vecOfVec[i] = vec;
    }
    auto end = std::chrono::steady_clock::now();
    size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
    std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

    //Count elements
    size_t totalElements = count_total_elements(vecOfVec);
    std::cout << "Total elements in vecOfVec: " << totalElements <<  " " << std::endl;

    //Merge vector of vectors
    std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
    std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}