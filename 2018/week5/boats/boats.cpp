#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Boat{
    int ring;
    int length;
};

int compare_boats(Boat b1, Boat b2){
    return b1.ring < b2.ring;
}

void run(){
    int n; cin >> n;
    vector<Boat> boats (n);

    for (int i = 0; i < n; i++){
        cin >> boats[i].length;
        cin >> boats[i].ring;
    }


    // sort boats by ring position
    sort(boats.begin(), boats.end(), compare_boats);

    // just take the boat tied to the first ring
    int right_end = boats[0].ring;
    int right_end_old;
    int count = 1;

    // iterate over boats in increasing ring position
    for (int i = 1; i < n; i++){
        if (boats[i].ring < right_end){ // this boat has potential to finish earlier than current right_end (first postion boats can finish is at their ring position)
            right_end = min(right_end, max(right_end_old + boats[i].length, boats[i].ring)); // check if it really does finish earlier, if yes replace right_end
        } else { // this boat can't replace the one before, take it and update right_end
            right_end_old = right_end;
            right_end = max(right_end_old + boats[i].length, boats[i].ring);
            count ++;
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