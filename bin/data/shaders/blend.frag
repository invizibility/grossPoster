uniform sampler2D blob;
uniform sampler2D guts;
//uniform float blendAlpha;

void main(void) {
    vec2 texcoord = gl_TexCoord[0].xy;
    vec4 background = texture2D(blob, texcoord);
    vec4 foreground = texture2D(guts, texcoord);
    
    gl_FragColor = foreground + background;
}
