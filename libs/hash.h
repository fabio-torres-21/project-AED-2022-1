#include <string>
#include <list>
using namespace std;

// Return a number computed from the bits of the characters in the string s.
unsigned int hash_string(const string& s) {
    unsigned int h = 0;
    for (size_t i = 0; i < s.length(); i++)
        h += s[i];  // oh, how about we just add them all up
    return int(h);
}

const int TABLE_SIZE = 99;

class HashSet {
    list<string> buckets[TABLE_SIZE];  // hi! i'll be your hash table today

    bool lookup(const string& value, bool adding) {
        unsigned int hash = hash_string(value);
        list<string>& bucket = buckets[hash % TABLE_SIZE];

        // Search this hash bucket for the given value.
        for (list<string>::iterator it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == value)
                return true;
        }

        // If we get here, no matching entry was found.
        if (adding)
            bucket.push_front(value);
        return false;
    }

public:
    bool contains(const string& value) {
        return lookup(value, false);
    }

    void add(const string& value) {
        lookup(value, true);
    }
};