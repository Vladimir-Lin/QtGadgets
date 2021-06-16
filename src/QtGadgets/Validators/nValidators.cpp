#include <qtgadgets.h>

N::Validators:: Validators         (void)
              : QList<Validator *> (    )
{
}

N::Validators::~Validators (void)
{
  if ( count ( ) <= 0 ) return ;
  for (int i=0;i<count();i++)  {
    delete ME[i]               ;
  }                            ;
  clear ( )                    ;
}

N::Validator * N::Validators::validator(int type,QObject * parent)
{
  switch ( type )                                    {
    case 1001                                        :
    return new IntValidator               ( parent ) ;
    case 1002                                        :
    return new DoubleValidator            ( parent ) ;
    case 1101                                        :
    return new RegExpValidator            ( parent ) ;
    case 1102                                        :
    return new RegularExpressionValidator ( parent ) ;
    case 2001                                        :
    return new UuidValidator              ( parent ) ;
    case 10000 + Calendars::Geogrian                 :
    return new GeogrianValidator          ( parent ) ;
    case 10000 + Calendars::Holocene                 :
    return new HoloceneValidator          ( parent ) ;
    case 10000 + Calendars::Buddhist                 :
    return new BuddhistValidator          ( parent ) ;
    case 10000 + Calendars::StarDate                 :
    return new StardateValidator          ( parent ) ;
    case 10000 + Calendars::StarTrek                 :
    return new StarTrekValidator          ( parent ) ;
    case 10000 + Calendars::Taiwanese                :
    return new TaiwanValidator            ( parent ) ;
  }                                                  ;
  return NULL                                        ;
}
