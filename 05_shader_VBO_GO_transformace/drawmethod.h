#ifndef DRAWMETHOD_H
#define DRAWMETHOD_H

class DrawMethod
{
    int m_mode;
    int m_first;
    int m_count;
public:
    DrawMethod(int mode, int first, int count);
    void draw();
};

#endif // DRAWMETHOD_H
