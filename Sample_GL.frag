#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragVector;

// output data
out vec3 color;

void main()
{
		const float c = 0.02f;

    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    float dist = sqrt(sqrt(fragVector[0] * fragVector[0] + fragVector[1] * fragVector[1] + fragVector[2] * fragVector[2]));
    color = vec3(fragColor[0] + c * dist, fragColor[1] + c * dist, fragColor[2] + c * dist);
}
