#include <qtgadgets.h>

N::ChartPiece:: ChartPiece(void)
{
}

N::ChartPiece:: ChartPiece(const ChartPiece & piece)
{
  ME = piece ;
}

N::ChartPiece::~ChartPiece(void)
{
}

void N::ChartPiece::addName(QString name)
{
  Name = name ;
}

void N::ChartPiece::setColor(Qt::GlobalColor color)
{
  Color = color ;
}

void N::ChartPiece::setColor(QColor color)
{
  Color = color ;
}

void N::ChartPiece::setPercentage(float percentage)
{
  Percentage = percentage ;
}

N::ChartPiece & N::ChartPiece::operator = (const ChartPiece & piece)
{
  nMemberCopy ( piece , Name       ) ;
  nMemberCopy ( piece , Color      ) ;
  nMemberCopy ( piece , Percentage ) ;
  return ME                          ;
}
