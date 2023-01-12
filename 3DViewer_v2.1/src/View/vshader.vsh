                                  // переменные атрибуты, т.е. те, которые пришли извне
attribute highp vec4 a_position; // координаты точки(вертекса)
attribute highp vec2 a_texcoord; // координаты текстуры
attribute highp vec3 a_normal; // нормаль

uniform highp mat4 u_projectionMatrix; // матрица проекции
uniform highp mat4 u_vievMatrix;  // видовая матрица
uniform highp mat4 u_modelMatrix; // матрица модели

varying highp vec4 v_position;  // переменные для передачи данных в фрагментный шейдер
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

void main(void)
{
    mat4 mv_matrix = u_vievMatrix * u_modelMatrix; // mv_matrix - это модельновидовая матрица

    gl_Position = u_projectionMatrix * mv_matrix * a_position; // формирование конечной позиции ( переможение координаты точки на матрицу проекции и модельновидовую матрицу)

    v_texcoord = a_texcoord; // передача текстурных координат в фрагментный шейдер, без модификаций
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0))); // передача нормали в фрагментный шейдер с учетом сдвигов и поворотов объекта
    v_position = mv_matrix * a_position; // передача координат точки с учетом сдвигов и поворотов объекта в фрагментный шейдер
}
