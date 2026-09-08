#include "shader.h"

class EmptyShader : public Shader {
public:
  EmptyShader() {}
  EmptyShader(ShaderGlobalPayload &payload) : Shader(payload) {}
  ~EmptyShader() = default;

  virtual V2F vertex_shader(const Vertex &vertex_input) {
    V2F processed_v;
    Matrix v_m = Matrix::vector2matrix(Math::get_homogeneous(vertex_input.pos));
    v_m = (global_payload.transform_matrix * v_m).cartesian();
    processed_v.pos = Math::to_Vec3<float>(v_m);

    return processed_v;
  }

  virtual Vec3i fragment_shader(const V2F &v2f) { return Vec3i(0, 0, 0); }
};
