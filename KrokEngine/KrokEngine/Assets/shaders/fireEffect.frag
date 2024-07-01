//FIRE FRAGMENT SHADER
#version 330
#extension GL_ARB_explicit_uniform_location : require

precision highp float;

layout(location = 2) uniform sampler2D diffuseTexture;
layout(location = 3) uniform vec4 diffuseColor;
layout(location = 4) uniform float time;
layout(location = 5) uniform vec4 fireColor;

in vec3 worldVertex;
in vec2 texCoord;

out vec4 fragment_color;

float rand(float n){
    return fract(sin(n) * 43758.5453123);
}

float noise(float p){
    float fl = floor(p);
    float fc = fract(p);
    return mix(rand(fl), rand(fl + 1.0), fc);
}

void main( void ) {
    
    //Texture
    vec4 texColor = texture2D(diffuseTexture, texCoord);

    //Flickering
    float flickerSpeed = 20.0f;
    float flicker = clamp(noise(time * flickerSpeed), 0.8, 1.0);

    //GlowEffect
    float m_GlowDistance = 0.5f;
    float m_GlowSpeed = 2.5f;
    float tempGlow = worldVertex.y * m_GlowDistance - time * m_GlowSpeed;
    float glow = tempGlow - floor(tempGlow);

    vec4 color = texColor * diffuseColor * fireColor + (glow * 0.35 * fireColor);
    color.a = clamp( texColor.a * diffuseColor.a * fireColor.a + glow * flicker, 0 , texColor.a);
    fragment_color = color;
}