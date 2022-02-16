# My solutions to the problems of the Algorithms Lab of ETH Zurich in Fall 2018 and 2019

| Week                  | Problem                         | Points | Solution                                                                                                          |
| --------------------- | ------------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------- |
| C++ intro             | Basic data types                | 100    | types                                                                                                             |
| C++ intro             | BFS                             | 100    | standard BFS                                                                                                      |
| C++ intro             | Build the sum                   | 100    | naive                                                                                                             |
| C++ intro             | DFS                             | 100    | standard DFS                                                                                                      |
| C++ intro             | Hello World                     | 100    | naive                                                                                                             |
| C++ intro             | Maps                            | 100    | maps                                                                                                              |
| C++ intro             | Sets                            | 100    | sets                                                                                                              |
| C++ intro             | Sort                            | 100    | std::sort()                                                                                                       |
| C++ intro             | Strings                         | 100    | strings                                                                                                           |
| C++ intro             | Vectors                         | 100    | vectors                                                                                                           |
| 1                     | Build the sum                   | 100    | naive linear                                                                                                      |
| 1                     | Dominoes                        | 100    | naive linear                                                                                                      |
| 1                     | Even Pairs                      | 100    | Partial sums, binomial coefficient                                                                                |
| 1                     | Even Matrices                   | 100    | dimension reduction & partial sums                                                                                |
| PotW 2 (2018 & 2019)  | Deck of Cards                   | 100    | sliding window                                                                                                    |
| 2                     | Beach Bars                      | 100    | partial sums, sliding window                                                                                      |
| 2                     | Burning Coins                   | 100    | DP, 2 tables                                                                                                      |
| 2                     | Search Snippets                 | 100    | ordering words by occurences, sliding window                                                                      |
| 2                     | The Great Game                  | 100    | recursion & memoization, 2 tables                                                                                 |
| PotW 3 (2018)         | Magician and the Coin           | 100    | recursion & memoization                                                                                           |
| PotW 3 (2019)         | From Russia with Love           | 100    | recursion & memoization                                                                                           |
| 3                     | Hit                             | 100    | intersection                                                                                                      |
| 3                     | First hit                       | 100    | intersection, shuffle input and clip ray to avoid costly intersections                                            |
| 3                     | Antenna                         | 100    | Min_circle                                                                                                        |
| 3                     | Almost antenna                  | 100    | Min_circle, support points                                                                                        |
| PotW 4 (2018)         | Defensive Line                  | 100    | sliding window & DP                                                                                               |
| PotW 4 (2019)         | Chariot Race                    | 100    | recursion and memoization, passing information if current node is covered by parent                               |
| 4                     | Ant Challenge                   | 100    | Kruskal per species, then Dijkstra                                                                                |
| 4                     | Buddy Selection                 | 100    | perfect matching                                                                                                  |
| 4                     | Building a Graph                | 100    | Kurskal, Dijkstra                                                                                                 |
| 4                     | Important Bridges BGL           | 100    | biconnected components                                                                                            |
| 4                     | Shortest Paths                  | 100    | Dijkstra                                                                                                          |
| PotW 5 (2018)         | Hiking Maps                     | 100    | inclusion test & sliding window                                                                                   |
| PotW 5 (2019)         | Motorcycles                     | 100    | sorting by increasing slope and then linear pass to test for intersections                                        |
| 5                     | Boats                           | 100    | greedy, version of earliest deadline first                                                                        |
| 5                     | Attack of the Clones            | 100    | greedy, earliest deadline first in a circle                                                                       |
| 5                     | Ligth at the Museum             | 100    | split & list, brute force all switch configurations                                                               |
| 5                     | Punch                           | 100    | dynamic programming, 2D table for beverages x liters                                                              |
| 5                     | High School Teams               | 100    | split & list, brute force all combinations with at most k refs, for those brute force all team combinations       |
| 5 (2019)              | Octopussy                       | 100    | greedy with recursive dependency resolution                                                                       |
| 5 (2019)              | Planks                          | 100    | Split & List with to bits per plank                                                                               |
| PotW 6 (2018 & 2019)  | Planet Express                  | 100    | strong components & Dijkstra                                                                                      |
| 6                     | Coin Tossing                    | 100    | max flow, making sure claimed scores and flow match number of games                                               |
| 6                     | Shopping Trip                   | 100    | max flow, adding edges between junctions in both directions                                                       |
| 6                     | Kingdom Defence                 | 100    | max flow with edge demand (min capacity)                                                                          |
| 6                     | Tetris                          | 100    | max flow with splitting nodes into in- and out-nodes (vertex capacity)                                            |
| 6 (2019)              | London                          | 100    | max flow, edges between front/back letter combinations                                                            |
| PotW 7 (2018)         | Octopussy                       | 100    | greedy with recursive dependency resolution                                                                       |
| PotW 7 (2019)         | Attack of the Clones            | 100    | greedy, earliest deadline first in a circle                                                                       |
| 7                     | What is the Maximum             | 100    | quadratic programming                                                                                             |
| 7                     | Diet                            | 100    | linear programming                                                                                                |
| 7                     | Portfolios                      | 100    | quadratic programming, minimize over variance matrix                                                              |
| 7                     | Inball                          | 100    | linear programming, find closest point to every halfspace border and check                                        |
| 7                     | Radiation                       | 100    | LP, for every d try to find coefficiants for a 3D-polynomial of degree d that solves the constraints              |
| PotW 8 (2018)         | London                          | 100    | max flow, edges between front/back letter combinations                                                            |
| PotW 8 (2019)         | Cantonal Courier                | 100    | max flow                                                                                                          |
| 8                     | Graypes                         | 100    | Delaunay triangulation, taking shortest edge                                                                      |
| 8                     | Bistro                          | 100    | voronoi using Delaunay triangulation                                                                              |
| 8                     | H1N1                            | 100    | Delaunay/voronoi duality and precomputing largest escape path                                                     |
| 8                     | Germs                           | 100    | Delaunay for nearest neighbour graph                                                                              |
| PotW 9 (2018 & 2019)  | Suez                            | 100    | find constraints/objective and solve with LP                                                                      |
| 9                     | Satellites                      | 100    | max cardinality matching in bipartite graph & König algorithm                                                     |
| 9                     | Algocoön                        | 100    | max flow / min cut with multiple min cuts                                                                         |
| 9                     | Real Estate Market              | 100    | min cost matching                                                                                                 |
| 9                     | Canteen                         | 100    | min cost max flow, days as nodes and edges between days as fridge                                                 |
| 9                     | Marathon                        | 100    | multiple max flow min cost & binary search to find the optimal flow                                               |
| PotW 10 (2018 & 2019) | GoldenEye                       | 100    | voronoi (using Delaunay) & union find                                                                             |
| 10                    | New Tiles                       | ---    | Cancer to implement                                                                                               |
| 10                    | On Her Majesty's Secret Service | 100    | minimum bottleneck matching, minimizing longest edge in bipartite graph                                           |
| 10                    | Light the Stage                 | 100    | Delaunay for nearest neighbour & trying out all possible collisions                                               |
| 10                    | Evolution                       | 100    | binary search on each interval found by DFS                                                                       |
| 10                    | Return of the Jedi              | 100    | finding 2nd most optimal spanning tree using Prim & DFS                                                           |
| 10                    | Poker Chips                     | 100    | recursion with insane 5D memoization table                                                                        |
| 10 (2019)             | Defensive Line                  | 100    | sliding window & DP                                                                                               |
| 10 (2019)             | Moving Books                    | 100    | greedy, in every round everyone picks the heaviest box he can                                                     |
| PotW 11 (2018 & 2019) | India                           | 100    | min cost max flow, binary search on number of suitcases to find maximum that still respects budget (see Marathon) |
| 11                    | The Empire Strikes Back         | 100    | Delaunay for finding max radius per shot, then LP for solving for required energy                                 |
| 11 (2018)                    | Planks                          | 100    | Split & List with to bits per plank                                                                               |
| 11                    | Carsharing                      | 100    | min cost max flow with a space-time graph and clever edge weights                                                 |
| 11                    | San Francisco                   | 100    | binary search over recursive function to find smallest k to achieve x points                                      |
| 11 (2019)             | DHL                             | 100    | DP making use of the nature of the cost function                                                                  |
| 11 (2019)             | Evolution                       | 100    | binary search on each interval found by DFS                                                                       |
| 11 (2019)             | Surveillance Photographs        | 100    | max flow on graph with two layers                                                                                 |
| PotW 12 (2018)        | New York                        | 100    | DFS over all trees, for every node discovered update node m hops above                                            |
| PotW 12 (2019)        | San Francisco                   | 100    | binary search over recursive function to find smallest k to achieve x points                                      |
| 12                    | Ligh Pattern                    | 100    | DP with linear table and two numbers per entry for normal and inverted lights                                     |
| 12                    | Casino Royale                   | 100    | min cost max flow, space-time graph (see Carsharing)                                                              |
| 12                    | Radiation                       | 100    | LP, for every d try to find coefficiants for a 3D-polynomial of degree d that solves the constraints              |
| 12                    | Hong Kong                       | 100    | Delaunay/voronoi duality and precomputing max clearance for every triangle (see H1N1)                             |
| 12 (2019)             | Clues                           | 100    | computing graph 2-coloring and connected components simultaneously using Delaunay triangulation                   |
| 12 (2019)             | Magician and the Coin           | 100    | recursion & memoization                                                                                           |
| 12 (2019)             | Asterix and the tour of Gaul    | 100    | min cost max flow                                                                                                 |
| 12 (2019)             | Asterix and the Roman Lines     | 100    | LP                                                                                                                |
| PotW 13 (2018)        | World Cup (mock exam)           | 100    | Delaunay to find relevant contour lines & LP to maximize profit under constraints                                 |
| PotW 13 (2019)        | Revenge of the Sith             | 100    | Delaunay and union find to find the largest suitable set of connected planets                                     |
| 13                    | Bob's Burden                    | 100    | Dijkstra for finding shortest path between 3 vertices & modelling node weight with in- and out-nodes              |
| 13                    | Corbusier                       | 100    | simple DP with 2D table                                                                                           |
| 13                    | Cantonal Courier                | 100    | max flow                                                                                                          |
| 13                    | Clues                           | 100    | computing graph 2-coloring and connected components simultaneously using Delaunay triangulation                   |
| 13                    | Moving Books                    | 100    | greedy, in every round everyone picks the heaviest box he can                                                     |
| 13 (2019)             | World Cup (mock exam)           | 100    | Delaunay to find relevant contour lines & LP to maximize profit under constraints                                 |
| 13 (2019)             | New York                        | 100    | DFS over all trees, for every node discovered update node m hops above                                            |
| 13 (2019)             | Phantom Menace                  | 100    | max flow for finding maximal vertex-disjoint paths                                                                |
| PotW 14 (2018)        | Fleetrace                       | 100    | minimum cost bipartite matching                                                                                   |
| PotW 14 (2019)        | Carsharing                      | 100    | min cost max flow with a space-time graph and clever edge weights                                                 |

    -- may OK-Jesus be with you!
