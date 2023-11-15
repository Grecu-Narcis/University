package Model;

public class Dog extends Animal {
    public Dog(int age)
    {
        super(age);
    }
    @Override
    public String sound()
    {
        return "Wof wof!";
    }
}
