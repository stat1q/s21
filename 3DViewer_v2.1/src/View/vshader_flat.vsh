#extension GL_EXT_gpu_shader4 : require
attribute highp vec4 a_position; // координаты точки(вертекса)
attribute highp vec2 a_texcoord; // координаты текстуры
attribute highp vec3 a_normal; // нормаль

uniform int a_shift;
uniform int n_shift;

uniform mediump vec4 color; // через переменную типа uniform передаем извне цвет
uniform sampler2D u_texture; // текстура
uniform highp vec4 u_ligthtPosition; // позиция источника света
uniform highp float u_lightPower; // интенсивность света

uniform highp float u_specelarFactor;
uniform highp vec4 u_ligthtColor;

uniform highp mat4 u_projectionMatrix; // матрица проекции
uniform highp mat4 u_vievMatrix;  // видовая матрица
uniform highp mat4 u_modelMatrix; // матрица модели

flat varying vec4 FragColor;

void main(void)
{
    vec4 v_position;
    vec2 v_texcoord;
    vec3 v_normal;

    mat4 mv_matrix = u_vievMatrix * u_modelMatrix;

    gl_Position = u_projectionMatrix * mv_matrix * a_position;

    v_texcoord = a_texcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = mv_matrix * a_position;

    vec4 resultColor;
    if (n_shift == 0) {
    resultColor = color;
    } else {
    resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 diffMatColor;

    if (a_shift == 0) {
        diffMatColor = color;
    } else if (a_shift == 1) {
         diffMatColor = texture2D(u_texture, v_texcoord);
    }

    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVect = normalize(v_position.xyz - u_ligthtPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVect, v_normal));
    float len = length(v_position.xyz - eyePosition.xyz);
    float ambientFactor = 0.1;

    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVect)); // / (1.0 + 0.25 * pow(len, 2.0));
    resultColor += diffColor;

    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;

    vec4 specelarColor = u_ligthtColor * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVect)), u_specelarFactor); /// (1.0 + 0.25 * pow(len, 2.0));
    resultColor += specelarColor;
    }
    FragColor = resultColor;
}
