import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
import numpy as np
import math
import os

WIDTH, HEIGHT = 1000, 1000

COLORS = [
    "red", "green", "blue", "orange", "cyan",
    "brown", "pink", "lime", "magenta", "purple",
]

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return isinstance(other, Point) and self.x == other.x and self.y == other.y

    def __lt__(self, other):
        return (self.x, self.y) < (other.x, other.y)


class Edge:
    def __init__(self, start, end=None, direction=None, base_points=None):
        self.start = start                      # 起始點 (x, y)
        self.end = end                          # 終點，若為 None 代表是射線
        self.direction = direction              # 單位方向向量，射線用
        self.base_points = base_points          # 兩個產生該中垂線的點


    def length(self):
        if self.end is None:
            return float('inf')                 # 射線無限長
        x1, y1 = self.start
        x2, y2 = self.end
        return math.hypot(x2 - x1, y2 - y1)


    def slope(self):
        dx, dy = None, None
        if self.end:
            dx = self.end[0] - self.start[0]
            dy = self.end[1] - self.start[1]
        elif self.direction:
            dx, dy = self.direction
        else:
            return None

        if dx == 0:
            return float('inf')                 # 垂直線
        return dy / dx


    def get_line_equation(self):
        # 返回一般式: Ax + By + C = 0 的係數 A, B, C
        x1, y1 = self.start
        if self.end:
            x2, y2 = self.end
        elif self.direction:
            x2 = x1 + self.direction[0]
            y2 = y1 + self.direction[1]
        else:
            raise ValueError("無法取得方向或終點")

        A = y1 - y2
        B = x2 - x1
        C = x1 * y2 - x2 * y1
        return A, B, C


    def intersection_with(self, other):
        # 計算與另一條 VoronoiEdge 的交點(若平行回傳 None)
        A1, B1, C1 = self.get_line_equation()
        A2, B2, C2 = other.get_line_equation()

        denom = A1 * B2 - A2 * B1
        if denom == 0:
            return None                         # 平行，無交點

        x = (B1 * C2 - B2 * C1) / denom
        y = (C1 * A2 - C2 * A1) / denom
        return (x, y)


