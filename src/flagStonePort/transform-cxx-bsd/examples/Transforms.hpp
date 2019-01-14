/*
 *  Transforms.hpp
 *  Transform Examples
 *
 *  Created by smackay on Tue May 13 2003.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#ifndef __Transforms_h__
#define __Transforms_h__ 1

/*
 * The Transforms class illustrates the different coordinate and colour transforms
 * that can be applied to an object to change its appearance without changing the
 * original definition.
 *
 * To run this example, type the following on a command line:
 *
 * examples --example Transforms [--resultDir path]
 *
 * where
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 */
class Transforms
{
public:
    Transforms(map<string, string>& options)
    {
        FSMovie movie;

        int width = 3200;
        int height = 2400;

        movie.setFrameSize(FSBounds(0, 0, 16000, 8000));
        movie.setFrameRate(2.0f);
        movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

        /*
        * Define the objects used to create the rectangle.
        */
        int identifier = movie.newIdentifier();

        FSBounds bounds(-width/2, -height/2, width/2, height/2);

        FSVector<FSLineStyle*> lineStyles(1);
        FSVector<FSFillStyle*> fillStyles(1);

        lineStyles[0] = new FSSolidLine(20, FSColorTable::black());
        fillStyles[0] = new FSSolidFill(FSColorTable::red());

        FSShape shape;

        shape.add(new FSShapeStyle(1, 1, 0, -width/2, -height/2));
        shape.add(new FSLine(width, 0));
        shape.add(new FSLine(0, height));
        shape.add(new FSLine(-width, 0));
        shape.add(new FSLine(0, -height));

        FSDefineShape* rectangle = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        movie.add(rectangle);

        // Define variables for the different transforms that will be applied to the shape.
        
        FSCoordTransform transform;
        FSColorTransform colourTransform;

        /*
        * Both the FSPlaceObject and FSPlaceObject2 can be used to add an object
        * to the display list and apply either a coordinate transform, a color 
        * transform or both.
        *
        * The first example applies a simple translation transform to set the
        * location of the object on the Flash Player's screen. Both classes
        * provide constructors where the x and y coordinates are provided as 
        * arguments avoiding the need to explicitly create an FSCoordTransform
        * object.
        *
        * Also the FSCoordTransform has a constructor where the location and 
        * scaling can be specified. Here the scaling is set in a second step
        * just for clarity.
        */

        transform = FSCoordTransform(2000, 2000);
        
        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 1, transform));
        movie.add(new FSShowFrame());

        /*
        * Scale the rectangle in both the x and y directions.
        */
        transform = FSCoordTransform(5600, 2000);
        transform.scale(0.6, 1.1);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 2, transform));
        movie.add(new FSShowFrame());

        /*
        * Rotate the rectangle clockwise by the specified number of degrees.
        */
        transform = FSCoordTransform(9200, 2000);
        transform.rotate(15);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 3, transform));
        movie.add(new FSShowFrame());

        /*
        * Apply a shearing transform to both the x and y directions.
        */
        transform = FSCoordTransform(13800, 2000);
        transform.shear(0.1, 0.2);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 4, transform));
        movie.add(new FSShowFrame());

        /*
        * Change the colour of the rectangle. Here the terms are added to the
        * colour defined for the solid fill style of the rectangle. A value
        * for the alpha channel can also be specified - here it is omitted.
        */
        transform = FSCoordTransform(2000, 6000);
        colourTransform = FSColorTransform(-255, 128, 0);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 5, transform, colourTransform));
        movie.add(new FSShowFrame());

        /*
        * Change the colour of the rectangle by changing the saturation of the colours
        * by specifying a multiplier for each channel. The alpha channel is omitted
        * as the FSDefineShape class does not support transparent shapes.
        */
        transform = FSCoordTransform(6000, 6000);
        colourTransform = FSColorTransform(0.7f, 1.0f, 1.0f);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 6, transform, colourTransform));
        movie.add(new FSShowFrame());

        /*
        * Both the add and multiply transforms can be performed in a single step.
        */
        transform = FSCoordTransform(10000, 6000);
        colourTransform = FSColorTransform(0.9f, 1.0f, 1.0f, 0, 128, 128);

        movie.add(new FSPlaceObject(rectangle->getIdentifier(), 7, transform, colourTransform));
        movie.add(new FSShowFrame());

        saveMovie(movie, stringOption(options, "resultDir"), "Transforms.swf");
    }
};

#endif