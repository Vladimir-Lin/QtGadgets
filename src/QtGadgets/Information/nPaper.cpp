#include <qtgadgets.h>

N::Paper:: Paper(void)
{
}

N::Paper::~Paper(void)
{
}

bool N::Paper::load(Sql & sql,QString table)
{
  bool success = false                                 ;
  papers.clear()                                       ;
  if (!sql.isValid()) return false                     ;
  SqlConnection SQL(sql)                               ;
  if (SQL.open("nPaper","load"))                       {
    QString   Q                                        ;
    Q = sql.SelectFrom("uuid,name,width,height",table) +
        " order by id asc;"                            ;
    if (SQL.Query(Q)) while (SQL.Next())               {
      PaperSize PS                                     ;
      PS.uuid      = SQL.Uuid(0)                       ;
      PS.name      = SQL.String(1)                     ;
      PS.direction = Qt::Vertical                      ;
      PS.width     = SQL.Value(2).toInt()              ;
      PS.height    = SQL.Value(3).toInt()              ;
      papers << PS                                     ;
    } else                                             {
    }                                                  ;
    success = (papers.count() > 0)                     ;
    SQL.close()                                        ;
  } else                                               {
  }                                                    ;
  SQL.remove()                                         ;
  return success                                       ;
}

bool N::Paper::isValid(PaperSize & p)
{
  if (p.name.length()<=0) return false ;
  if (p.width        <=0) return false ;
  if (p.height       <=0) return false ;
  return true                              ;
}

N::PaperSize & N::Paper::indexOf(QString name)
{
  for (int i=0;i<papers.count();i++)           {
    if (papers[i].name==name) return papers[i] ;
  }                                            ;
  return papers[0]                             ;
}

N::PaperSize & N::Paper::operator[](QString name)
{
  return indexOf(name);
}

int N::Paper::WidthPixels(QString paper,int DPI)
{
  PaperSize PS = indexOf(paper) ;
  if (!isValid(PS)) return 0    ;
  return Pixels(DPI,PS.width)   ;
}

int N::Paper::HeightPixels(QString paper,int DPI)
{
  PaperSize PS = indexOf(paper) ;
  if (!isValid(PS)) return 0    ;
  return Pixels(DPI,PS.height)  ;
}

// Conversion between DPI and millimeter
// inch = 2.54 cm = 25.4 mm
// DPI  = dot / inch
// DPCM = dot / cm = DPI / 2.54
// 1 cm = 10 mm
// DPMM = DPI / 25.4 = (DPI * 10) / 254
// Pixels = Length * DPMM = Length * DPI * 10 / 254
int N::Paper::Pixels(int DPI,int mm)
{
  long long pm = DPI ;
  pm *= 10           ;
  pm *= mm           ;
  pm /= 254          ;
  return (int)pm     ;
}

QStringList N::Paper::Sizes(void)
{
  QStringList S                      ;
  for (int i=0;i<papers.count();i++) {
    S << papers[i].name              ;
  }                                  ;
  return S                           ;
}
