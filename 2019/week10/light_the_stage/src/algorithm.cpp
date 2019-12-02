#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

void run()
{
    int m, n;
    K::FT h;
    cin >> m >> n;
    vector<pair<Point, K::FT>> part;
    part.reserve(m);
    vector<Point> lights;
    lights.reserve(n);
    for (int i = 0; i < m; i++)
    {
        int x, y, r;
        cin >> x >> y >> r;
        part.emplace_back(Point(x, y), r);
    }
    cin >> h;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        lights.emplace_back(x, y);
    }

    Triangulation t;
    t.insert(lights.begin(), lights.end());

    // go through all participants and register first light that eliminates them
    // if we find a participant who does not get eliminated, we only need to check the same for subsequent participants
    vector<int> die_times(m, n);
    bool check_all = true;
    for (int i = 0; i < m; i++)
    {
        auto p = part[i];
        K::FT dist = p.second + h;
        if (check_all)
        {
            for (int j = 0; j < n; j++)
            {
                Point l = lights[j];
                if (CGAL::squared_distance(p.first, l) < dist * dist)
                {
                    die_times[i] = j;
                    break;
                }
            }
            if (die_times[i] == n)
                check_all = false;
        }
        else
        {
            // only check if this participant survives completely
            auto nearest = t.nearest_vertex(p.first)->point();
            if (CGAL::squared_distance(p.first, nearest) < dist * dist)
                die_times[i] = 0;
        }
    }

    int winning_time = 0;
    vector<int> winners;
    winners.reserve(m);
    for (int i = 0; i < m; i++)
    {
        if (die_times[i] == winning_time)
        {
            winners.push_back(i);
        }
        else if (die_times[i] > winning_time)
        {
            winning_time = die_times[i];
            winners.clear();
            winners.push_back(i);
        }
    }
    for (int w : winners)
        cout << w << " ";
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}