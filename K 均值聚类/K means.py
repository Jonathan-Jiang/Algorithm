# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from random import randint as rand
from math import pow
from copy import deepcopy

from ConvexHull import GrahamScan, drawConvexHull


# ========================================
# K-means algorithm
# 直接用平方表示距离，不开根号了
def distance((x1, y1), (x2, y2)):
    return pow(x2 - x1, 2) + pow(y2 - y1, 2)

def K_means(Q):
    global clusters, seeds
    seeds = [(rand(50, 450), rand(50, 450)) for _ in xrange(k)]
    while True:
        now_seeds = [None for _ in xrange(k)]
        clusters = {}
        for i in xrange(k):
            clusters.setdefault(i, [])

        for q in Q:
            dist = []
            for seed in seeds:
                if seed == None:
                    dist.append(5000)
                else:
                    dist.append(distance(q, seed))
            seed_index = dist.index(min(dist))
            clusters[seed_index].append(q)

        for i in xrange(k):
            if len(clusters[i]) == 0:
                continue
            new_seed = reduce(lambda (x1, y1), (x2, y2): (x1 + x2, y1 + y2) , clusters[i])
            now_seeds[i] = (new_seed[0] / len(clusters[i]), new_seed[1] / len(clusters[i]))

        deviation = []
        for i in xrange(k):
            if now_seeds[i] == None or seeds[i] == None:
                continue
            # 直接用平方表示距离，不开根号了
            deviation.append(pow(seeds[i][0] - now_seeds[i][0], 2) + pow(seeds[i][1] - now_seeds[i][1], 2))

        seeds = deepcopy(now_seeds)

        if len(deviation) == 0 or max(deviation) <= 0.00001:
            index = 0
            for seed in seeds:
                if seed == None:
                    seeds.pop(index)
                index += 1
            break

# ========================================

def drawSeeds():
    black_color = pygame.Color(0, 255, 0)
    for point in seeds:
        pygame.draw.circle(screen, black_color, point, 10)

def drawCluster():
    deep = 0
    for points in clusters.values():
        if len(points) == 0:
            continue
        draw_color = pygame.Color(deep, 0, 0)
        for point in points:
            if point == None:
                continue
            pygame.draw.circle(screen, draw_color, point, 10)
        convex_hull_points = GrahamScan(points)
        drawConvexHull(convex_hull_points, screen)
        deep += 20

def generateQ():
    global Q
    Q = [(rand(0, 500), rand(0, 500)) for _ in xrange(10)]
    K_means(Q)

Q, seeds, clusters, k = None, None, None, 1
generateQ()

pygame.init()
fpsClock = pygame.time.Clock()

screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption('K-means')

running = True

back_color = pygame.Color(100, 100, 255)

while running:
    screen.fill(back_color)

    drawCluster()
    drawSeeds()

    pygame.display.flip()
    pygame.display.update()
    fpsClock.tick(30)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit(0)

        if event.type == pygame.KEYDOWN:
            if event.key == K_SPACE:
                k += 1
                K_means(Q)
                for q in Q:
                    if q in seeds:
                        print 'fuck'
                print '============='
                print 'k', k
                print 'Q', Q
                print 'seeds', seeds
                print 'clusters', clusters
                print '============='
            if event.key == K_r:
                k = 1
                generateQ()
