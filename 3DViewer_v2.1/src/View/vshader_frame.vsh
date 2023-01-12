attribute highp vec4 a_position;

uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_vievMatrix;
uniform highp mat4 u_modelMatrix;

varying highp vec4 v_position;

void main(void)
{
    mat4 mv_matrix = u_vievMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_matrix * a_position;
    v_position = mv_matrix * a_position;
}
