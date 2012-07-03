/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */

#ifndef AMBOSS_KML_HELPER_WRITER_H_INCLUDED
#define AMBOSS_KML_HELPER_WRITER_H_INCLUDED

#include <string>
#include <ostream>

namespace Amboss {
namespace KML {


inline std::string getIndent( size_t indent )
{
    std::string ret = "";
    for( size_t i=0 ; i<indent ; ++i ) ret += "  ";
    return ret;
}


inline void writePoint( std::ostream &out , double x , double y , size_t indent , const std::string &name )
{
    out << getIndent( indent     ) << "<Placemark>" << "\n";
    if( name != "" ) out << getIndent( indent + 1 ) << "<name>" << name << "</name>" << "\n";
    out << getIndent( indent + 1 ) << "<Point>" << "\n";
    out << getIndent( indent + 2 ) << "<coordinates>" << "\n";
    out << getIndent( indent + 3 ) << x << "," << y << ",0 " << "\n";
    out << getIndent( indent + 2 ) << "</coordinates>" << "\n";
    out << getIndent( indent + 1 ) << "</Point>" << "\n";
    out << getIndent( indent     ) << "</Placemark>" << "\n";
}

} // namespace KML
} // namespace Amboss


#endif // AMBOSS_KML_HELPER_WRITER_H_INCLUDED
