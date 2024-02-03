#include "gfx.hpp"
#include <pspge.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <psputils.h>
#include <stdint.h>
#include <cstdint>
#include <algorithm>
#include <pspge.h>

uint32_t* draw_buffer;
uint32_t* disp_buffer;

namespace GFX {

    void init() {
        draw_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
        disp_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr() + (272 * 512 * 4));

        sceDisplaySetMode(0, 480, 272);
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
    }

    void clear(uint32_t color) {
        for (int i = 0; i < 512 * 272; i++) {
            draw_buffer[i] = color;
        }
    }

    void swapBuffers() {
        uint32_t* temp = disp_buffer;
        disp_buffer = draw_buffer;
        draw_buffer = temp;

        sceKernelDcacheWritebackInvalidateAll();
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);
    }

    void drawRect(int x, int y, int w, int h, uint32_t color) {
        // Limitar valores de x e y para evitar desenho fora da tela
        x = std::min(x, 480);
        y = std::min(y, 272);

        // Ajustar largura e altura para evitar desenho fora da tela
        w = std::min(w, 480 - x);
        h = std::min(h, 272 - y);

        int off = x + (y * 512);

        // Desenhar o retângulo apenas se tiver largura e altura positivas
        if (w > 0 && h > 0) {
            for (int y1 = 0; y1 < h; y1++) {
                for (int x1 = 0; x1 < w; x1++) {
                    draw_buffer[x1 + off + y1 * 512] = color;
                }
            }
        }
    }

        void drawCircle(int centerX, int centerY, int radius, uint32_t color) {
         for (int y = centerY - radius; y <= centerY + radius; y++) {
                for (int x = centerX - radius; x <= centerX + radius; x++) {
                    if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) <= radius * radius) {
                      // O ponto (x, y) está dentro do círculo, então atribua a cor
                     if (x >= 0 && x < 480 && y >= 0 && y < 272) {
                           draw_buffer[x + y * 512] = color;
                        }
                    }
                }
           }
        }
    
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color) {
        // Ordenar os vértices verticalmente para facilitar o desenho
            if (y1 > y2) std::swap(x1, x2), std::swap(y1, y2);
            if (y1 > y3) std::swap(x1, x3), std::swap(y1, y3);
            if (y2 > y3) std::swap(x2, x3), std::swap(y2, y3);
    
            // Desenhar as três linhas do triângulo
            drawLine(x1, y1, x2, y2, color);
            drawLine(x2, y2, x3, y3, color);
            drawLine(x3, y3, x1, y1, color);
    }

    void drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

    

        while (true) {
            draw_buffer[x1 + y1 * 512] = color;

            if (x1 == x2 && y1 == y2) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
}