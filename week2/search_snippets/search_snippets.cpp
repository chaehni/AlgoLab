#include <iostream>
#include <vector>
#include <string>
#include <set>

typedef std::pair<unsigned, unsigned> IntPair;

unsigned doTest()
{
    unsigned n, numbers_count = 0, tmp;
    std::cin >> n;
    std::vector<unsigned> M(n);
    std::set<IntPair> numbers_set;
    for (unsigned i = 0; i < n; ++i)
    {
        std::cin >> M[i];
    }
    for (unsigned i = 0; i < n; ++i)
    {
        for (unsigned j = 0; j < M[i]; ++j)
        {
            std::cin >> tmp;
            numbers_set.insert(IntPair(tmp, i));
        }
        numbers_count += M[i];
    }
    // numbers_vector is an array of:
    // <position_in_file, word_at_the_position>
    // as all positions are unique, it will be properly sorted here
    std::vector<IntPair> numbers_vector(numbers_set.begin(), numbers_set.end());

    // the vector of current words for the sliding window:
    // current_words[i] = k => there are k occurences of i-th word in
    // [numbers_vector[left].first ; numbers_vector[right].first]
    std::vector<int> current_words(n);
    unsigned left = 0, right = 0,
             best_result = numbers_vector.back().first - numbers_vector[0].first + 1;
    current_words[numbers_vector[0].second] = 1;

    // the number of different words in current_words
    unsigned words_in_set = 1;
    while (right < numbers_vector.size())
    {
        if (words_in_set == n)
        {
            // the set already contains all numbers
            unsigned cur_result =
                numbers_vector[right].first - numbers_vector[left].first + 1;
            if (cur_result < best_result)
            {
                best_result = cur_result;
            }
            tmp = --current_words[numbers_vector[left].second];
            if (tmp == 0)
            {
                --words_in_set;
            }
            ++left;
        }
        else
        {
            if (++right == numbers_vector.size())
            {
                break;
            }
            tmp = current_words[numbers_vector[right].second]++;
            if (!tmp)
            {
                ++words_in_set;
            }
        }
    }
    return best_result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    unsigned test_count;
    std::cin >> test_count;
    for (unsigned i = 0; i < test_count; ++i)
    {
        std::cout << doTest() << "\n";
    }
    return 0;
}