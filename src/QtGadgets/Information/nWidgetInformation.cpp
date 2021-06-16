#include <qtgadgets.h>

N::WidgetInformation:: WidgetInformation(QWidget * widget)
{
  setWidget ( widget ) ;
}

N::WidgetInformation:: WidgetInformation(void)
{
  visible  = false            ;
  minimize = false            ;
  maximize = false            ;
  geometry . setRect(0,0,0,0) ;
}

N::WidgetInformation::~WidgetInformation(void)
{
}

void N::WidgetInformation::setWidget(QWidget * widget)
{
  visible  = widget->isVisible   () ;
  minimize = widget->isMinimized () ;
  maximize = widget->isMaximized () ;
  geometry = widget->geometry    () ;
}

void N::WidgetInformation::restoreWidget(QWidget * widget)
{
  if (visible)                                         {
    if (minimize) { widget->showMinimized(); return; } ;
    if (maximize) { widget->showMaximized(); return; } ;
    widget->setGeometry(geometry)                      ;
  } else                                               {
    widget->hide()                                     ;
  }                                                    ;
}

bool N::WidgetInformation::Load(QString scope,Settings & settings)
{
  QStringList items                                                     ;
  items << "visible"                                                    ;
  items << "minimize"                                                   ;
  items << "maximize"                                                   ;
  items << "x"                                                          ;
  items << "y"                                                          ;
  items << "width"                                                      ;
  items << "height"                                                     ;
  bool info = true                                                      ;
  settings.beginGroup (scope)                                           ;
  for (int i=0;i<items.count();i++)                                     {
    if (!settings.contains(items[i])) info = false                      ;
  }                                                                     ;
  if (info)                                                             {
    if ("SQL"==settings.Mode)                                           {
      QString cn = settings.SQL->connection("WidgetInformation","Load") ;
      {
        QSqlDatabase db = settings.SQL->db(cn)                          ;
        if (settings.SQL->Open(db))                                     {
          QSqlQuery q(db)                                               ;
          visible  = settings.value(q,"visible" ).toBool()              ;
          minimize = settings.value(q,"minimize").toBool()              ;
          maximize = settings.value(q,"maximize").toBool()              ;
          geometry.setX     (settings.value(q,"x"     ).toInt())        ;
          geometry.setY     (settings.value(q,"y"     ).toInt())        ;
          geometry.setWidth (settings.value(q,"width" ).toInt())        ;
          geometry.setHeight(settings.value(q,"height").toInt())        ;
          settings.SQL->Close(db)                                       ;
        }                                                               ;
        db = QSqlDatabase()                                             ;
      }                                                                 ;
      QSqlDatabase::removeDatabase(cn)                                  ;
    } else                                                              {
      visible  = settings.value("visible" ).toBool()                    ;
      minimize = settings.value("minimize").toBool()                    ;
      maximize = settings.value("maximize").toBool()                    ;
      geometry.setX     (settings.value("x"     ).toInt())              ;
      geometry.setY     (settings.value("y"     ).toInt())              ;
      geometry.setWidth (settings.value("width" ).toInt())              ;
      geometry.setHeight(settings.value("height").toInt())              ;
    }                                                                   ;
  } else                                                                {
    #ifndef  QT_NO_DEBUG
    qDebug("No Widget Information")                                     ;
    #endif
  }                                                                     ;
  settings.endGroup   (                                               ) ;
  return info                                                           ;
}

bool N::WidgetInformation::Save(QString scope,Settings & settings)
{
  settings.beginGroup (scope                         )                ;
  if ("SQL"==settings.Mode)                                           {
    QString cn = settings.SQL->connection("WidgetInformation","Load") ;
    {
      QSqlDatabase db = settings.SQL->db(cn)                          ;
      if (settings.SQL->Open(db))                                     {
        QSqlQuery q(db)                                               ;
        settings.setValue   (q,"visible" ,visible          )          ;
        settings.setValue   (q,"minimize",minimize         )          ;
        settings.setValue   (q,"maximize",maximize         )          ;
        settings.setValue   (q,"x"       ,geometry.x     ())          ;
        settings.setValue   (q,"y"       ,geometry.y     ())          ;
        settings.setValue   (q,"width"   ,geometry.width ())          ;
        settings.setValue   (q,"height"  ,geometry.height())          ;
        settings.SQL->Close(db)                                       ;
      }                                                               ;
      db = QSqlDatabase()                                             ;
    }                                                                 ;
    QSqlDatabase::removeDatabase(cn)                                  ;
  } else                                                              {
    settings.setValue   ("visible" ,visible          )                ;
    settings.setValue   ("minimize",minimize         )                ;
    settings.setValue   ("maximize",maximize         )                ;
    settings.setValue   ("x"       ,geometry.x     ())                ;
    settings.setValue   ("y"       ,geometry.y     ())                ;
    settings.setValue   ("width"   ,geometry.width ())                ;
    settings.setValue   ("height"  ,geometry.height())                ;
  }                                                                   ;
  settings.endGroup   (                              )                ;
  return true                                                         ;
}
