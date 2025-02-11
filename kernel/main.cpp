/**
 * @file main.cpp
 *
 * カーネル本体のプログラムを書いたファイル．
 */

#include <cstdint>
#include <cstddef>
#include <cstdio>

// #@@range_begin(includes)
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
// #@@range_end(includes)

void* operator new(size_t size, void* buf) {
  return buf;
}

void operator delete(void* obj) noexcept {
}

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        RGBResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        BGRResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
  }

  for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
    for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
      // 白で塗りつぶし
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }
  for (int x = 0; x < 200; ++x) {
    for (int y = 0; y < 100; ++y) {
      // 緑の四角を描画
      pixel_writer->Write(x, y, {0, 255, 0});
    }
  }

  // #@@range_begin(write_fonts)
  int i = 0;
  for (char c = '!'; c <= '~'; ++c, ++i) {
    WriteAscii(*pixel_writer, 8 * i, 50, c, {0, 0, 0});
  }
  WriteString(*pixel_writer, 0, 66, "Hello, World!", {0, 0, 255});
  // #@@range_end(write_fonts)

  // #@@range_begin(sprintf)
  char buf[128];
  sprintf(buf, "1 + 2 = %d", 1 + 2);
  WriteString(*pixel_writer, 0, 82, buf, {0, 0, 0});
  // #@@range_end(sprintf)
  while (1) __asm__("hlt");
}