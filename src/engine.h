#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "shaders/shader.h"
#include "tgaimage.h"

struct Engine_Data {
  Vec3f main_light_dir;
  float main_light_intensity;
  Vec3f camera_pos;
  float *z_buffer;
};

class Engine {
private:
  Vec3f main_light_dir;
  float main_light_intensity;
  Vec3f camera_pos;
  float *z_buffer;
  void wireframe_dfs(const Face &f, bool (&faces_visited)[],
                     TGAImage *frame_buffer) const;

public:
  Engine(Vec3f main_light_dir_, float main_light_intensity_, Vec3f camera_pos_,
         float *zbuffer_)
      : main_light_dir(main_light_dir_),
        main_light_intensity(main_light_intensity_), camera_pos(camera_pos_),
        z_buffer(zbuffer_) {}
  Engine_Data get_engine_data() const {
    Engine_Data data;
    data.main_light_dir = main_light_dir;
    data.main_light_intensity = main_light_intensity;
    data.camera_pos = camera_pos;
    data.z_buffer = z_buffer;
    return data;
  }

  void reset_zbuffer(int width, int height) {
    delete[] z_buffer;
    z_buffer = new float[width * height];
  }

  void render_shaded_model(const HEModel &model, Shader *shader,
                           TGAImage *frame_buffer) const;
  void render_model_wireframe(const HEModel &model,
                              TGAImage *frame_buffer) const;
  void rasterize_triangle(const std::vector<V2F> vert_data, Shader *shader,
                          TGAImage *frame_buffer) const;
  void draw_line(int x0, int y0, int x1, int y1, TGAColor color,
                 TGAImage *frame_buffer) const;
  ~Engine() { delete[] z_buffer; }
};

#endif
