#include <iostream>
using namespace std;

class IBackpack
{
public:
  virtual void assemble() = 0;
  virtual ~IBackpack() {}
};

// A plain backpack only has shoulder straps.
class PlainBackpack : public IBackpack
{
public:
  virtual void assemble() 
  { 
    cout << "\n ShoulderStraps and mainCompartment"; 
  }
};

/**
 * Now, let's decorate the PlainBackpack.
 * 
 * IBackpack object is used to delegate the implementation of 
 * the assemble() method depending on the type of m_decorator.
 */
class BackpackDecorator : public IBackpack
{
public:
  BackpackDecorator(IBackpack *decorator) : m_Decorator(decorator) {}

  virtual void assemble()
  {
    m_Decorator->assemble();
  }

private:
  IBackpack *m_Decorator;
};

/**
 * Concrete Decorators.
 * 
 * Below three concrete Decorators are all identical apart from
 * the implementation of assemble().
 * 
 * The first, adds a laptopSlot;
 * The second, adds a USBCharge;
 * The third, adds a waterBottle.
 */
class WithLaptopSlot : public BackpackDecorator
{
public:
  WithLaptopSlot(IBackpack *dcrator) : BackpackDecorator(dcrator) {}
  virtual void assemble()
  {
    BackpackDecorator::assemble();
    cout << " + LaptopSlot";
  }
};

class WithUSBCharge : public BackpackDecorator
{
public:
  WithUSBCharge(IBackpack *dcrator) : BackpackDecorator(dcrator) {}
  virtual void assemble()
  {
    BackpackDecorator::assemble();
    cout << " + USBCharge";
  }
};

class WithWaterBottle : public BackpackDecorator
{
public:
  WithWaterBottle(IBackpack *dcrator) : BackpackDecorator(dcrator) {}
  virtual void assemble()
  {
    BackpackDecorator::assemble();
    cout << " + WaterBottle";
  }
};

/**
 * "Wrapping a gift, putting it in a box, and wrapping the box ..."
 * 
 * We must read below the construction of the backpack in reverse order.
 * 1. Create a PlainBackpack;
 * 2. Pass it to the BackpackDecorator;
 * 3. Which passes it along to be decorated with a laptop slot;
 * 4. In turn, it's passed to be decorated with a USB charge;
 * 5. Finally, the "box" is "wrapped" with a water bottle.
 * 
 * This way, the client has the power to dynamically assemble a backpack
 * with any features available;
 */
int main()
{
  IBackpack *pBackpack =
      new WithWaterBottle(                     //5
          new WithUSBCharge(                   //4
              new WithLaptopSlot(              //3
                  new BackpackDecorator(       //2
                      new PlainBackpack())))); //1

  pBackpack->assemble();
  delete pBackpack;

  return 0;
}
// Output
// ShoulderStraps and mainCompartment + LaptopSlot + USBCharge
// + WaterBottle

