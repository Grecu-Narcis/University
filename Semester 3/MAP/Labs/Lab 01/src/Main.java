// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
import Model.Animal;
import Model.Dog;

public class Main {
    public static void main(String[] args) {
//        int sum = 0;
//        int numberOfElements = 0;
//
//        for (String item : args)
//        {
//            try {
//                int currentNumber = Integer.parseInt(item);
//                numberOfElements++;
//                sum = sum + currentNumber;
//            }
//            catch(NumberFormatException ex) {
//                System.out.println(item + " is not a valid number. It won't be part of the average!");
//            }
//        }
//
//        if (numberOfElements != 0) {
//            double average = 1. * sum / numberOfElements;
//            System.out.println("The average is: " + average);
//        }
//
//        else
//        {
//            System.out.println("Please enter at least one number!");
//        }

        Dog a = new Dog(2);
        Animal b = new Dog(3);

        System.out.println(a.sound());
        System.out.println(b.sound());
    }
}