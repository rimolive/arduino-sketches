/*
    Copyright Giuseppe Di Cillo (www.coagula.org)
    Contact: dicillo@coagula.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE

const int buttonPinLeft = 8;      // pin for the Up button
const int buttonPinRight = 9;    // pin for the Down button
const int buttonPinEsc = 10;     // pin for the Esc button
const int buttonPinEnter = 11;   // pin for the Enter button
const int buttonPinNone = 20;   // pin for the Enter button

int adc_key_in  = 0;

// LiquidCrystal display with:
// rs on pin 7
// rw on ground
// enable on pin 6
// d4, d5, d6, d7 on pins 5, 4, 3, 2
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Menu variables
MenuBackend menu = MenuBackend(menuUsed, menuChanged);
//initialize menuitems
MenuItem menu1Item1 = MenuItem("Item1");
MenuItem menuItem1SubItem1 = MenuItem("Item1SubItem1");
MenuItem menuItem1SubItem2 = MenuItem("Item1SubItem2");
MenuItem menu1Item2 = MenuItem("Item2");
MenuItem menuItem2SubItem1 = MenuItem("Item2SubItem1");
MenuItem menuItem2SubItem2 = MenuItem("Item2SubItem2");
MenuItem menuItem3SubItem3 = MenuItem("Item2SubItem3");
MenuItem menu1Item3 = MenuItem("Item3");


void setup()
{
  lcd.begin(16, 2);

  //configure menu
  menu.getRoot().add(menu1Item1);
  menu1Item1.addRight(menu1Item2).addRight(menu1Item3);
  menu1Item1.add(menuItem1SubItem1).addRight(menuItem1SubItem2);
  menu1Item2.add(menuItem2SubItem1).addRight(menuItem2SubItem2).addRight(menuItem3SubItem3);
  menu.toRoot();
  lcd.setCursor(0, 0);
  lcd.print("www.coagula.org");

}  // setup()...


void loop()
{

  navigateMenus();  //in some situations I want to use the button for other purpose (eg. to change some settings)

} //loop()...


void menuChanged(MenuChangeEvent changed) {

  MenuItem newMenuItem = changed.to; //get the destination menu

  lcd.setCursor(0, 1); //set the start position for lcd printing to the second row

  if (newMenuItem.getName() == menu.getRoot()) {
    lcd.print("Main Menu       ");
  } else if (newMenuItem.getName() == "Item1") {
    lcd.print("Item1           ");
  } else if (newMenuItem.getName() == "Item1SubItem1") {
    lcd.print("Item1SubItem1");
  } else if (newMenuItem.getName() == "Item1SubItem2") {
    lcd.print("Item1SubItem2   ");
  } else if (newMenuItem.getName() == "Item2") {
    lcd.print("Item2           ");
  } else if (newMenuItem.getName() == "Item2SubItem1") {
    lcd.print("Item2SubItem1   ");
  } else if (newMenuItem.getName() == "Item2SubItem2") {
    lcd.print("Item2SubItem2   ");
  } else if (newMenuItem.getName() == "Item2SubItem3") {
    lcd.print("Item2SubItem3   ");
  } else if (newMenuItem.getName() == "Item3") {
    lcd.print("Item3           ");
  }
}

void menuUsed(MenuUseEvent used) {
  lcd.setCursor(0, 0);
  lcd.print("You used        ");
  lcd.setCursor(0, 1);
  lcd.print(used.item.getName());
  delay(1000);  //delay to allow message reading
  lcd.setCursor(0, 0);
  lcd.print("www.coagula.org");
  menu.toRoot();  //back to Main
}


int read_LCD_buttons() {              // read the buttons
  adc_key_in = analogRead(0);       // read the value from the sensor

  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  // We make this the 1st option for speed reasons since it will be the most likely result

  if (adc_key_in > 1000) return buttonPinNone;

  // For V1.0 comment the other threshold and use the one below:
  else if (adc_key_in < 50)   return buttonPinRight;
  else if (adc_key_in < 250)  return buttonPinEsc;
  else if (adc_key_in < 450)  return buttonPinEsc;
  else if (adc_key_in < 650)  return buttonPinLeft;
  else if (adc_key_in < 850)  return buttonPinEnter;

  return buttonPinNone;                // when all others fail, return this.
}

void navigateMenus() {
  MenuItem currentMenu = menu.getCurrent();

  switch (read_LCD_buttons()) {
    case buttonPinEnter:
      if (!(currentMenu.moveDown())) { //if the current menu has a child and has been pressed enter then menu navigate to item below
        menu.use();
      } else { //otherwise, if menu has no child and has been pressed enter the current menu is used
        menu.moveDown();
      }
      break;
    case buttonPinEsc:
      menu.toRoot();  //back to main
      break;
    case buttonPinRight:
      menu.moveRight();
      break;
    case buttonPinLeft:
      menu.moveLeft();
      break;
  }
}




