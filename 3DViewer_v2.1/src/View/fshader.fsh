uniform mediump vec4 color; // через переменную типа uniform передаем извне цвет
uniform sampler2D u_texture; // текстура
uniform highp vec4 u_ligthtPosition; // позиция источника света
uniform highp vec4 u_ligthtColor;
uniform highp float u_lightPower; // интенсивность света
uniform highp float u_specelarFactor;


uniform int a_shift;
uniform int n_shift;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

void main(void)
{
    vec4 resultColor;
    if (n_shift == 0) {
    resultColor = color; // результирующий цвет( по умолчанию черный)

    } else {
    resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 diffMatColor;

    if (a_shift == 0) {
        diffMatColor = color;
    } else if (a_shift == 1) {
         diffMatColor = texture2D(u_texture, v_texcoord);
    }

    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz); // вектор направления взгляда (все вектора нужно нормировать)
    vec3 lightVect = normalize(v_position.xyz - u_ligthtPosition.xyz); // вектор направления освещения (из конца вычитаем начало)
    vec3 reflectLight = normalize(reflect(lightVect, v_normal)); // вектор направления отраженного света(для этого есть функция reflect(вектор направления света, нормаль относительно которой нужно отразмить данный свет)
    float len = length(v_position.xyz - eyePosition.xyz); // расстояние от наблюдателя до рассматривоемой точки
    float ambientFactor = 0.1; // интенсивность фонового освещения


    // Это освещение по ФОНГУ!!!!
    /*
    расчет диффузного цвета (умножаем цвет материала на интенсивность источника света  и на скалярное произведение
    нормали и обратного вектора направления освещения(отсекая отрицательные(max))
    */
    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVect)); // / (1.0 + 0.25 * pow(len, 2.0));
    resultColor += diffColor;
    /*
    расчет окружающего(фонового) света
    */
    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;
    /*
    добвление блика источника света. Умножается цвет источника(в данном случае белый, непрозрачный), интенсивность свечения,  скалярное
    произведение отраженного света на обратное направление вектору взгляда и все это выражение возводится в степень размера пятна блика
    (1.0 + 0.25 * pow(len, 2.0)) - это деление на еденицу + коэфф умноженный на квадррат рассстояния для уменьшения влияния источника света
    в зависимости от расстояния
    */
    vec4 specelarColor = u_ligthtColor * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVect)), u_specelarFactor); /// (1.0 + 0.25 * pow(len, 2.0));
    resultColor += specelarColor;
    }
    gl_FragColor = resultColor;
}
