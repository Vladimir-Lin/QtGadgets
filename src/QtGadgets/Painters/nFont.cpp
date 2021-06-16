#include <qtgadgets.h>

typedef struct        {
  char   Family [964] ;
  double Size         ;
  int    Stretch      ;
  int    Weight       ;
  int    FixedPitch   ;
  int    Bold         ;
  int    Italic       ;
  int    Kerning      ;
  int    Overline     ;
  int    StrikeOut    ;
  int    Underline    ;
  double WordSpacing  ;
} nFontConfiguration  ;

N::Font:: Font     (void)
        : QFont    (    )
        , uuid     (0   )
        , name     (""  )
        , cm       (0.40)
        , editable (true)
{
  setStyleStrategy ( PreferAntialias ) ;
}

N::Font:: Font     (const QString & family,int pointSize,int weight,bool italic)
        : QFont    (                family,    pointSize,    weight,     italic)
        , uuid     (0                                                          )
        , name     (""                                                         )
        , cm       (0.40                                                       )
        , editable (true                                                       )
{
  setStyleStrategy ( PreferAntialias ) ;
}

N::Font:: Font     (const QFont & font, QPaintDevice * pd)
        : QFont    (              font,                pd)
        , uuid     (0                                    )
        , name     (""                                   )
        , cm       (0.40                                 )
        , editable (true                                 )
{
  setStyleStrategy ( PreferAntialias ) ;
}

N::Font:: Font     (const QFont & font)
        : QFont    (              font)
        , uuid     (0                 )
        , name     (""                )
        , cm       (0.40              )
        , editable (true              )
{
  setStyleStrategy ( PreferAntialias ) ;
}

N::Font:: Font  (const Font & font)
        : QFont (             font)
{
  uuid     = font.uuid                 ;
  name     = font.name                 ;
  cm       = font.cm                   ;
  editable = font.editable             ;
  setStyleStrategy ( PreferAntialias ) ;
}

int N::Font::packsize(void)
{
  return sizeof(nFontConfiguration) ;
}

void N::Font::setScreen(Screen & screen)
{
  int mm = (int)(cm * 100)                   ;
  int ps = screen . heightPixels ( mm ) / 10 ;
  setPixelSize ( ps )                        ;
}

void N::Font::setDPI(int DPI)
{
  int    ps   = 0     ;
  double inch = cm    ;
  inch *= 100         ;
  inch /= 254         ;
  inch *= DPI         ;
  ps    = (int)inch   ;
  setPixelSize ( ps ) ;
}

QByteArray N::Font::Configure(void)
{
  QByteArray conf                                            ;
  conf . resize ( sizeof(nFontConfiguration) )               ;
  nFontConfiguration nfc                                     ;
  memset ( &nfc , 0 , sizeof(nFontConfiguration) )           ;
  QString f = family ( )                                     ;
  strcpy ( nfc.Family , f.toUtf8().constData() )             ;
  nfc . Size        = cm                                     ;
  nfc . Stretch     = stretch     ()                         ;
  nfc . Weight      = weight      ()                         ;
  nfc . FixedPitch  = fixedPitch  () ? 1 : 0                 ;
  nfc . Bold        = bold        () ? 1 : 0                 ;
  nfc . Italic      = italic      () ? 1 : 0                 ;
  nfc . Kerning     = kerning     () ? 1 : 0                 ;
  nfc . Overline    = overline    () ? 1 : 0                 ;
  nfc . StrikeOut   = strikeOut   () ? 1 : 0                 ;
  nfc . Underline   = underline   () ? 1 : 0                 ;
  nfc . WordSpacing = wordSpacing ()                         ;
  memcpy ( conf.data() , &nfc , sizeof(nFontConfiguration) ) ;
  return     conf                                            ;
}

void N::Font::setConfigure(QByteArray & conf)
{
  if (conf.size()!=sizeof(nFontConfiguration)) return          ;
  nFontConfiguration * nfc = (nFontConfiguration *)conf.data() ;
  QString f = QString::fromUtf8 ( nfc -> Family )              ;
  cm = nfc->Size                                               ;
  setFamily     (  f                   )                       ;
  setStretch    (  nfc->Stretch        )                       ;
  setWeight     (  nfc->Weight         )                       ;
  setFixedPitch ( (nfc->FixedPitch==1) )                       ;
  setBold       ( (nfc->Bold      ==1) )                       ;
  setItalic     ( (nfc->Italic    ==1) )                       ;
  setKerning    ( (nfc->Kerning   ==1) )                       ;
  setOverline   ( (nfc->Overline  ==1) )                       ;
  setStrikeOut  ( (nfc->StrikeOut ==1) )                       ;
  setUnderline  ( (nfc->Underline ==1) )                       ;
  setWordSpacing(  nfc->WordSpacing    )                       ;
}

QByteArray N::Font::toCpp(QString variableName,int tabSize)
{
  QByteArray cpp                       ;
  QString    space = " "               ;
  space = space.repeated(tabSize)      ;
  cpp.append ( space.toUtf8()        ) ;
  cpp.append ( "nFont "              ) ;
  cpp.append ( variableName.toUtf8() ) ;
  cpp.append ( ";\n"                 ) ;
  return cpp                           ;
}

QFont N::Font::toQFont(void)
{
  return *((QFont *)this) ;
}
