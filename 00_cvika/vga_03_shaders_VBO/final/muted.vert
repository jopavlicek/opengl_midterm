attribute highp vec4 positionIn;
attribute lowp vec4 colorIn;
varying lowp vec4 colorOut;

void main()
{
    vec4 mutedColor = vec4(colorIn.r * 0.5, colorIn.g * 0.5, colorIn.b * 0.5, 1.0);
    colorOut = mutedColor;
    gl_Position = positionIn;
}
