/*
 * Layer.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LAYER_H_INCLUDED
#define AMBOSS_LAYER_H_INCLUDED


namespace Amboss {
namespace Shapefile {


class Layer
{
public:

    Layer( OGRLayer *ogrLayer ) : ogrLayer_( ogrLayer ) { }

    std::string name( void ) const { return ogrLayer_->GetName(); }
    

    // hier gehts weiter, GeometryType, FeatureDefinition, FeatureIteration, Filters

private:

    OGRLayer *ogrLayer_;
};

Layer makeLayer( OGRLayer *ogrLayer )
{
    return Layer( ogrLayer );
}



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_LAYER_H_INCLUDED
