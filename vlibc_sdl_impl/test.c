#define __VLIBC_SDL_IMPL__
#define SDL_MAIN_HANDLED
#include "vlibc_sdl.h"

#define WIDTH 800
#define HEIGHT 600

vlibc_shader_data_t frag_shader_data;
vlibc_fragment_shader_t frag_shader;
vlibc_canvas canvas;

float* depth_buffer;

vlibc_uint32_t frag_shader_f(vlibc_vec2d frag_pos, vlibc_rgba frag_color, vlibc_shader_data_t *data) {
	int depthBufferIndex = WIDTH * frag_pos.y + frag_pos.x;
	float currentDepth = depth_buffer[depthBufferIndex];
	vlibc_f_rgba *passthrough_data = data->passthrough_data;
	float fragDepth = passthrough_data[2].r;
	if (fragDepth >= currentDepth) {
		return vlibc_rgba_to_hex((vlibc_rgba){0, 0, 0, 0});
	}

	depth_buffer[depthBufferIndex] = fragDepth;

	vlibc_vec3d result = (vlibc_vec3d){0, 0, 0}; 

	vlibc_vec3d fragPos = (vlibc_vec3d){
		passthrough_data[1].r, passthrough_data[1].g, passthrough_data[1].b
	};

	float ambient = 0.06f;
	vlibc_vec3d lightColor = (vlibc_vec3d){VLIBC_ABS(float, vlibc_cos(__vlibc_sdl_time * 0.01f)), VLIBC_ABS(float, vlibc_sin(__vlibc_sdl_time * 0.01f)), 1};
	vlibc_vec3d lightPos = (vlibc_vec3d){vlibc_sin(__vlibc_sdl_time * 0.01f) * 1.5f, vlibc_cos(__vlibc_sdl_time * 0.01f) * 1.5f, 2};

	vlibc_vec3d normal = vlibc_vec3d_normalize((vlibc_vec3d){passthrough_data[0].r, passthrough_data[0].g, passthrough_data[0].b});
	vlibc_vec3d lightDir = vlibc_vec3d_normalize(vlibc_sub_vec3d(lightPos, fragPos));
	float diff = VLIBC_MAX(vlibc_vec3d_dot(normal, lightDir), 0.0);
	diff = VLIBC_MAX(ambient, diff);
	vlibc_vec3d diffuse = (vlibc_vec3d){diff, diff, diff};
	diffuse = vlibc_mul_vec3d(diffuse, lightColor);

	float specularIntensity = 0.5;
	vlibc_vec3d viewDir = vlibc_vec3d_normalize(vlibc_sub_vec3d((vlibc_vec3d){0, 0, 0}, fragPos));
	vlibc_vec3d reflectDir = vlibc_vec3d_reflect(vlibc_vec3d_negate(lightDir), normal);
	float spec = vlibc_pow(VLIBC_MAX(vlibc_vec3d_dot(viewDir, reflectDir), 0.0), 8);
	vlibc_vec3d specular = vlibc_mul_vec3d((vlibc_vec3d){specularIntensity * spec, specularIntensity * spec, specularIntensity * spec}, lightColor);

	result = vlibc_add_vec3d(diffuse, specular);

	result.x = VLIBC_ABS(float, result.x);
	result.y = VLIBC_ABS(float, result.y);
	result.z = VLIBC_ABS(float, result.z);

	return vlibc_rgba_to_hex(vlibc_f_rgba_to_rgba((vlibc_f_rgba) {
		(result.x) * 255, (result.y) * 255, (result.z) * 255, 255
	}));
}

vlibc_mat4_t perspective;

