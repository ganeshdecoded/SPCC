import heapq

class Graph:
    def __init__(self):
        self.edges = {}
        self.heuristics = {}

    def add_edge(self, from_node, to_node, cost):
        self.edges.setdefault(from_node, []).append((to_node, cost))
        self.edges.setdefault(to_node, [])  # ensure every node is in the dictionary

    def set_heuristic(self, node, h_value):
        self.heuristics[node] = h_value

# Greedy Best-First Search
def best_first_search(graph, start, goal):
    visited = set()
    queue = [(graph.heuristics[start], start, [start])]

    while queue:
        _, current, path = heapq.heappop(queue)
        if current == goal:
            return path
        if current in visited:
            continue
        visited.add(current)
        for neighbor, cost in graph.edges.get(current, []):
            if neighbor not in visited:
                heapq.heappush(queue, (graph.heuristics[neighbor], neighbor, path + [neighbor]))
    return None

# A* Search Algorithm
def a_star_search(graph, start, goal):
    visited = set()
    queue = [(graph.heuristics[start], 0, start, [start])]

    while queue:
        est_total, cost_so_far, current, path = heapq.heappop(queue)
        if current == goal:
            return path
        if current in visited:
            continue
        visited.add(current)
        for neighbor, cost in graph.edges.get(current, []):
            if neighbor not in visited:
                new_cost = cost_so_far + cost
                est = new_cost + graph.heuristics[neighbor]
                heapq.heappush(queue, (est, new_cost, neighbor, path + [neighbor]))
    return None

# Example usage
g = Graph()
g.add_edge('A', 'B', 1)
g.add_edge('A', 'C', 3)
g.add_edge('B', 'D', 3)
g.add_edge('C', 'D', 1)
g.add_edge('D', 'E', 5)

g.set_heuristic('A', 6)
g.set_heuristic('B', 4)
g.set_heuristic('C', 2)
g.set_heuristic('D', 1)
g.set_heuristic('E', 0)

print("Best-First Search Path:", best_first_search(g, 'A', 'E'))
print("A* Search Path:", a_star_search(g, 'A', 'E'))
