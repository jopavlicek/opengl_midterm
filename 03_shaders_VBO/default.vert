attribute highp vec4 positionIn;
attribute lowp vec4 colorIn;
varying lowp vec4 colorOut;

void main()
{
    colorOut = colorIn;
    gl_Position = positionIn;
}
