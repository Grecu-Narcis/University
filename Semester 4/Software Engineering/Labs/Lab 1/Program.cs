using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Lab_1
{
    internal class Program
    {
        static string convertDateToHex(DateTime currentDate)
        {
            int currentDay = currentDate.Day,
                    currentMonth = currentDate.Month,
                    currentYear = currentDate.Year,
                    currentHour = currentDate.Hour,
                    currentMinute = currentDate.Minute,
                    currentSecond = currentDate.Second;

            return currentDay.ToString("X") + "." +
                currentMonth.ToString("X") + "." +
                currentYear.ToString("X") + " " +
                currentHour.ToString("X") + ":" +
                currentMinute.ToString("X") + ":" +
                currentSecond.ToString("X");
        }

        static string convertDateToBinary(DateTime currentDate)
        {
            int currentDay = currentDate.Day,
                    currentMonth = currentDate.Month,
                    currentYear = currentDate.Year,
                    currentHour = currentDate.Hour,
                    currentMinute = currentDate.Minute,
                    currentSecond = currentDate.Second;

            return Convert.ToString(currentDay, 2) + "." +
                Convert.ToString(currentMonth, 2) + "." +
                Convert.ToString(currentYear, 2) + " " +
                Convert.ToString(currentHour, 2) + ":" +
                Convert.ToString(currentMinute, 2) + ":" +
                Convert.ToString(currentSecond, 2);
        }

        static void Main(string[] args)
        {
            while (true)
            {
                DateTime currentTime = DateTime.Now;

                int currentDay = currentTime.Day,
                    currentMonth = currentTime.Month,
                    currentYear = currentTime.Year,
                    currentHour = currentTime.Hour,
                    currentMinute = currentTime.Minute,
                    currentSecond = currentTime.Second;

                Console.WriteLine("Decimal: " + currentTime.ToString());
                Console.WriteLine("Hex: " + convertDateToHex(currentTime));
                Console.WriteLine("Binary: " + convertDateToBinary(currentTime));

                Thread.Sleep(1000);
                Console.Clear();
            }
        }
    }
}
