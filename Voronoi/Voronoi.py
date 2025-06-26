import tkinter as tk
from tkinter import filedialog
import numpy as np
from scipy.spatial import Voronoi
import os

WIDTH, HEIGHT = 600, 600

class Voronoi:
    def __init__(self, root):
        self.root = root
        self.root.title("Voronoi Diagram")
        self.canvas = tk.Canvas(root, width=WIDTH, height=HEIGHT, bg="white")
        self.canvas.pack()

        # Buttons
        btn_frame = tk.Frame(root)
        btn_frame.pack()

        tk.Button(btn_frame, text="畫 Voronoi", command=self.draw_voronoi).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="清除", command=self.clear_canvas).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="讀入檔案", command=self.load_file).pack(side=tk.LEFT)
        tk.Button(btn_frame, text="輸出檔案", command=self.save_file).pack(side=tk.LEFT)

        self.canvas.bind("<Button-1>", self.on_click)
        self.points = []
        self.segments = []

    def on_click(self, event):
        x, y = event.x, event.y
        self.points.append((x, y))
        self.canvas.create_oval(x-3, y-3, x+3, y+3, fill="black")

    def clear_canvas(self):
        self.canvas.delete("all")
        self.points.clear()
        self.segments.clear()

    def draw_voronoi(self):
        if len(self.points) < 2:
            return

        points = np.array(self.points)
        vor = Voronoi(points)

        self.segments.clear()
        for vpair in vor.ridge_vertices:
            if -1 in vpair:
                continue  # skip infinite
            p1 = vor.vertices[vpair[0]]
            p2 = vor.vertices[vpair[1]]
            x1, y1 = p1
            x2, y2 = p2
            self.canvas.create_line(x1, y1, x2, y2, fill="blue")
            self.segments.append(((x1, y1), (x2, y2)))

    def load_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("Text Files", "*.txt")])
        if not file_path:
            return
        self.clear_canvas()

        with open(file_path, 'r') as f:
            lines = f.readlines()

        reading = False
        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            if not reading:
                try:
                    n = int(line)
                    if n == 0:
                        break
                    reading = True
                except ValueError:
                    continue
                continue
            else:
                parts = line.split()
                if len(parts) != 2:
                    continue
                x, y = map(float, parts)
                self.points.append((x, y))
                self.canvas.create_oval(x-3, y-3, x+3, y+3, fill="black")

    def save_file(self):
        if not self.points:
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
            for x, y in self.points:
                f.write(f"({x:.1f}, {y:.1f})\n")
            f.write("\n# Edges (lexical order):\n")
            for (x1, y1), (x2, y2) in sorted_segments:
                f.write(f"({x1:.1f}, {y1:.1f}) -> ({x2:.1f}, {y2:.1f})\n")

if __name__ == "__main__":
    root = tk.Tk()
    app = Voronoi(root)
    root.mainloop()