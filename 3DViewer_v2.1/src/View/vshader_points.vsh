attribute highp vec4 a_positionP;
uniform highp mat4 u_projectionMatrixP;
uniform highp mat4 u_vievMatrixP;
uniform highp mat4 u_modelMatrixP;

void main(void)
{
    mat4 mv_matrix = u_vievMatrixP * u_modelMatrixP;
    gl_Position = u_projectionMatrixP * mv_matrix * a_positionP;
}