void display() {
	memset(canvas.pixels, vlibc_rgba_to_hex((vlibc_rgba) {0, 0, 0, 255}), WIDTH * HEIGHT * sizeof(uint32_t));

	for (int i = 0; i < WIDTH * HEIGHT; i++) {
						  /*FLT_MAX*/
		depth_buffer[i] = 3.40282346638528859812e+38F;
	}

	// cube vertices stolen from learnopengl
	static float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

#define attributesCount 3
#define floatsPerElement 6
#define elementsCount sizeof(vertices) / sizeof(float) / floatsPerElement
	static vlibc_vertex transformedVertices[elementsCount] = {};
	static vlibc_f_rgba staticAttributes[elementsCount * attributesCount];


	vlibc_mat4_t transformation = vlibc_mat4_identity();
	transformation = vlibc_mat4_scaling((vlibc_vec3d) {0.6f, 0.6f, 0.6f});
	transformation = vlibc_mat4_mul(vlibc_mat4_rotation(__vlibc_sdl_time * VLIBC_DEG2RAD * 0.5f, (vlibc_vec3d){1, 1, 1}), transformation);
	transformation = vlibc_mat4_mul(vlibc_mat4_translation((vlibc_vec3d) {0, 0, -2.5}), transformation);

	for (int i = 0; i < elementsCount * floatsPerElement; i += floatsPerElement) {
		int elementIndex = i / floatsPerElement;
		vlibc_vertex* currentVertex = &transformedVertices[elementIndex];

		vlibc_f_rgba* attributes = &staticAttributes[elementIndex * attributesCount];

		float* position = &vertices[i];
		float position4[] = {
			position[0], position[1], position[2], 1
		};

		currentVertex->col_count = attributesCount;
		currentVertex->col = attributes;
		vlibc_vec3d perspectivePosition = vlibc_mat4_mul_pos(vlibc_mat4_mul(perspective, transformation), (vlibc_vec3d){position[0], position[1], position[2]});
		position4[0] = perspectivePosition.x;
		position4[1] = perspectivePosition.y;
		position4[2] = perspectivePosition.z;

		vlibc_vec3d normal = (vlibc_vec3d){
			vertices[i + 3], vertices[i + 4], vertices[i + 5]
		};

		vlibc_vec3d multiplied = vlibc_mat4_mul_dir(transformation, normal);

		attributes[0] = 
			(vlibc_f_rgba){
				multiplied.x, multiplied.y, multiplied.z, 255
			};
		attributes[1] = (vlibc_f_rgba) {
			position4[0], position4[1], position4[2], 255
		};
		attributes[2] = (vlibc_f_rgba) {vlibc_linearize_depth(perspectivePosition.z, 0.01f, 10.0f), 0, 0, 0};


		currentVertex->pos = (vlibc_vec2d) {
			position4[0],
			position4[1]
		};
		currentVertex->pos = (vlibc_vec2d) {
			(currentVertex->pos.x + 0.5) * WIDTH,
			(currentVertex->pos.y + 0.5) * HEIGHT
		};
	}


	vlibc_f_rgba frag_shader_passthrough_data[attributesCount] = {};


	vlibc_vertex drawnVertices[elementsCount] = {};
	int drawnTriangles = 0;
	for (int i = 0; i < elementsCount; i += 3) {
		vlibc_vertex currentVertex1 = transformedVertices[i];
		vlibc_vertex currentVertex2 = transformedVertices[i + 1];
		vlibc_vertex currentVertex3 = transformedVertices[i + 2];
		int mustContinue = 0;
		if (drawnTriangles) {
			for (int j = 0; j < drawnTriangles; j += 3) {
				vlibc_vertex testVertex1 = drawnVertices[j];
				vlibc_vertex testVertex2 = drawnVertices[j + 1];
				vlibc_vertex testVertex3 = drawnVertices[j + 2];
				if (vlibc_vertex_equal(currentVertex1, testVertex1) && vlibc_vertex_equal(currentVertex2, testVertex2) && vlibc_vertex_equal(currentVertex3, testVertex3)) {
					mustContinue = 1;
					break;
				}
			}
		}
		if (mustContinue) continue;
		frag_shader_data.passthrough_data = frag_shader_passthrough_data;
		vlibc_filled_triangle(&canvas, (vlibc_rgba){0, 0, 0, 255}, (vlibc_vec2d){0, 0}, &transformedVertices[i], &frag_shader, &frag_shader_data);
		drawnVertices[drawnTriangles++] = currentVertex1;
		drawnVertices[drawnTriangles++] = currentVertex2;
		drawnVertices[drawnTriangles++] = currentVertex3;
	}

	vlibc_sdl_flush_canvas(&canvas);
}

int main(int argc, char *argv[]) {
	frag_shader_data = vlibc_create_shader_data(vlibc_nullptr, 0, vlibc_nullptr);
	frag_shader = vlibc_create_fragment_shader(frag_shader_f);

	canvas = vlibc_sdl_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});

	perspective = vlibc_mat4_perspective(60.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 10.0f);
	depth_buffer = malloc(WIDTH * HEIGHT * sizeof(float));

	vlibc_sdl_create_window("test", WIDTH, HEIGHT);
	vlibc_sdl_start(display);

	return 0;
}