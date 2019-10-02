#include <iostream>
#include <vector>
#include <algorithm>

// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

struct Participant
{
    Point p;
    K::FT r;
};

void run()
{
    int m, n;
    K::FT h;
    cin >> m >> n;

    vector<Participant> parts(m);
    for (int i = 0; i < m; i++)
        cin >> parts[i].p >> parts[i].r;

    cin >> h; // triangle is isosceles -> the radius on the stage is also h

    Triangulation t;
    vector<Point> lights(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        lights[i] = Point(x, y);
    }
    t.insert(lights.begin(), lights.end());

    vector<pair<int, int>> elimination_time(m);
    //int winner_time = 0;
    bool test_all = true;
    for (int i = 0; i < m; i++)
    {
        bool eliminated = true;
        int min_time = INT32_MAX;

        // first see if player gets eliminated at all
        auto nearest = t.nearest_vertex(parts[i].p);
        if (CGAL::squared_distance(nearest->point(), parts[i].p) >= CGAL::square(h + parts[i].r))
            test_all = false;
        else if (!test_all)
            min_time = 0;

        if (test_all)
        {
            // we have to test all lights
            for (int j = 0; j < n; j++)
            {
                K::FT dist = CGAL::squared_distance(lights[j], parts[i].p);
                if (dist < CGAL::square(h + parts[i].r))
                    min_time = min(min_time, j);
            }
        }

        elimination_time[i] = make_pair(min_time, i);
    }

    // sort vector first by decreasing kill time and for same time by increasing player index
    sort(elimination_time.begin(), elimination_time.end(), [](pair<int, int> p1, pair<int, int> p2) {
        return (p1.first > p2.first || (p1.first == p2.first) && p1.second < p2.second);
    });

    for (int i = 0; i < m; i++)
    {
        if (elimination_time[i].first == elimination_time[0].first)
            cout << elimination_time[i].second << " ";
        else
            break;
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}