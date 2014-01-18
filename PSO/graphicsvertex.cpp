#include "graphicsvertex.h"

GraphicsVertex::GraphicsVertex()
{
    setFlag(ItemIsMovable);
    qreal size = 20;
    setRect(0, 0, size, size);
}
