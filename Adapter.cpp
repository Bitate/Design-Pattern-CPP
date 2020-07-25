/*************************************************************************
 * This is the TextShape class adapter.
 * 
 * Participants:
 *     Target(Shape)
 *          Defines the domain specific interface that Client uses.
 *     Client(DrawingEditor)
 *          Collaborates the objects conforming to the Target interface.
 *     Adapter(TextShape)
 *          To adapte the interface of Adaptee to the Target interface.
 *     Adaptee(TextView)
 *          An existing interface that needs adapting.
 * Collaborations:
 *      Clients call operations on an Adapter instance.
 *      In turn, the adapter calls Adaptee operations 
 *      that carry out the requst.
 *************************************************************************/

/**
 * This defines the domain-specific interface that Client uses.
 */
class Shape
{
public:
    Shape();
    virtual void BoundingBox(Point &bottomLeft, Point &topRight) const;
    
    /**
     * For creating a Manipulator object, which knows 
     * how to animate a shape when the user manipulates it.
     * But TextView has no this operation.
     */
    virtual Manipulator* CreateManipulator() const;
};

/**
 * This is the adaptee(to be adopted) class.
 * This is an existing interface that needs to be adapted.
 */
class TextView
{
public:
    TextView();
    void GetOrigin(Coord &x, Coord &y) const;
    void GetExtent(Coord &width, Coord &height) const;
    virtual bool IsEmpty() const;
};

/**
 * This is the TextShape adapter class to adapt TextView adaptee.
 * 
 * A class adaptor uses multiple inheritance to adapt interfaces.
 * The key to class adapters is to use one inheritance branch to 
 * inherit the interface and another branch to inherit the implementation.
 * In C++, inherit the interface publicly; inherit the implementation privately.
 */
class TextShape : public Shape, private TextView
{
public:
    TextShape();

    /**
     * This operation converts TextView's interface to conform to Shape's.
     */
    virtual void BoundingBox(Point &bottomLeft, Point &topRight) const;
    
    /**
     * This operation demonstrates the direct forwarding of requests common in adapter implementation.
     */
    virtual bool IsEmpty() const;
    
    /**
     * This operation is not supported/implemented by TextView class originally.(see line 40-46)
     * We implemente from scratch assuming we've already implemented a TextManipulator class that
     * supports manipulation of a TextShape.
     */
    virtual Manipulator *CreateManipulator() const;
};

// Implementations
void TextShape::BoundingBox(Point &bottomLeft, Point &topRight) const
{
    Coord bottom, left, width, height;
    GetOrigin(bottom, left);
    GetExtent(width, height);
    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}

bool TextShape::IsEmpty() const
{
    return TextView::IsEmpty();
}

Manipulator *TextShape::CreateManipulator() const
{
    return new TextManipulator(this);
}



/**********************************************************************
 * This is the object adapter.
 * 
 * Compare to class adapter, the object adapter requires a little more
 * effort to code, but it's more flexible. For example, the object 
 * adapter version of TextShape will work equally well with subclasses
 * of TextView --- That is the client simply passes an instance of 
 * a TextView subclass to the TextShape constructor.
 **********************************************************************/

/**
 * The object adapter uses object compisition to combine classes with different interfaces.
 * In this method, the adapter TextShape keeps a pointer to TextView.
 */
class TextShape : public Shape
{
public:
    TextShape(TextView* );
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;

private:
    TextView* _text;
};

/**
 * TextShape must initialize the pointer to TextView object, it does so in this constructor.
 * TextShape must also call operation on its TextView object whenever its own operations are called.
 * In below code, assuming that the client creates the TextView object and passes it into the TextShape constructor.
 */
TextShape::TextShape(TextView* t)
{
    _text = t;
}
void TextShape::BoundingBox(Point &bottomLeft, Point &topRight) const
{
    Coord bottom, left, width, height;
    _text->GetOrigin(bottom, left);
    _text->GetExtent(width, height);
    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}
bool TextShape::IsEmpty() const
{
    return _text->IsEmpty();
}

/**
 * CreateManipulator's implementation does not change from the class adapter version above,
 * since it's implemented from scratch and does not reuse any existing TextView functions.
 */
Manipulator *TextShape::CreateManipulator() const
{
    return new TextManipulator(this);
}