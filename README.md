# My solutions to the problems of the Algorithms Lab of ETH Zurich in Fall 2018

| Week      | Problem                         | Points | Solution                                                                                                          |
| --------- | ------------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------- |
| C++ intro | Basic data types                | 100    | types                                                                                                             |
| C++ intro | BFS                             | 100    | standard BFS                                                                                                      |
| C++ intro | Build the sum                   | 100    | naive                                                                                                             |
| C++ intro | DFS                             | 100    | standard DFS                                                                                                      |
| C++ intro | Hello World                     | 100    | naive                                                                                                             |
| C++ intro | Maps                            | 100    | maps                                                                                                              |
| C++ intro | Sets                            | 100    | sets                                                                                                              |
| C++ intro | Sort                            | 100    | std::sort()                                                                                                       |
| C++ intro | Strings                         | 100    | strings                                                                                                           |
| C++ intro | Vectors                         | 100    | vectors                                                                                                           |
| 1         | Build the sum                   | 100    | naive linear                                                                                                      |
| 1         | Dominoes                        | 100    | naive linear                                                                                                      |
| 1         | Even Pairs                      | 100    | Partial sums, binomial coefficient                                                                                |
| 1         | Even Matrices                   | 100    | dimension reduction & partial sums                                                                                |
| PotW 2    | Deck of Cards                   | 100    | sliding window                                                                                                    |
| 2         | Beach Bars                      | 100    | partial sums, sliding window                                                                                      |
| 2         | Burning Coins                   | 100    | dynamic programming (memoization), 2 tables                                                                       |
| 2         | Search Snippets                 | 100    | ordering words by occurences, sliding window                                                                      |
| 2         | The Great Game                  | 100    | backward recursion & memoization, 2 tables                                                                        |
| PotW 3    | Magician and the Coin           | 100    | backward recursion & memoization                                                                                  |
| 3         | Hit                             | 100    | intersection                                                                                                      |
| 3         | First hit                       | 100    | intersection, shuffle input and clip ray to avoid costly intersections                                            |
| 3         | Antenna                         | 100    | Min_circle                                                                                                        |
| 3         | Almost antenna                  | 100    | Min_circle, support points                                                                                        |
| PotW 4    | Defensive Line                  | 100    | sliding window & DP                                                                                               |
| 4         | Ant Challenge                   | 100    | Kruskal per species, then Dijkstra                                                                                |
| 4         | Buddy Selection                 | 100    | perfect matching                                                                                                  |
| 4         | Building a Graph                | 100    | Kurskal, Dijkstra                                                                                                 |
| 4         | Important Bridges BGL           | 100    | biconnected graph                                                                                                 |
| 4         | Shortest Paths                  | 100    | Dijkstra                                                                                                          |
| PotW 5    | Hiking Maps                     | 100    | inclusion test & sliding window                                                                                   |
| 5         | Boats                           | 100    | greedy, version of earliest finish time                                                                           |
| 5         | Attack of the Clones            | 100    | greedy, eraliest deadline first with circle                                                                       |
| 5         | Ligth at the Museum             | 100    | brute force all switch configurations using split & list                                                          |
| 5         | Punch                           | 100    | dynamic programming, 2D table for beverages * liters                                                              |
| 5         | High School Teams               | 100    | split & list, brute force all combinations with at most k refs, for those brute force all team combinations       |
| PotW 6    | Planet Express                  | 100    | strong components & Dijkstra                                                                                      |
| 6         | Coin Tossing                    | 100    | max flow, making sure claimed scores and flow match number of games                                               |
| 6         | Shopping Trip                   | 100    | max flow, adding edges between junctions in both directions                                                       |
| 6         | Kingdom Defence                 | 100    | max flow with edge demand (min capacity)                                                                          |
| 6         | Tetris                          | 100    | max flow with splitting nodes into in- and out-nodes (vertex capacity)                                            |
| PotW 7    | Octopussy                       | 100    | greedy with recursive dependency resolution                                                                       |
| 7         | What is the Maximum             | 100    | quadratic programming                                                                                             |
| 7         | Diet                            | 100    | linear programming                                                                                                |
| 7         | Portfolios                      | 100    | quadratic programming, minimize over variance matrix                                                              |
| 7         | Inball                          | 100    | linear programming, find closest point to every halfspace border and check                                        |
| PotW 8    | London                          | 100    | max flow, edges between front/back letter combinations                                                            |
| 8         | Graypes                         | 100    | delauny triangulation, taking shortest edge                                                                       |
| 8         | Bistro                          | 100    | voronoi using delauny triangulation                                                                               |
| 8         | H1N1                            | 100    | delauny/voronoi duality and precomputing largest escape path                                                      |
| 8         | Germs                           | 100    | delauny for nearest neighbour graph                                                                               |
| PotW 9    | Suez                            | 100    | find constraints/objective and solve with LP                                                                      |
| 9         | Satellites                      | 100    | max cardinality matching in bipartite graph & König algorithm                                                     |
| 9         | Algocoön                        | 100    | max flow / min cut with multiple min cuts                                                                         |
| 9         | Real Estate Market              | 100    | min cost matching                                                                                                 |
| 9         | Canteen                         | 100    | min cost max flow, days as nodes and edges between days as fridge                                                 |
| 9         | Marathon                        | 100    | multiple max flow min cost & binary search to find the optimal flow                                               |
| PotW 10   | GoldenEye                       | 100    | voronoi (using delauny) & union find                                                                              |
| 10        | New Tiles                       | ---    |                                                                                                                   |
| 10        | On Her Majesty's Secret Service | 100    | minimum bottleneck matching, minimizing longest edge in bipartite graph                                           |
| 10        | Light the Stage                 | 100    | delauny for nearest neighbour & trying out all possible collisions                                                |
| 10        | Evolution                       | 100    | binary search on each interval found by DFS                                                                       |
| 10        | Return of the Jedi              | 100    | finding 2nd most optimal spanning tree using Prim & DFS                                                           |
| 10        | Poker Chips                     | 100    | recursion with insane 5D memoization table                                                                        |
| PotW 11   | India                           | 100    | min cost max flow, binary search on number of suitcases to find maximum that still respects budget (see Marathon) |
| 11        | The Empire Strikes Back         | ---    |                                                                                                                   |
| 11        | Planks                          | ---    |                                                                                                                   |
| 11        | Carsharing                      | ---    |                                                                                                                   |
| 11        | San Francisco                   | ---    |                                                                                                                   |
| PotW 12   | New York                        | 100    | DFS over all trees, for every node discovered update node m hops above                                            |
| 12        | Ligh Pattern                    | ---    |                                                                                                                   |
| 12        | Casino Royale                   | ---    |                                                                                                                   |
| 12        | Radiation                       | ---    |                                                                                                                   |
| 12        | Hong Kong                       | 100    | delauny/voronoi duality and precomputing max clearance for every triangle (see H1N1)                              |
| PotW 13   | World Cup (mock exam)           | 100    | delauny to find relevant contour lines & LP to maximize profit under constraints                                  |
| 13        | Bob's Burden                    | 100    | Dijkstra for finding shortest path between 3 vertices & modelling node weight with in- and out-nodes              |
| 13        | Corbusier                       | 100    | simple DP with 2D table                                                                                           |
| 13        | Cantonal Courier                | 100    | max flow                                                                                                          |
| 13        | Clues                           | 100    | computing graph 2-coloring and connected components simultaneously using delauny triangulation                    |
| 13        | Moving Books                    | 100    | greedy, in every round everyone picks the heaviest box he can                                                     |
| PotW 14   | Fleetrace                       | ---    |                                                                                                                   |