class Voronoi:
    def __init__(self, root):
        screen_width = int((root.winfo_screenwidth() - WIDTH - 50) / 2)
        screen_height = int((root.winfo_screenheight() - HEIGHT - 50) / 2)

        self.root = root
        self.root.title("Voronoi Diagram")
        self.root.geometry(f"{WIDTH}x{HEIGHT}+{screen_width}+{screen_height}")
        self.root.minsize(WIDTH + 50, HEIGHT + 50)
        self.root.config(bg="white")
        self.root.attributes("-topmost", True)

        self.all_point_groups = []  # List[List[tuple]]，每組點是 list of (x,y)
        self.current_group_index = -1

        self.canvas = tk.Canvas(root, width=WIDTH, height=HEIGHT, bg="#000000")
        # self.canvas.configure(scrollregion=(-100, -100, WIDTH, HEIGHT))
        self.canvas.pack()

        btn_frame = tk.Frame(root)
        btn_frame.pack()

        tk.Button(btn_frame, text="上一筆", command=self.show_prev_group).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="畫 Voronoi", command=self.draw_voronoi).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="下一筆", command=self.show_next_group).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="清除", command=self.clear_canvas).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="讀入檔案", command=self.load_file).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="輸出檔案", command=self.save_file).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="當前", command=self.show_current_group).pack(side=tk.LEFT)

        self.canvas.bind("<Button-1>", self.on_click)
        self.points = []
        self.segments = []


    def on_click(self, event):
        p = Point(event.x, event.y)
        self.points.append(p)
        self.canvas.create_oval(p.x-3, p.y-3, p.x+3, p.y+3, fill="#ff0000", tags=("point",))
        self.canvas.create_text(p.x + 5, p.y - 5,
                                text = f"({p.x:.1f}, {p.y:.1f})",
                                anchor = "sw",
                                fill = "#00ff00",
                                font = ("Arial", 8),
                                tags = ("point_label",))

    def clear_canvas(self):
        self.canvas.delete("all")
        self.points.clear()
        self.segments.clear()


    def draw_voronoi(self):
        self.canvas.delete("edge")
        self.segments.clear()

        if not self.points:
            print("沒有點，無法建立 Voronoi Diagram")
            messagebox.showwarning("Warning", "沒有點，無法建立 Voronoi Diagram")
            return
        elif len(self.points) == 1:
            print("只有一點，無法建立 Voronoi Diagram")
            messagebox.showwarning("Warning", "只有一點，無法建立 Voronoi Diagram")
            return
        elif len(self.points) == 2:
            self.two_point()
        elif len(self.points) == 3:
            self.three_point()
        else:
            print("多於三點，尚未實作其 Voronoi Diagram")
            messagebox.showwarning("Warning", "多於三點，尚未實作其 Voronoi Diagram")
            return


    def two_point(self):
        # 畫兩點的垂直平分線
        A, B = self.points
        if A == B:
            print("兩點共點，無法建立正確 Voronoi Diagram")
            messagebox.showwarning("Warning", "兩點共點，無法建立正確 Voronoi Diagram")
            return

        x1, y1 = A.x, A.y
        x2, y2 = B.x, B.y
        mx, my = (x1 + x2) / 2, (y1 + y2) / 2
        dx, dy = x2 - x1, y2 - y1
        if dx == 0:
            x_start, x_end = 0, WIDTH
            y_start = y_end = my
        elif dy == 0:
            y_start, y_end = 0, HEIGHT
            x_start = x_end = mx
        else:
            slope = -dx / dy
            length = max(WIDTH*2, HEIGHT*2)
            x_start = mx - length
            y_start = my - slope * length
            x_end = mx + length
            y_end = my + slope * length

        self.canvas.create_line(x_start, y_start, x_end, y_end, fill="cyan", width=2, tags="edge")
        self.segments.append(((x_start, y_start), (x_end, y_end)))
        self.canvas.tag_raise("point_label")
        self.canvas.tag_raise("point")


    def three_point(self):
        A, B, C = self.points
        O = self.compute_circumcenter(A, B, C)
        if O is None:
            print("三點共線，僅有兩條 Voronoi Edge")
            points = sorted([A, B, C], key=lambda p: (p.x, p.y))

            for i in range(2):
                p1 = points[i]
                p2 = points[i + 1]
                mx = (p1.x + p2.x) / 2
                my = (p1.y + p2.y) / 2
                dx = p2.x - p1.x
                dy = p2.y - p1.y

                if dx == 0:
                    # 垂直線的中垂線是水平線
                    x_start, x_end = 0, WIDTH
                    y_start = y_end = my
                elif dy == 0:
                    # 水平線的中垂線是垂直線
                    y_start, y_end = 0, HEIGHT
                    x_start = x_end = mx
                else:
                    slope = -dx / dy  # 中垂線斜率是邊的負倒數
                    length = 1000
                    x_start = mx - length
                    y_start = my - slope * length
                    x_end = mx + length
                    y_end = my + slope * length

                self.canvas.create_line(x_start, y_start, x_end, y_end, fill=COLORS[(i + 3) % len(COLORS)], width=2, tags="edge")
                self.segments.append(((x_start, y_start), (x_end, y_end)))
                self.canvas.tag_raise("point_label")
                self.canvas.tag_raise("point")
            return

        # 重心
        Gx = (A.x + B.x + C.x) / 3
        Gy = (A.y + B.y + C.y) / 3
        # self.canvas.create_oval(Gx-4, Gy-4, Gx+4, Gy+4, fill="orange")

        # 逆時針排序
        points = [A, B, C]
        points.sort(key=lambda p: -math.atan2(p.y - Gy, p.x - Gx))
        # for i, p in enumerate(points):
            # print(math.atan2(p.y - Gy, p.x - Gx), f"Point {i}: ({p.x}, {p.y}), Angle: {math.degrees(math.atan2(p.y - Gy, p.x - Gx)):.2f}°")
            # print("vector:", p.x - Gx, p.y - Gy)

        for i in range(3):
            p1 = points[i]
            p2 = points[(i + 1) % 3]

            # 邊向量
            dx = p2.x - p1.x
            dy = p2.y - p1.y

            # 法向量（順時針90度旋轉）由於畫布跟數學座標系統有點不一樣，所以這樣是順時針旋轉
            nx = -dy
            ny = dx

            # 單位化
            norm = (nx**2 + ny**2) ** 0.5
            nx /= norm
            ny /= norm

            # 從外心 O 沿該方向延伸
            end = self.draw_ray(O, (nx, ny))

            # 繪製射線
            self.canvas.create_line(O[0], O[1], end[0], end[1], fill=COLORS[i % len(COLORS)], width=2, tags="edge")
            self.segments.append(((O[0], O[1]), end))

        
        self.canvas.tag_raise("point_label")
        self.canvas.tag_raise("point")
        self.canvas.create_oval(O[0]-4, O[1]-4, O[0]+4, O[1]+4, fill="white")
        # self.canvas.create_text(O[0]+5, O[1]-5, text="O", fill="white", font=("Arial", 10))


    def draw_ray(self, origin, direction, margin=10):
        ox, oy = origin
        dx, dy = direction

        # 如果方向為 0，直接返回原點（避免除以 0）
        if dx == 0 and dy == 0:
            return origin

        # 對四個邊界分別計算與射線的交點
        intersections = []

        def within_bounds(x, y):
            return -margin <= x <= WIDTH + margin and -margin <= y <= HEIGHT + margin

        # 上邊界 y = 0
        if dy != 0:
            t = (0 - oy) / dy
            if t > 0:
                x = ox + t * dx
                y = oy + t * dy
                if within_bounds(x, y):
                    intersections.append((x, y))

        # 下邊界 y = HEIGHT
        if dy != 0:
            t = (HEIGHT - oy) / dy
            if t > 0:
                x = ox + t * dx
                y = oy + t * dy
                if within_bounds(x, y):
                    intersections.append((x, y))

        # 左邊界 x = 0
        if dx != 0:
            t = (0 - ox) / dx
            if t > 0:
                x = ox + t * dx
                y = oy + t * dy
                if within_bounds(x, y):
                    intersections.append((x, y))

        # 右邊界 x = WIDTH
        if dx != 0:
            t = (WIDTH - ox) / dx
            if t > 0:
                x = ox + t * dx
                y = oy + t * dy
                if within_bounds(x, y):
                    intersections.append((x, y))

        if intersections:
            # 取距離 origin 最遠的交點（以防某些交點很近）
            intersections.sort(key=lambda p: (p[0] - ox) ** 2 + (p[1] - oy) ** 2, reverse=True)
            return intersections[0]
        else:
            # 若沒交點（在畫布外又無交點），直接沿著方向延伸很遠
            return (ox + dx * 10000, oy + dy * 10000)


    def compute_circumcenter(self, A, B, C):
        # 回傳三角形 ABC 的外心座標 (x, y)
        Ax, Ay = A.x, A.y
        Bx, By = B.x, B.y
        Cx, Cy = C.x, C.y

        D = 2 * (Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By))
        if D == 0:
            return None  # 三點共線

        Ux = ((Ax**2 + Ay**2)*(By - Cy) + (Bx**2 + By**2)*(Cy - Ay) + (Cx**2 + Cy**2)*(Ay - By)) / D
        Uy = ((Ax**2 + Ay**2)*(Cx - Bx) + (Bx**2 + By**2)*(Ax - Cx) + (Cx**2 + Cy**2)*(Bx - Ax)) / D
        return (Ux, Uy)


    def load_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("Text Files", "*.txt")])
        if not file_path:
            return

        self.all_point_groups.clear()
        self.current_group_index = -1
        self.clear_canvas()

        with open(file_path, 'r') as f:
            lines = [line.strip() for line in f if line.strip() and not line.strip().startswith('#')]

        i = 0
        while i < len(lines):
            try:
                n = int(lines[i])
                i += 1
            except ValueError:
                i += 1
                continue

            group = []
            for _ in range(n):
                if i >= len(lines):
                    break
                parts = lines[i].split()
                if len(parts) != 2:
                    i += 1
                    continue
                try:
                    x, y = map(float, parts)    # 把parts裡的元素轉成float，並拆解給x和y
                    group.append(Point(x, y))
                except ValueError:
                    pass
                i += 1

            if group:
                self.all_point_groups.append(group)

        if self.all_point_groups:
            self.current_group_index = 0
            self.show_current_group()


    def show_current_group(self):
        self.clear_canvas()
        if 0 <= self.current_group_index < len(self.all_point_groups):
            group = self.all_point_groups[self.current_group_index]
            self.points = group.copy()
            for p in group:
                self.canvas.create_oval(p.x - 3, p.y - 3, p.x + 3, p.y + 3, fill="red", tags=("point",))
                self.canvas.create_text(p.x + 5, p.y - 5,
                                        text = f"({p.x:.1f}, {p.y:.1f})",
                                        anchor = "sw",
                                        fill = "#00ff00",
                                        font = ("Arial", 8),
                                        tags = ("point_label",))


    def show_prev_group(self):
        if self.current_group_index > 0:
            self.current_group_index -= 1
            self.show_current_group()
        else:
            self.show_current_group()
            messagebox.showwarning("Warning", "已經是第一組點了")


    def show_next_group(self):
        if self.current_group_index < len(self.all_point_groups) - 1:
            self.current_group_index += 1
            self.show_current_group()
        else:
            self.show_current_group()
            messagebox.showwarning("Warning", "已經是最後一組點了")


    def save_file(self):
        if not self.all_point_groups:
            return

        file_path = filedialog.asksaveasfilename(defaultextension=".txt")
        if not file_path:
            return

        sorted_segments = sorted(
            [tuple(sorted(seg)) for seg in self.segments],
            key=lambda s: (s[0][0], s[0][1], s[1][0], s[1][1])
        )

        with open(file_path, 'w') as f:
            f.write("# Points:\n")
            for p in self.points:
                f.write(f"({p.x:.1f}, {p.y:.1f})\n")
            f.write("\n# Edges (lexical order):\n")
            for (x1, y1), (x2, y2) in sorted_segments:
                f.write(f"({x1:.1f}, {y1:.1f}) -> ({x2:.1f}, {y2:.1f})\n")

if __name__ == "__main__":
    root = tk.Tk()
    app = Voronoi(root)
    root.mainloop()