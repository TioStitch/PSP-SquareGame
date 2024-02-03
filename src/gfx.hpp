#include <cstdint>

namespace GFX {
    void init();
    void clear(uint32_t color);
    void swapBuffers();
    void drawRect(int x, int y, int w, int h, uint32_t color);
    void drawCircle(int x, int y, int radius, uint32_t color);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
    void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
}