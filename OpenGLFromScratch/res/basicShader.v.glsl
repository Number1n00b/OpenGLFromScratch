#version 330

in vec3 position;
in vec2 texCoord;

//We're gonna use lambertion lighting. Done per-pixel.
in vec3 normal;

//Shared with the fragment shader
out vec2 texCoord0;
out vec3 normal0;

//Both GPU and CPU has access to a 'uniform' variable, so it can change at runtime.
//This transform variable is the camera position / view direction. It is what we use to get the perspective of the camera.
uniform mat4 transform;

void main(){
    //The transaltion factor affects how much the transform matrix translates the position vector.
    float translation_factor = 1.0;

    gl_Position = transform * vec4(position.x, position.y, position.z, translation_factor);

    //Set the texture coordinate.
    texCoord0 = vec2(texCoord.x, texCoord.y);
    normal0 = (transform * vec4(normal, 0.0)).xyz;
}