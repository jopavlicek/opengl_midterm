attribute highp vec4 position;
attribute lowp vec4 color;
varying lowp vec4 col;
uniform highp float damage;

void main() {
    float avgColor = (color.r+color.b+color.g)/3.0;
    vec4 tmpColor = vec4(avgColor, avgColor, avgColor, damage);
    col = tmpColor;
    gl_Position = position;
}
