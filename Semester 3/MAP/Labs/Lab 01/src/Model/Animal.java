package Model;

public abstract class Animal {
    private int age;

    public Animal(int age)
    {
        this.age = age;
    }

    public int getAge()
    {
        return this.age;
    }

    public abstract String sound();
}
