import heapq
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d
#多项式插值通常在数据点较少且分布均匀时效果较好。当数据点较多或者不希望插值多项式在整个区间内振荡时，可以考虑使用分段插值方法，如样条插值或B样条插值，因为它们可提供更好的局部控制和减少振荡。
def smooth_path(path, factor=10):
    if path is None or len(path) < 3:
        return path  # 路径太短，不需要平滑处理

    # 分离路径里的 x 和 y 坐标
    x_coords, y_coords = zip(*path)

    # 创建等差数列用于曲线插值
    t = range(len(path))
    t_smooth = np.linspace(min(t), max(t), num=len(t) * factor)

    # 使用三次样条插值创建平滑的路径
    interp_x = interp1d(t, x_coords, kind='cubic')
    interp_y = interp1d(t, y_coords, kind='cubic')

    # 生成平滑路径的新坐标点
    x_smooth = interp_x(t_smooth)
    y_smooth = interp_y(t_smooth)

    return list(zip(x_smooth, y_smooth))


def visualize_maze(maze, path=None, start=None, end=None):
    fig, ax = plt.subplots()
    ax.imshow(maze, cmap=plt.cm.Dark2)

    if path:
        smoothed_path = smooth_path(path)
        x_coords, y_coords = zip(*smoothed_path)
        ax.plot(y_coords, x_coords, color='lightgreen', linewidth=3)  # 绘制平滑后的路径

    if start:
        ax.text(start[1], start[0], 'S', ha='center', va='center', color='yellow')

    if end:
        ax.text(end[1], end[0], 'G', ha='center', va='center', color='red')

    # 绘制网格线
    ax.grid(which='major', axis='both', linestyle='-', color='k', linewidth=2)
    ax.set_xticks(np.arange(-.5, len(maze[0]), 1))
    ax.set_yticks(np.arange(-.5, len(maze), 1))
    ax.xaxis.set_ticklabels([])
    ax.yaxis.set_ticklabels([])

    plt.show()

class Node:
    """用于 A* 路径寻找的节点类"""

    def __init__(self, parent=None, position=None):
        self.parent = parent  # 父节点
        self.position = position  # 节点在网格中的位置
        self.g = 0  # 从起点到当前节点的移动成本
        self.h = 0  # 启发式预估从当前节点到目标节点的剩余成本
        self.f = 0  # 当前节点的总成本：f = g + h

    def __eq__(self, other):
        return self.position == other.position
    
    def __lt__(self, other):
        return self.f < other.f


def astar(maze, start, end):
    """在给定迷宫中返回从起点到终点的路径列表"""
    
    # 创建初始和结束节点，并初始化 g，h 和 f 的值
    start_node = Node(None, tuple(start))
    end_node = Node(None, tuple(end))
    start_node.g = start_node.h = start_node.f = 0
    end_node.g = end_node.h = end_node.f = 0
    
    # 初始化开放列表和封闭列表
    open_list = []
    closed_list = set()
    
    # 将起点加入开放列表
    heapq.heappush(open_list, start_node)
    
    # 添加一个停止条件
    outer_iterations = 0
    max_iterations = (len(maze) // 2) ** 10

    # 循环直到找到终点
    while len(open_list) > 0:
        outer_iterations += 1
        
        if outer_iterations > max_iterations:
            # 如果达到这个点，则按当前路径返回
            # 它可能不包含目的地
            return None

        # 获取当前节点
        current_node = heapq.heappop(open_list)
        

        # 找到目标
        if current_node == end_node:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            # 返回反转后的路径，因为我们需要从起点到终点
            return path[::-1]
        closed_list.add(current_node.position)
        # 生成孩子节点
        children = []
        for new_position in [(0, -1), (0, 1), (-1, 0), (1, 0)]: # 相邻的方格

            # 获取节点位置
            node_position = (current_node.position[0] + new_position[0], current_node.position[1] + new_position[1])

            # 确保位置在迷宫范围内
            if node_position[0] > (len(maze) - 1) or node_position[0] < 0 or node_position[1] > (len(maze[len(maze)-1]) -1) or node_position[1] < 0:
                continue

            # 确保可以行走的地形
            if maze[node_position[0]][node_position[1]] != 0:
                continue

            # 创建新的节点
            new_node = Node(current_node, node_position)

            # 添加到列表
            children.append(new_node)

        # 遍历孩子节点
        for child in children:

            # 如果孩子节点在封闭列表中
            if child.position in closed_list:
                continue

            # 计算 f, g, 和 h 值
            child.g = current_node.g + 1
            child.h = abs(child.position[0] - end_node.position[0]) + abs(child.position[1] - end_node.position[1])
            child.f = child.g + child.h

            # 如果孩子已经在开放列表中且当前的 g 成本更高
            for open_node in open_list:
                if child == open_node and child.g > open_node.g:
                    continue

            # 将孩子添加到开放列表中
            heapq.heappush(open_list, child)

    return None

# 一个带有障碍物的样例迷宫
maze = [[0, 0, 0, 0, 1],
        [0, 1, 1, 0, 1],
        [0, 0, 0, 1, 0],
        [1, 1, 0, 0, 0],
        [0, 0, 0, 0, 0]]

start = [0, 0]  # 起始位置
end = [4, 4]    # 结束（目标）位置

path = astar(maze, start, end)
print(path)  # 如存在，输出从起点到终点的路径

# 可视化迷宫以及路径
visualize_maze(maze, path, start, end)