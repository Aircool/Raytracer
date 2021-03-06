#pragma once

const int WIDTH = 1280;
const int HEIGHT = 720;

// RayTracing Options
const bool ENABLE_AREA_LIGHTING = true;
const bool ENABLE_REFLECTION = true;
const bool ENABLE_REFRACTION = false;

// Camera Constants
const float FOCAL_LENGTH = 1000.0f;
const int ANTI_ALIAS_X = 4;

// Lighting Coefficients
const float AMBIENT_COEFF = 0.5f;
const float DIFFUSE_COEFF = 0.3f;
const float SPECULAR_COEFF = 0.2f;