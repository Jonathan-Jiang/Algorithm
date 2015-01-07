# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from random import randint as rand

# ========================================
# geohash algorithm
# 希尔伯特填充曲线
'''
hilbert_map = {
'a': {(0, 0): (0, 'd'), (0, 1): (1, 'a'), (1, 0): (3, 'b'), (1, 1): (2, 'a')},
'b': {(0, 0): (2, 'b'), (0, 1): (1, 'b'), (1, 0): (3, 'a'), (1, 1): (0, 'c')},
'c': {(0, 0): (2, 'c'), (0, 1): (3, 'd'), (1, 0): (1, 'c'), (1, 1): (0, 'b')},
'd': {(0, 0): (0, 'a'), (0, 1): (3, 'c'), (1, 0): (1, 'd'), (1, 1): (2, 'd')}}
'''

hilbert_map = {
'a': {(0, 0): ([0, 0], 'd'), (0, 1): ([0, 1], 'a'), (1, 0): ([1, 1], 'b'), (1, 1): ([1, 0], 'a')},
'b': {(0, 0): ([1, 0], 'b'), (0, 1): ([0, 1], 'b'), (1, 0): ([1, 1], 'a'), (1, 1): ([0, 0], 'c')},
'c': {(0, 0): ([1, 0], 'c'), (0, 1): ([1, 1], 'd'), (1, 0): ([0, 1], 'c'), (1, 1): ([0, 0], 'b')},
'd': {(0, 0): ([0, 0], 'a'), (0, 1): ([1, 1], 'c'), (1, 0): ([0, 1], 'd'), (1, 1): ([1, 0], 'd')}}

def Hilbert(x, y):
    current_square = 'a'
    # position = 0
    position = []
    for i in range(geohash_length - 1, -1, -1):
        # position <<= 2
        quad_x = 1 if x & (1 << i) else 0
        quad_y = 1 if y & (1 << i) else 0
        quad_position, current_square = hilbert_map[current_square][(quad_x, quad_y)]
        # position |= quad_position
        position.extend(quad_position)
    return position

# Peano 填充曲线
def Peano(x, y):
    position = []
    for i in range(geohash_length - 1, -1, -1):
        # position <<= 2
        quad_x = 1 if x & (1 << i) else 0
        quad_y = 1 if y & (1 << i) else 0
        position.append(quad_x)
        position.append(quad_y)
    return position

# 策略设计模式
class GeoHash():
    def __init__(self, strategy_func):
        self.strategy_func = strategy_func

    # 获取坐标 (x, y) 的块坐标 (square_x, square_y)
    def get_square_coordinate(self, x, y):
        return int((x + 180) / width_gap), int((y + 90) / height_gap)

    # 获取一个经纬度坐标 (x, y) 的 geohash 值
    # 先获取该经纬度坐标值的块坐标值
    # 然后调用 geohash 函数来计算
    # geohash 函数的参数是块坐标值
    def get_code_using_abstract_coordinate(self, x, y):
        rx, ry = self.get_square_coordinate(x, y)
        return geohash(rx, ry, self.strategy_func);

    # 计算一个块坐标的 geohash 值
    # 使用块坐标
    def get_code_using_square_coordinate(self, (rx, ry)):
        return geohash(rx, ry, self.strategy_func);

    # 获取一个经纬度坐标 (x, y) 的邻近点
    # 注意传入的参数是一个经纬度值，可以是浮点数
    # geohash 函数传入的是一个块坐标值
    def get_adjacent_points(self, x, y):
        # 获取当前经纬度坐标 (x, y) 的块坐标 (rx, ry)
        rx, ry = self.get_square_coordinate(x, y)
        # 获取以当前块坐标为中心的周边 8 个坐标，和当前块坐标本身共 9 个坐标
        # 去除掉越界的情况
        square_coordinates = [(rx + i, ry + j) for i in range(-1, 2) for j in range(-1, 2) if rx + i >= 0 and rx + i < (1 << geohash_length) and ry + j >= 0 and ry + j < (1 << geohash_length)]
        # 获取这 9 个块坐标的 geohash 值
        hash_codes = map(self.get_code_using_square_coordinate, square_coordinates)

        adjacent_points = []
        for key in cache.keys():
            # 只要以当前坐标为中心的 9 宫格内所有坐标有任意一个命中
            if key in hash_codes:
                # 利用距离筛选来处理边界跳跃情况
                for point in cache[key]:
                    if (point[0] - x) * (point[0] - x) + (point[1] - y) * (point[1] - y) <= width_gap * width_gap + height_gap * height_gap:
                        adjacent_points.append(point)

        return adjacent_points

