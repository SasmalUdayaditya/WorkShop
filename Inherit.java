//Lets start with some java programs.
class Frnd
{
    void working(int a)
    {
        System.out.println("Age: "+a);
        System.out.println("Profession: Student");    
    }
}
public class Inherit extends Frnd{
    public static void main(String args[])
    {
        Inherit obj = new Inherit();
        obj.working(20);
    }
}
