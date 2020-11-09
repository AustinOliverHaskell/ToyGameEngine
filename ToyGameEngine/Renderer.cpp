#include "Renderer.h"

Renderer::Renderer(Camera * camera) {
	this->camera = camera;
	items_to_render = new std::map<unsigned int, Renderable*>();
}

Renderer::~Renderer() {
	delete items_to_render;
}

void Renderer::add_item(Renderable* item) {
	items_to_render->emplace(item->id, item);
}

void Renderer::remove_item(unsigned int id) {
	items_to_render->erase(id);
}

void Renderer::swap_camera(Camera* camera) {
	this->camera = camera;
}

void Renderer::render() {
	for (auto item : *items_to_render) {
		render_item(item.second);
	}
}

void Renderer::render_item(unsigned int item) {

	auto item_iter = items_to_render->find(item);
	if (item_iter == items_to_render->end()) {
		throw "Item to render's ID was not found";
	}

	render_item(item_iter->second);
}

void Renderer::render_item(Renderable* item) {
	if (camera == nullptr) {
		return;
	}

	glm::mat4 MVP = camera->projection_matrix * 
					camera->view_matrix * 
					item->transform;

	glUseProgram(item->shader);

	glUniformMatrix4fv(item->MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(item->ModelMatrixID, 1, GL_FALSE, &item->transform[0][0]);
	glUniformMatrix4fv(item->ViewMatrixID, 1, GL_FALSE, &camera->view_matrix[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, item->verticies);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, item->colors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, item->normals);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(glm::vec3) * item->face_count * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}


