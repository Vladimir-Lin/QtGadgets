#include <qtgadgets.h>

N::RasterOptions:: RasterOptions(void)
                 : raster       (1   )
                 , numerator    (1   )
                 , denominator  (1   )
{
}

N::RasterOptions:: RasterOptions(const RasterOptions & options)
{
  ME = options ;
}

N::RasterOptions::~RasterOptions(void)
{
}

N::RasterOptions & N::RasterOptions::operator = (const RasterOptions & options)
{
  nMemberCopy ( options , raster      ) ;
  nMemberCopy ( options , numerator   ) ;
  nMemberCopy ( options , denominator ) ;
  nMemberCopy ( options , screen      ) ;
  nMemberCopy ( options , paper       ) ;
  nMemberCopy ( options , picture     ) ;
  return ME                             ;
}
