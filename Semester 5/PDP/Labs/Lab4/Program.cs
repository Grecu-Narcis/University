using Lab4;
using System;

class Program
{
    static void Main()
    {
        List<string> urls = ["www.dspcluj.ro/HTML/CORONAVIRUS/incidenta.html",
            "www.dspcluj.ro/HTML/CORONAVIRUS/incidenta.html",
            "www.dspcluj.ro/HTML/CORONAVIRUS/incidenta.html",
            "www.dspcluj.ro/HTML/CORONAVIRUS/incidenta.html"];

        CallBackSolution callBackSolution = new CallBackSolution(urls);
        TaskSolution taskSolution = new TaskSolution(urls);
        AsyncAwaitSolution asyncAwaitSolution = new AsyncAwaitSolution(urls);

        while (true)
        {
            printMenu();

            Console.WriteLine("Your option: ");
            string option = Console.ReadLine();

            switch (option)
            {
                case "1":
                    callBackSolution.Run();
                    break;

                case "2":
                    taskSolution.Run();
                    break;

                case "3":
                    asyncAwaitSolution.Run();
                    break;
            }

            Console.WriteLine();
        }
    }
    
    static void printMenu()
    {
        Console.WriteLine("Select solution:");
        Console.WriteLine("1. Callback\n2.Tasks\n3.Async-await\n");
    }
}
