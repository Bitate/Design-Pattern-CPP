/***********************************************************************
 * Decorator Design Pattern
 * 
 * Participants:
 *      Component (Visual Component)
 *          The interface for objects that can have responsibilities 
 *          added to them dynamically.
 *      ConcreteComponent (TextView)
 *          An object to which additional responsibilities can be attached.
 *      Decorator
 *          Keep/Maintains a reference to a Component object and defines 
 *          an interface that conforms to Component's interface.
 *      ConcreteDecorator (BorderDecorator, ScrollDecorator)
 *          Adds responsibilities to the component.
 * Collaborations:
 *      Decorator forwards requests to its Component object. It may
 *      optionally perform additional operations before and after 
 *      forwarding the request.
 ***********************************************************************/

/**
 * We assume there's Component class called VisualComponent.
 */
class VisualComponent
{
public:
    VisualComponent();
    virtual void Draw();
    virtual void Resize();
    // ...
};

/**
 * We define a subclass of VisualComponent called Decorator,
 * which we will subclass to obtain different decorations.
 */
class Decorator : public VisualComponent
{
public:
    Decorator(VisualComponent* );

    virtual void Draw();
    virtual void Resize();
    // ...

private:
    VisualComponent* _component;
};

/**
 * Decorator decorates the VisualComponent referenced by the _component pointer,
 * which is initialized in the Decorator's constructor. For each operatio in 
 * VisualComponent's interface, Decorator defines a default implementation that
 * passes the request to _component.
 */
void Decorator::Draw()
{
    _component->Draw();
}

void Decorator::Resize()
{
    _component->Resize();
}

/**
 * Subclasses of Decorator define specific decorations. The class BorderDecorator
 * adds a border to its enclosing component. BorderDecorator is a subclass of 
 * Decorator that overrides the Draw() to draw the border. BorderDecorator also
 * define a private DrawBorder() helper function that does the drawing. The subclass
 * inherits all other operation implementations form Decorator.
 * 
 * A similar implementation would follow for ScrollDecorator and DropShadowDecorator,
 * which would add scrolling and drop shadow operations to visual component.
 */
class BorderDecorator : public Decorator
{
public:
    BorderDecorator(VisualComponent*, int borderWidth);
    virtual void Draw();

private:
    void DrawBorder(int);
private:
    int _width;
};

/**
 * Now we can compose instances of these classes to provide different decorations.
 * The following code illustrates how we can use decorators to create a bordered
 * scrollable TextView.
 *
 * First, we need a way to put a visual component into a window object.
 * We'll assume our Window class provides a SetContents operation for this purpose.
 */
void Window::SetContents(VisualComponent* contents)
{
    // ...
}

/**
 * Now we can create the text view and a window to put it in.
 */
Window* window = new Window;
TextView* textView = new TextView;

/**
 * TextView is a VisualComponent, which lets us put it into the window:
 */
window->SetContents(textView);

/**
 * But we want a bordered and scrollable TextView. So we decorate it accordingly
 * before putting it in the window.
 * 
 * Because Window accesses its contents through the VisualComponent interface, 
 * it's unaware of decorator's presence and its modifications. 
 * The client/user can still keep track of the text view 
 * if the client/user have to interact with it directly,
 * for example, when you need to invoke operations that aren't part of the 
 * VisualComponent interface. Clients that rely on the component's indentity should
 * refer to it directly as well.
 */
window->SetContents(
    new BorderDecorator(
        new ScrollDecorator(textView), 
        1   // border width
    )
);

