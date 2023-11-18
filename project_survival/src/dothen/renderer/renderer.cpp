#include "renderer.h"

DOTHENRenderer::DOTHENRenderer(DOTHENRendererContext *context){
	this->context = context;
}

DOTHENRenderer::~DOTHENRenderer(){
	/// EMPTY
}

void DOTHENRenderer::render(){
	this->processRenderer();
}
