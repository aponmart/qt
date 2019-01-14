/*
 *  DisplayList.hpp
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

#ifndef __DisplayList_h__
#define __DisplayList_h__ 1

/*
 * The DisplayList class illustrates how to use the classes that update and change
 * the Flash Player's display list.
 *
 * To run this example, type the following on a command line:
 *
 * examples --example DisplayList [--resultDir path]
 *
 * where
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 */
class DisplayList
{
public:
    DisplayList(map< string, string>& options)
    {
        FSMovie movie;

        int width = 160;
        int height = 120;

        movie.setFrameSize(FSBounds(0, 0, 880, 180));
        movie.setFrameRate(2.0f);
        movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

        /*
        * Define the outline of a rectangle.
        */
        FSShape rectangle;

        rectangle.add(new FSShapeStyle(1, 1, 0, -width/2, -height/2));
        rectangle.add(new FSLine(width, 0));
        rectangle.add(new FSLine(0, height));
        rectangle.add(new FSLine(-width, 0));
        rectangle.add(new FSLine(0, -height));

        /*
        * The following variables are reused for each shape to simplify the code.
        * The shape and style arrays can be safely reused in the FSDefineShape
        * constructor as it will assume ownership of the objects they contain so
        * no explicit memory management is required.
        */
        int identifier = 0;

        FSBounds bounds(-width/2, -height/2, width/2, height/2);
        FSShape shape;

        FSVector<FSLineStyle*> lineStyles(1);
        FSVector<FSFillStyle*> fillStyles(1);

        /*
        * Define a red rectangle.
        */
        shape = rectangle;
        identifier = movie.newIdentifier();

        lineStyles[0] = new FSSolidLine(1, FSColorTable::black());
        fillStyles[0] = new FSSolidFill(FSColorTable::red());

        FSDefineShape* redRectangle = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        movie.add(redRectangle);

        /*
        * Define a yellow rectangle.
        */
        shape = rectangle;
        identifier = movie.newIdentifier();

        lineStyles[0] = new FSSolidLine(1, FSColorTable::black());
        fillStyles[0] = new FSSolidFill(FSColorTable::yellow());

        FSDefineShape* yellowRectangle = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        movie.add(yellowRectangle);
        
        /*
        * The FSPlaceObject class is used to add a shape on the display list.
        *
        * Objects are referenced by their unique identifier - specified when the
        * object is created. Objects are placed on the display list on a given
        * layer. Layers define the order in which shapes are displayed. Shapes
        * with a higher layer number are displayed in front of those with a lower
        * layer number. The location and appearance of the shape is controlled
        * by an FSCoordTransform and optional FSColorTranform objects. These
        * transforms can be used to display a shape without changing the original
        * definition - allowing it to be reused.
        *
        * The FSPlaceObject class provides a simplified constructor which allows
        * the coordinates where an object will be placed to be specified rather
        * than explicitly creating an FSCoordTranform object.
        *
        * FSShowFrame is used to render the display list on the screen. The scope
        * of a frame is delimited by successive FSShowFrame objects.
        */

        /*
        * Place the red rectangle on layer 1, at coordinates (100,80).
        */
        movie.add(new FSPlaceObject(redRectangle->getIdentifier(), 1, 100, 80));
        movie.add(new FSShowFrame());

        /*
        * Place the yellow rectangle in front of the red rectangle.
        */
        movie.add(new FSPlaceObject(yellowRectangle->getIdentifier(), 2, 120, 100));
        movie.add(new FSShowFrame());

        /*
        * To Change the location of an object it first must be removed then placed
        * at its new location. The FSPlaceObject2 class simplifies this into single
        * step - see later.
        */
        movie.add(new FSRemoveObject(redRectangle->getIdentifier(), 1));
        movie.add(new FSPlaceObject(redRectangle->getIdentifier(), 1, 140, 80));
        movie.add(new FSShowFrame());

        /*
        * The FSPlaceObject2 class provides more control over how the display
        * list is updated. It should be used in preference to the FSPlaceObject
        * class. For placing new objects on the display list the constructors
        * are identical.
        */
        movie.add(new FSPlaceObject2(redRectangle->getIdentifier(), 3, 320, 80));
        movie.add(new FSShowFrame());

        /*
        * Place the yellow rectangle in front of the red rectangle.
        */
        movie.add(new FSPlaceObject2(yellowRectangle->getIdentifier(), 4, 340, 100));
        movie.add(new FSShowFrame());

        /*
        * To Change the location of an object only the layer number is required to
        * reference the object.
        */
        movie.add(new FSPlaceObject2(3, 360, 80));
        movie.add(new FSShowFrame());

        /*
        * The FSPlaceObject2 class can also be used to replace an object on a layer
        * with another. Only the identifier of the new object and the layer number
        * of the object being replaced is required. The new object will be placed
        * at the same location as the one it replaces.
        */
        movie.add(new FSPlaceObject2(redRectangle->getIdentifier(), 5, 560, 80));
        movie.add(new FSShowFrame());

        // Replace the red rectangle with the yellow.
        movie.add(new FSPlaceObject2(yellowRectangle->getIdentifier(), 5));
        movie.add(new FSShowFrame());

        /*
        * The FSPlaceObject2 class can define clipping region where the outline of a
        * shape is used to clip objects placed in front of it up to and including a
        * given layer number.
        *
        * Use the outline of the red rectangle to clip all objects placed
        * in front, up to layer 8.
        */
        movie.add(new FSPlaceObject2(redRectangle->getIdentifier(), 6, 8, 740, 80));
        movie.add(new FSPlaceObject2(redRectangle->getIdentifier(), 7, 760, 100));
        movie.add(new FSPlaceObject2(yellowRectangle->getIdentifier(), 8, 780, 120));
        movie.add(new FSShowFrame());

        /*
        * the FSRemoveObject2 class is slightly simpler to use than FSRemoveObject
        * as only the layer number is required to remove an object.
        */
        movie.add(new FSRemoveObject(yellowRectangle->getIdentifier(), 8));
        movie.add(new FSShowFrame());

        saveMovie(movie, stringOption(options, "resultDir"), "DisplayList.swf");
    }
};

#endif