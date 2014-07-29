#-*- coding: utf-8 -*-
from Queue import Queue, PriorityQueue
from math import fabs

width, height = 5, 6

class Node():
    def __init__(self, x, y):
        self.x = x
        self.y = y

def is_valid(x, y):
    if x < 0 or x >= width or y < 0 or y >= height:
        return False
    return True

def find_next_nodes(node):
    x, y = node.x, node.y
    next_position = ((x - 1, y - 2), (x + 1, y - 2), (x - 2, y - 1), (x + 2, y - 1), (x - 2, y + 1), (x + 2, y + 1), (x - 1, y + 2), (x + 1, y + 2))
    for ret_x, ret_y in next_position:
        if is_valid(ret_x, ret_y):
            yield Node(ret_x, ret_y)

def is_target(node):
    if node.x == width - 1 and node.y == height - 1:
        return True
    return False

def get_index(node):
    return node.x + node.y * width

def print_path(path):
    cur_x, cur_y = width - 1, height - 1
    while path[cur_x + cur_y * width] != -1:
        print cur_x, cur_y
        next_sum = path[cur_x + cur_y * width]
        cur_x, cur_y = next_sum % width, next_sum / width

# F = G + H
# manhattan distance
# 启发函数 H
def get_FCost(node):
    return fabs(node.x - width) + fabs(node.y - height)

def AStar():
    queue = PriorityQueue()
    cur_node = Node(0, 0)
    queue.put((get_FCost(cur_node), cur_node))
    visited = [get_index(cur_node)]
    path = [-1 for _ in xrange(width * height)]
    while not queue.empty():
        _, cur_node = queue.get()

        for node in find_next_nodes(cur_node):
            if get_index(node) in visited:
                continue

            path[get_index(node)] = get_index(cur_node)

            if is_target(node):
                print_path(path)
                return
            queue.put((get_FCost(node), node))
            visited.append(get_index(node))
    print 'not found'

def main():
    AStar()

if __name__ == '__main__':
    main()
