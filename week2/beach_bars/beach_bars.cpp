#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

void run(){
    int n; cin >> n;
    vector<int> sols(n);

    for (int i = 0; i < n; i++){
        int temp; cin >> temp;
        sols[i] = temp;
    }
    //sort the sols ascending
    sort(sols.begin(), sols.end());

    //map the sols to new array such that first sol is at position zero (shift sols by -min)
    int min = sols[0];
    int max = sols[sols.size()-1];
    vector<int> counts(max-min+1, 0);
    for (int e: sols){
        counts[e-min] = 1;
    }
    
    //compute partial sums
    vector<int> part_sums(max-min+1, 0);
    int temp = 0;
    for (int i = 0; i < part_sums.size(); i++){
        temp += counts[i];
        part_sums[i] = temp;
    }
    
    //for each coordinate calculate the number of sols within radius of 100m
    vector<int> numbers(max-min+1);
    for (int i = 0; i < part_sums.size(); i++){
        
        //left-right overlap
        if (part_sums.size() < 201){
            numbers[i] = part_sums[part_sums.size()-1]; //all sols
            continue;
        }

        //left overlap
        if (i < 100+1){
            numbers[i] = part_sums[i+100]; //all sols to the left, 100 meters to the right
            continue;
        }

        //right overlap
        if (i+100 > part_sums.size()-1){
            numbers[i] = part_sums[part_sums.size()-1] - part_sums[i-100-1]; // 100 meters to the left, all to the right
            continue;
        }

        //no overlap
        numbers[i] = part_sums[i+100] - part_sums[i-100-1]; // 100 meters to the left and right
    }

    //find places with max number of parasols
    int max_sols = 0;
    int loc = 0;
    set<int> locations;
    for (int e: numbers){
        if (e > max_sols){
            max_sols = e;
            locations.clear();
            locations.insert(loc);
        }else if(e == max_sols){
            locations.insert(loc);
        }
        loc++;
    }

    //of potential places keep the ones with minimal maximum distance
    //UGLY SOLUTION O(200*n)
    int max_dist = 100;
    set<int> finish;
    for (auto e: locations){
            
        int dist;
        //left and right overlap
        int left_boundary = (e-100 < 0 ? 0 : e-100);
        int right_boundary = (e+100 >= counts.size() ? counts.size()-1 : e+100);

        int dist_left = 100;
        int dist_right = 100;
        while(left_boundary <= e){
            if (counts[left_boundary]){
                dist_left = abs(left_boundary-e);
                break;
            }
            left_boundary++;
        }

        while(right_boundary >= e){
            if (counts[right_boundary]){
                dist_right = abs(right_boundary-e);
                break;
            }
            right_boundary--;
        }

        dist = (dist_left >= dist_right ? dist_left : dist_right);

        //update finish set
        if (dist < max_dist){
            max_dist = dist;
            finish.clear();
            finish.insert(e);
        } else if (dist == max_dist){
            finish.insert(e);
        }

    }

    cout << max_sols << " " << max_dist << "\n";
    for (auto e: finish){
        cout << e+min << " ";
    }
    cout << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}