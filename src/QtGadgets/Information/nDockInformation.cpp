#include <qtgadgets.h>

N::DockInformation:: DockInformation(void)
{
  floating = false ;
  show     = true  ;
  area     = 0     ;
  width    = 0     ;
  height   = 0     ;
}

N::DockInformation:: DockInformation(const DockInformation & dock)
{
  ME = dock ;
}

N::DockInformation::~DockInformation(void)
{
}

N::DockInformation & N::DockInformation::operator = (const DockInformation & dock)
{
  nMemberCopy ( dock , floating ) ;
  nMemberCopy ( dock , show     ) ;
  nMemberCopy ( dock , area     ) ;
  nMemberCopy ( dock , width    ) ;
  nMemberCopy ( dock , height   ) ;
  return ME                       ;
}
