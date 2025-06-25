attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;

void main() {
    vec4 tmpColor = vec4(1.0-colAttr.r, 1.0-colAttr.g, 1.0-colAttr.b, 1.0);
    col = tmpColor;
    gl_Position = posAttr;
}
