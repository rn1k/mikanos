#pragma once

// #@@range_begin(pixel_color_def)
#include "frame_buffer_config.hpp"

struct PixelColor {
  uint8_t r, g, b;
};
// #@@range_end(pixel_color_def)

class PixelWriter {
 public:
  PixelWriter(const FrameBufferConfig& config) : config_{config} {
  }
  // virtual: 仮想関数を表す．virtualがついているとオーバーライドされる
  virtual ~PixelWriter() = default; // destructor
  virtual void Write(int x, int y, const PixelColor& c) = 0; // `=0`は純粋仮想関数であることを示す

 protected:
  uint8_t* PixelAt(int x, int y) {
    return config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x);
  }

 private:
  const FrameBufferConfig& config_;
};

// #@@range_begin(pixel_writer_def)
class RGBResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};
// #@@range_end(pixel_writer_def)