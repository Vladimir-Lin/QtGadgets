#include <qtgadgets.h>

N::UuidValidator:: UuidValidator ( QObject * parent )
                 : QValidator    (           parent )
                 , Validator     (           parent )
{
}

N::UuidValidator::~UuidValidator (void)
{
}

int N::UuidValidator::Type(void) const
{
  return 2001 ;
}

void N::UuidValidator::Fixup(QString & input) const
{
  fixup(input) ;
}

QLocale N::UuidValidator::Locale(void) const
{
  return QValidator::locale() ;
}

void N::UuidValidator::setLocale (const QLocale & locale)
{
  QValidator::setLocale(locale) ;
}

QValidator::State N::UuidValidator::isValid(QString & input,int & pos) const
{
  return validate(input,pos) ;
}

void N::UuidValidator::fixup(QString & input) const
{ Q_UNUSED ( input ) ;
}

QValidator::State N::UuidValidator::validate(QString & input,int & pos) const
{
  if (input.length()<=0) return QValidator::Intermediate ;
  bool okay = false                                      ;
  input . toULongLong ( &okay )                          ;
  return okay ? Acceptable : Invalid                     ;
}
