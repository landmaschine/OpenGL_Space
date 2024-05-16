#include "HitBoxRender.h"

HitBoxRender::HitBoxRender() {}

HitBoxRender::HitBoxRender(PolyData poly, MovementComponent& move) {
    polydat.print(poly);
}

HitBoxRender::~HitBoxRender() {
    
}