# geohash 编码的长度
# 越长精度越高
geohash_length = 3

base32_table = [
'0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'b', 'c', 'd', 'e', 'f', 'g',
'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r',
's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

# 经度取值范围
longitude = (-180, 180)
# 纬度取值范围
latitude = (-90, 90)

# 传入的参数是一个位置的块坐标值
# 返回它的 geohash 值
# 采用策略设计模式，第三个参数是采用的填充曲线类型
# 可以采用 Hilbert 或者 Peano 曲线
def geohash(x, y, strategy_func):
    encoded_sequence = strategy_func(x, y)
    sig = len(encoded_sequence) % 5
    for _ in range(5 - sig):
        encoded_sequence.insert(0, 0)
    hash_code = ''
    for i in range(len(encoded_sequence) / 5):
        hash_code += base32_table[int(''.join(map(str, encoded_sequence[i * 5 : i * 5 + 5])), 2)]
    return hash_code
# ========================================

def drawFrame():
    frame_color = pygame.Color(200, 200, 200)
    for i in range(1 << geohash_length):
        xstart = int(width_gap * i)
        ystart = int(height_gap * i)
        pygame.draw.line(screen, frame_color, (xstart, 0), (xstart, 180), 1)
        pygame.draw.line(screen, frame_color, (0, ystart), (360, ystart), 1)

def drawAllPoints():
    white_color = pygame.Color(255, 255, 255)
    for point in all_points:
        pygame.draw.circle(screen, white_color, point, 3)

    red_color = pygame.Color(255, 0, 0)
    for point in adjacent_points:
        pygame.draw.circle(screen, red_color, point, 3)
    
    black_color = pygame.Color(0, 0, 0)
    pygame.draw.circle(screen, black_color, current_point, 3)

def get_adjacent_points():
    global adjacent_points, current_index, current_point
    current_point = all_points[current_index]
    # 记住要 -180 和 -90
    adjacent_points = gh.get_adjacent_points(current_point[0] - 180, current_point[1] - 90)

    # 还原，要 +180 和 +90
    # 要注意画图需要的坐标和算法计算的坐标之间的差异
    adjacent_points = [(point[0] + 180, point[1] + 90) for point in adjacent_points]
    current_index = (current_index + 1) % 40

def generateAllPoints():
    global all_points, current_point, cache
    all_points = [(rand(0, 360), rand(0, 180)) for _ in xrange(40)]
    cache = {}
    for point in all_points:
        # 记住要 -180 和 -90
        # 因为屏幕的坐标范围是 (0, 360)，(0, 180)
        # 而经度的范围是 (-180, 180)，纬度范围是 (-90, 90)
        hash_code = gh.get_code_using_abstract_coordinate(point[0] - 180, point[1] - 90)
        if not hash_code in cache:
            cache[hash_code] = [(point[0] - 180, point[1] - 90)]
        else:
            cache[hash_code].append((point[0] - 180, point[1] - 90))
    get_adjacent_points()

all_points, adjacent_points = [], []
current_point = (0, 0)
current_index = 0
# 缓存，存放 geohash code 和经纬度之间的映射
cache = {}
# 初始化一个以 Peano 曲线为填充曲线的 GeoHash 算法
gh = GeoHash(Peano)

# 每条经度线之间的距离
width_gap = 360.0 / (1 << geohash_length)
# 每条纬度线之间的距离
height_gap = 180.0 / (1 << geohash_length)

generateAllPoints()

pygame.init()
fpsClock = pygame.time.Clock()

screen = pygame.display.set_mode((360, 180))
pygame.display.set_caption('GeoHash')

running = True

back_color = pygame.Color(100, 100, 255)

while running:
    screen.fill(back_color)

    drawFrame()
    drawAllPoints()

    pygame.display.flip()
    pygame.display.update()
    fpsClock.tick(30)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit(0)

        if event.type == pygame.KEYDOWN:
            if event.key == K_SPACE:
                generateAllPoints()
            if event.key == K_n:
                get_adjacent_points()
