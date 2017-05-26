#version 330

//Both GPU and CPU has access to a 'uniform' variable, so it can change at runtime.
uniform sampler2D diffuse;

//Shared with the vertex shader
in vec2 texCoord0;
in vec3 normal0;

out vec4 FragColor;

void main(){
    //@Hardcoded: Should import this with a uniform.
    vec3 lightDirection = vec3(0, 0, 1);

	//Lighting is applied in the second line.
    FragColor = texture2D(diffuse, texCoord0)
        * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}