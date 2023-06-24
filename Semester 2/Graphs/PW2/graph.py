import copy


class DictGraph:
    def __init__(self, vertices, edges):
        self._vertices = vertices
        self._edges = edges
        self._dict_in = {}
        self._dict_out = {}
        self._dict_cost = {}
        for index in range(vertices):
            self._dict_in[index] = []
            self._dict_out[index] = []

    @property
    def vertices(self):
        return self._vertices

    @property
    def edges(self):
        return self._edges

    @property
    def dict_in(self):
        return self._dict_in

    @property
    def dict_out(self):
        return self._dict_out

    @property
    def dict_cost(self):
        return self._dict_cost

    def parse_vertices(self):
        vertices = list(self._dict_in.keys())
        for v in vertices:
            yield v

    def parse_inbound(self, x):
        for y in self._dict_in[x]:
            yield y

    def parse_outbound(self, x):
        for y in self._dict_out[x]:
            yield y

    def parse_cost(self):
        keys = list(self._dict_cost.keys())
        for key in keys:
            yield key

    def add_vertex(self, x):
        if x in self._dict_in.keys() and x in self._dict_out.keys():
            return False
        self._dict_in[x] = []
        self._dict_out[x] = []
        self._vertices += 1
        return True

    def remove_vertex(self, x):
        if x not in self._dict_in.keys() and x not in self._dict_out.keys():
            return False

        self._dict_in.pop(x)
        self._dict_out.pop(x)

        for key in self._dict_in.keys():
            if x in self._dict_in[key]:
                self._dict_in[key].remove(x)
            elif x in self._dict_out[key]:
                self._dict_out[key].remove(x)

        keys = list(self._dict_cost.keys())
        for key in keys:
            if key[0] == x or key[1] == x:
                self._dict_cost.pop(key)
                self._edges -= 1
        self._vertices -= 1
        return True

    def in_degree(self, x):
        if x not in self._dict_in.keys():
            return -1
        return len(self._dict_in[x])

    def out_degree(self, x):
        if x not in self._dict_out.keys():
            return -1
        return len(self._dict_out[x])

    def add_edge(self, x, y, cost):
        if x in self.dict_in[y]:
            return False
        elif y in self._dict_out[x]:
            return False
        elif (x, y) in self._dict_cost.keys():
            return False

        self._dict_in[y].append(x)
        self._dict_out[x].append(y)
        self._dict_cost[(x, y)] = cost
        self._edges += 1
        return True

    def remove_edge(self, x, y):
        if x not in self._dict_in.keys() or y not in self._dict_in.keys() or x not in self._dict_out.keys() or y not in self._dict_out.keys():
            return False
        if x not in self._dict_in[y]:
            return False
        elif y not in self._dict_out[x]:
            return False
        elif (x, y) not in self._dict_cost.keys():
            return False
        self._dict_in[y].remove(x)
        self._dict_out[x].remove(y)
        self._dict_cost.pop((x, y))
        self._edges -= 1
        return True

    def find_edge(self, x, y):
        if x in self._dict_in[y]:
            return self._dict_cost[(x, y)]
        elif y in self._dict_out[x]:
            return self._dict_cost[(x, y)]
        return False

    def change_cost(self, x, y, cost):
        if (x, y) not in self._dict_cost.keys():
            return False
        self.dict_cost[(x, y)] = cost
        return True

    def make_copy(self):
        return copy.deepcopy(self)

    def bfs(self, start, end):
        # maintain a queue of paths
        queue = [[start]]
        # push the first path into the queue
        while queue:
            # get the first path from the queue
            path = queue.pop(0)
            # get the last node from the path
            node = path[-1]
            # path found
            if node == end:
                return path
            # enumerate all adjacent nodes, construct a
            # new path and push it into the queue
            for adjacent in self.parse_outbound(node):
                new_path = list(path)
                new_path.append(adjacent)
                queue.append(new_path)

    # PW 3

    def minimum_distance(self, start, end, k):
        edgenr = self.edges
        vertexnr = self.vertices

        d = [[999999 for _ in range(edgenr + 1)] for _ in range(vertexnr)]
        for i in range(edgenr + 1):
            d[start][i] = 0

        for step in range(1, edgenr + 1):
            for i in range(1, vertexnr):
                d[i][step] = d[i][step - 1]
                for j in self.parse_inbound(i):
                    if d[j][step - 1] + self._dict_cost[(j, i)] < d[i][step]:
                        d[i][step] = d[j][step - 1] + self._dict_cost[(j, i)]

        for i in range(1, vertexnr):
            minimum = d[i][edgenr]
            for j in self.parse_inbound(i):
                if d[j][edgenr] + self._dict_cost[(j, i)] < minimum:
                    return 0

        return d[end][k]

    # LAB 4

    def minTreeKruskal(self, mintree):
        mincost = 0
        count = 0

        tree = [0] * self.vertices
        for x in self.dict_in:
            tree[x] = x
        orderedEdges = sorted(self.dict_cost.items(), key=lambda item: item[1])
        x = 0
        while x < self.edges and count < self.vertices:
            edge = orderedEdges[x]
            v = tree[edge[0][0]]
            w = tree[edge[0][1]]
            if v != w and (edge[0][1], edge[0][0]) not in mintree:
                mincost += edge[1]
                count += 1
                mintree.append(edge[0])
                for y in self.dict_in:
                    if tree[y] == w:
                        tree[y] = v
            x += 1
        return mincost

    # LAB 5

    def _get_vertex_root(self, vertex, vertex_root):
        # if vertex is the root
        if vertex_root[vertex] == vertex:
            return vertex

        return self._get_vertex_root(vertex_root[vertex], vertex_root)


def write_graph_to_file(graph, file):
    file = open(file, "w")
    first_line = str(graph.vertices) + ' ' + str(graph.edges) + '\n'
    file.write(first_line)
    if len(graph.dict_cost) == 0 and len(graph.dict_in) == 0:
        raise ValueError("There is nothing to write")
    for edge in graph.dict_cost.keys():
        new_line = "{} {} {}\n".format(edge[0], edge[1], graph.dict_cost[edge])
        file.write(new_line)
    for vertex in graph.dict_in.keys():
        if len(graph.dict_in[vertex]) == 0 and len(graph.dict_out[vertex]) == 0:
            new_line = "{}\n".format(vertex)
            file.write(new_line)
    file.close()


def read_graph_from_file(filename):
    file = open(filename, "r")
    line = file.readline()
    line = line.strip()
    vertices, edges = line.split(' ')
    graph = DictGraph(int(vertices), int(edges))
    line = file.readline().strip()
    while len(line) > 0:
        line = line.split(' ')
        if len(line) == 1:
            graph.dict_in[int(line[0])] = []
            graph.dict_out[int(line[0])] = []
        else:
            graph.dict_in[int(line[1])].append(int(line[0]))
            graph.dict_out[int(line[0])].append(int(line[1]))
            graph.dict_cost[(int(line[0]), int(line[1]))] = int(line[2])

        line = file.readline().strip()
    file.close()
    return graph
