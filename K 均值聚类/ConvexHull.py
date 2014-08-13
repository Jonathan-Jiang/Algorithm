# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from random import randint as rand

# ========================================
# GrahamScan algorithm
def Top(stack):
    return stack[0]

def NextToTop(stack):
    return stack[1]

def Push(p, stack):
    stack.insert(0, p)

def Pop(stack):
    return stack.pop(0)

def vec2DCrossProduct((x1, y1), (x2, y2), (x0, y0)):
    # (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)
    # 是 p0p1 叉乘 p0p2
    # 如果这个值
    # > 0 p0p1 在 p0p2 的顺时针方向
    # < 0 p0p1 在 p0p2 的逆时针方向
    # = 0 共线
    return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)

def turnLeft((x1, y1), (x2, y2), (x0, y0)):
    return vec2DCrossProduct((x1, y1), (x2, y2), (x0, y0))

def GrahamScan(Q):
    if len(Q) == 1 or len(Q) == 2:
        return Q
    # let p0 be the point with the minimum y-coordinate
    Q = sorted(Q, key = lambda (x, y): y)
    (x0, y0) = Q.pop(0)
    # let <p1, ..., pm> be the remaining points in Q, sorted by the angle in counterclockwise order around p0
    Q.sort(lambda (x1, y1), (x2, y2): turnLeft((x2, y2), (x1, y1), (x0, y0)))

    # Top(S) = 0
    stack = []

    # Push(p0, S); Push(p1, S); Push(p2, S)
    Push((x0, y0), stack)
    Push(Q[0], stack)
    Push(Q[1], stack)
    Pop(Q)
    Pop(Q)

    for (x, y) in Q:
        # while the angle formed by points NextToTop(S), Top(S) and pi makes a non-left turn do
            # Pop(stack)
        while turnLeft((x, y), Top(stack), NextToTop(stack)) >= 0:
            Pop(stack)
        Push((x, y), stack)
    return stack
# ========================================

def drawConvexHull(points, screen):
    frame_color = pygame.Color(200, 200, 200)
    for i, point in enumerate(points):
        pygame.draw.line(screen, frame_color, points[i], points[(i + 1) % len(points)], 3)
