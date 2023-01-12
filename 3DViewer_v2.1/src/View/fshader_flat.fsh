#extension GL_EXT_gpu_shader4 : require
flat varying vec4 FragColor;

void main(void)
{
    gl_FragColor = FragColor;
}
