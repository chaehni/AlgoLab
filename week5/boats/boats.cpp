#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Boat{
    int ring;
    int length;
};

int compare_boats(Boat b1, Boat b2){
    return b1.ring - b1.length < b2.ring - b2.length;
}

void run(){
    int n; cin >> n;
    vector<Boat> boats (n);

    for (int i = 0; i < n; i++){
        cin >> boats[i].length;
        cin >> boats[i].ring;
    }

    // sort boats by earliest finish length optimistically (putting the boat completely to the left of the ring)
    sort(boats.begin(), boats.end(), compare_boats);

    // iterate over boats in sorted order
    // we were optimistic, so check if boat can really be taken
    int right_end = INT32_MIN;
    int count = 0; //first boat can always be placed such that right end is at 0

    for (auto b: boats){
        if (right_end <= b.ring){  // we can place boat
            right_end = max(right_end + b.length, b.ring);
            count++;
        }
    }

    cout << count << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}